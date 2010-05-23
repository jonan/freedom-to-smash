/*
This file is part of Freedom to Smash.
Copyright (C) 2009 Jon Ander Peñalba <jonan88@gmail.com>

Freedom to Smash is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>
*/

#include <character.hpp>

// Boost
#include <boost/foreach.hpp>
#include <boost/format.hpp>

// Ogre
#include <OgreEntity.h>
#include <OgreRoot.h>

// FtS
#include <physics/converter_functions.hpp>
#include <physics/shapes_manager.hpp>
#include <input.hpp>

#include <lua_engine.hpp>
#include <fts_evaluator.hpp>
#include <script_manager.hpp>

// Constructor
Character::Character(const String &name, Ogre::SceneManager &scene_manager)
        : Object(name, scene_manager, NUM_STATES)
        , on_floor(true)
        , has_double_jumped(false)
        , collision_right(false)
        , collision_left(false)
        , jumping_time(0)
{
    String script_path = boost::str(boost::format("../scripts/char_%s.lua") % name);
    handleScript(script_path);
    disableRotation();

    // Start with no action active
    for (int i=0; i < NUM_STATES; i++)
        action[i] = false;

    Ogre::Root::getSingleton().addFrameListener(this);
}

// Destructor
Character::~Character(void)
{
    Ogre::Root::getSingleton().removeFrameListener(this);
}

// Loads a character script.
void Character::handleScript(const String &file)
{
    lua_State *L = ScriptManager::get().getL();
    bool res = false;
    FtsEvaluator ev(L);

    LuaEngine::RunFile(L, file);

    double mass = 0;
    res = ev.evalNumber("Character.Mass", mass);
    double yaw = 0;
    res = ev.evalNumber("Character.Yaw", yaw);
    Ogre::Vector3 pos;
    res = ev.evalVector3("Character.Position", pos);
    Ogre::Vector3 size;
    res = ev.evalVector3("Character.Size", size);
    double scale = 1;
    res = ev.evalNumber("Character.Scale", scale);

    setPosition(pos);
    node->yaw(Ogre::Degree(yaw));
    node->setScale(scale, scale, scale);

    entity->getSkeleton()->setBlendMode(Ogre::ANIMBLEND_CUMULATIVE);

    btVector3 bsize(size.x, size.y, size.z);
    btCollisionShape *shape = &physics::ShapesManager::getInstance().getBoxShape(bsize);
    createBody(mass, *shape, this);

    LuaEngine::BeginCallEx(L, "Character.OnCreate");
    LuaEngine::PushPointer(L, this, "Character *");
    LuaEngine::EndCall(L, 1);
}

// Start performing an attack.
void Character::attack(void)
{
    if (action[IDLE] || action[MOVE]) {
        stopAction(IDLE);
        action[ATTACK] = true;
    }
}

// Start performing a jump.
void Character::jump(void)
{
    if ( (action[JUMP] || action[FALL]) && !has_double_jumped) {
        stopAction(JUMP);
        stopAction(FALL);
        action[JUMP] = true;
        jumping_time = 0;
        has_double_jumped = true;
    } else if (on_floor) {
        if (!action[ATTACK] && !action[DEFEND] && !action[LAND]) {
            stopAction(IDLE);
            action[JUMP] = true;
            applyForce(physics::vector3(Ogre::Vector3(0,400,0)));
        }
    }
}

// Start defending.
void Character::defend(void)
{
    if (on_floor && action[IDLE]) {
        stopAction(IDLE);
        action[DEFEND] = true;
    }
}

// Start moving.
void Character::move(const MoveDirection direction)
{
    if (!action[DEFEND]) {
        action[MOVE] = true;
        this->direction = direction;
    }
}

//
void Character::reset(void)
{
    setPosition(Ogre::Vector3(0,5,0));
    jumping_time = 0;
}

// Function that's called at the beginning of every frame.
bool Character::frameStarted(const Ogre::FrameEvent &event)
{
    frameCheck();
    frameAnimation(event);
    frameMovement(event);
    return true;
}

// Funtion that needs to be called every frame for the character to be updated.
void Character::frameCheck(void)
{
    if (on_floor) {
        if (!action[ATTACK] && !action[DEFEND] && !action[LAND] && !action[MOVE]) {
            action[IDLE] = true;
        }
    } else if (!action[JUMP]) {
        action[FALL] = true;
    }
}

// Funtion that needs to be called every frame for the character to be updated.
void Character::frameAnimation(const Ogre::FrameEvent &event)
{
    // Disable all animations
    for (int i=0; i<NUM_STATES; i++)
        BOOST_FOREACH(Ogre::AnimationState *anim, animations[i])
            anim->setEnabled(false);
    // Check what animations need to be enabled
    for (int i=0; i<NUM_STATES; i++) {
        if (action[i]) {
            if (!(i==MOVE && !on_floor)) {
                if (performAnimation(i, event) && i!=JUMP) {
                    stopAction(i);
                }
            }
        }
    }
}

// Funtion that needs to be called every frame for the character to be updated.
void Character::frameMovement(const Ogre::FrameEvent &event)
{
    if (action[MOVE]) {
        int dir = 0;
        if (direction == RIGHT && !collision_right)
            dir = -1;
        else if (direction == LEFT  && !collision_left)
            dir = 1;
        if (dir) {
            translate(dir*25*event.timeSinceLastFrame, 0, 0);
            node->setDirection(0,0,-dir,Ogre::Node::TS_PARENT);
            node->yaw(Ogre::Degree(90));
        }
    }
    if (action[JUMP] || action[FALL]) {
        Real initial_speed = 0;
        if (action[JUMP]) {
            initial_speed = 80;
            if (calculateVerticalSpeed(initial_speed) <= 0) {
                stopAction(JUMP);
                jumping_time = 0;
                initial_speed = 0;
            }
        }
        jumping_time += event.timeSinceLastFrame;
        //translate(0, calculateVerticalSpeed(initial_speed)*event.timeSinceLastFrame, 0);
    }
}

// Player stops performing an action
void Character::stopAction(const int type)
{
    BOOST_FOREACH(Ogre::AnimationState *anim, animations[type])
        anim->setTimePosition(0);
    action[type] = false;
}

// Calculates the current vertical speed.
const Real Character::calculateVerticalSpeed(const Real &start_speed)
{
    const static Real GRAVITY = 300;
    return (start_speed - (GRAVITY * jumping_time));
}
