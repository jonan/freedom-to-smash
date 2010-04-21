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

#include "character.hpp"

#include <boost/foreach.hpp>

#include <OgreEntity.h>
#include <OgreRoot.h>

#include "input.hpp"

// Constructor
Character::Character(Ogre::SceneManager &scene_manager)
        : AnimatedObject(scene_manager, NUM_STATES)
        , on_floor(true)
        , has_double_jumped(false)
        , jumping_time(0)
        , direction(1)
{
    setEntity("sinbad");
    entity->getSkeleton()->setBlendMode(Ogre::ANIMBLEND_CUMULATIVE);
    attachEntityToBone("Sword", "Handle.L");
    attachEntityToBone("Sword", "Handle.R");
    setPosition(Ogre::Vector3(0,5,0));
    node->yaw(Ogre::Degree(90));
    prepareAnimations();
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
void Character::move(const bool right)
{
    if (!action[DEFEND]) {
        action[MOVE] = true;
        direction = (right) ? -1 : 1;
    }
}

// Detects and solves collisions of the character with the battle ground.
void Character::recoverFromPenetration(const std::list<Object*> &objects)
{
    on_floor = false;

    int collision;
    BOOST_FOREACH(Object *obj, objects) {
        collision = detectCollision(*obj);
        if (collision & physics::RIGHT_COLLISION) {
            if (direction == -1)
                stopAction(MOVE);
        }
        if (collision & physics::LEFT_COLLISION) {
            if (direction == 1)
                stopAction(MOVE);
        }
        if (collision & physics::TOP_COLLISION) {
            stopAction(JUMP);
        }
        if (collision & physics::BOTTOM_COLLISION) {
            on_floor = true;
            if (action[FALL]) {
                stopAction(FALL);
                action[LAND] = true;
                jumping_time = 0;
                has_double_jumped = false;
            }
        }
    }
}

// Function that's called at the beginning of every frame.
bool Character::frameStarted(const Ogre::FrameEvent &event)
{
    frameCheck();
    frameAnimation(event);
    frameMovement(event);
    return true;
}

// Prepares all animations so they can be used.
void Character::prepareAnimations(void)
{
    createAnimation(ATTACK, "SliceVertical");
    createAnimation(DEFEND, "DrawSwords");
    createAnimation(FALL, "JumpLoop", true);
    createAnimation(IDLE, "IdleTop", true);
    createAnimation(IDLE, "IdleBase", true);
    createAnimation(JUMP, "JumpStart");
    createAnimation(LAND, "JumpEnd");
    createAnimation(MOVE, "RunTop", true);
    createAnimation(MOVE, "RunBase", true);
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
        translate(direction*10*event.timeSinceLastFrame, 0, 0);
        node->setDirection(0,0,-direction,Ogre::Node::TS_PARENT);
        node->yaw(Ogre::Degree(90));
    }
    if (action[JUMP]) {
        jumping_time += event.timeSinceLastFrame;
        if (jumping_time > 1.5) {
            stopAction(JUMP);
        }
        translate(0, 10*event.timeSinceLastFrame, 0);
    } else if (action[FALL]) {
        translate(0, -10*event.timeSinceLastFrame, 0);
    }
}

// Player stops performing an action
void Character::stopAction(const int type)
{
    BOOST_FOREACH(Ogre::AnimationState *anim, animations[type])
        anim->setTimePosition(0);
    action[type] = false;
}
