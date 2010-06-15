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
#include <physics/scene.hpp>
#include <input.hpp>

#include <lua_engine.hpp>
#include <fts_evaluator.hpp>
#include <script_manager.hpp>

// Constructor
Character::Character(const String &name, Ogre::SceneManager &scene_manager)
        : Object(name.c_str(), scene_manager, NUM_STATES)
        , on_floor(true)
        , has_double_jumped(false)
        , yaw(0)
        , collision_right(false)
        , collision_left(false)
        , jump_force(0)
        , walk_speed(0)
        , attack_obj(NULL)
        , attack_shape( &physics::ShapesManager::getInstance().getBoxShape( btVector3(0.1,4,10) ) )
        , initial_pos(NULL)
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
    delete initial_pos;
    Ogre::Root::getSingleton().removeFrameListener(this);
}

//
void Character::setInitialPos(Ogre::Vector3 *pos)
{
    initial_pos = new Ogre::Vector3(*pos);
}

// Loads a character script.
void Character::handleScript(const String &file)
{
    lua_State *L = ScriptManager::get().getL();
    bool res = false;
    FtsEvaluator ev(L);

    LuaEngine::RunFile(L, file);

    res = ev.evalNumber("Character.JumpForce", jump_force);
    res = ev.evalNumber("Character.WalkSpeed", walk_speed);

    double mass = 0;
    res = ev.evalNumber("Character.Mass", mass);

    double yaw = 0;
    res = ev.evalNumber("Character.Yaw", yaw);
    this->yaw = yaw;

    Ogre::Vector3 size;
    res = ev.evalVector3("Character.Size", size);

    double scale = 1;
    res = ev.evalNumber("Character.Scale", scale);

    node->yaw(Ogre::Degree(yaw));
    node->setScale(scale, scale, scale);

    entity->getSkeleton()->setBlendMode(Ogre::ANIMBLEND_CUMULATIVE);

    btVector3 bsize(size.x, size.y, size.z);
    btCollisionShape *shape = &physics::ShapesManager::getInstance().getBoxShape(bsize);
    setCenterOffset(physics::vector3(Ogre::Vector3(0,0,0)));
    createBody(mass, *shape, this);

    LuaEngine::BeginCallEx(L, "Character.OnCreate");
    LuaEngine::PushPointer(L, this, "Character *");
    LuaEngine::EndCall(L, 1);
}

// Start performing an attack.
void Character::attack(void)
{
    if (action[IDLE]) {
        stopAction(IDLE);
        action[ATTACK] = true;
        // Create physic attack object
        attack_obj = new physics::Object();
        attack_obj->createBody(20, *attack_shape);
        attack_obj->disableRotation();
        Ogre::Vector3 pos = getPosition();
        int dir = 0;
        if (direction == RIGHT && !collision_right)
            dir = -1;
        else if (direction == LEFT  && !collision_left)
            dir = 1;
        pos.x += dir*1.5;
        attack_obj->setPosition(pos.x, pos.y, pos.z);
        getScene()->addPhysicObject(*attack_obj);
    }
}

// Start performing a jump.
void Character::jump(void)
{
    if ( (action[JUMP] || action[FALL]) && !has_double_jumped) {
        stopAction(JUMP);
        stopAction(FALL);
        has_double_jumped = true;
        action[JUMP] = true;
        applyForce(physics::vector3(Ogre::Vector3(0,jump_force,0)));
    } else if (on_floor) {
        if (!action[ATTACK] && !action[DEFEND] && !action[LAND]) {
            stopAction(IDLE);
            action[JUMP] = true;
            applyForce(physics::vector3(Ogre::Vector3(0,jump_force,0)));
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
    setPosition(*initial_pos);
}

// Function that's called at the beginning of every frame.
bool Character::frameStarted(const Ogre::FrameEvent &event)
{
    frameAttack();
    frameCheck();
    frameMovement();
    frameAnimation(event);
    return true;
}

// Funtion that needs to be called every frame for the character to be updated.
void Character::frameAttack(void)
{
    if (attack_obj) {
        int dir = 0;
        if (direction == RIGHT && !collision_right)
            dir = -1;
        else if (direction == LEFT  && !collision_left)
            dir = 1;
        attack_obj->setVelocity(dir*70,0,0);
        if (!action[ATTACK]) {
            delete attack_obj;
            attack_obj = NULL;
        }
    }
}

// Funtion that needs to be called every frame for the character to be updated.
void Character::frameCheck(void)
{
    Real vertical_velocity = physics::vector3(getVelocity()).y;
    on_floor = (abs(vertical_velocity) < 0.1) && !action[JUMP];
    if (on_floor) {
        setVelocity(0, 0);
        if (action[FALL]) {
            stopAction(FALL);
            action[LAND] = true;
            has_double_jumped = false;
        } else if (!action[ATTACK] && !action[DEFEND] && !action[LAND] && !action[MOVE]) {
            action[IDLE] = true;
        }
    } else if (vertical_velocity < -0.1) {
        stopAction(JUMP);
        action[FALL] = true;
    }
}

// Funtion that needs to be called every frame for the character to be updated.
void Character::frameMovement(void)
{
    if (action[MOVE] && on_floor) {
        int dir = 0;
        if (direction == RIGHT && !collision_right)
            dir = -1;
        else if (direction == LEFT  && !collision_left)
            dir = 1;
        if (dir) {
            setVelocity(dir*walk_speed, 0);
            node->setDirection(0,0,-dir,Ogre::Node::TS_PARENT);
            node->yaw(Ogre::Degree(yaw));
        }
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

// Player stops performing an action
void Character::stopAction(const int type)
{
    BOOST_FOREACH(Ogre::AnimationState *anim, animations[type])
        anim->setTimePosition(0);
    action[type] = false;
}
