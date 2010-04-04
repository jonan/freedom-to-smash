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

#include "collision_box.hpp"
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
    setPosition(Ogre::Vector3(0,5,0));
    node->yaw(Ogre::Degree(90));
    setCollisionBoxSize(1.5,-1.5,2.2,-5.25);
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
    if (action[DEFEND] && !action[SPECIAL_ATTACK_2]) {
        action[ATTACK_2] = true;
    } else if (on_floor && !action[LAND]  && !action[SPECIAL_ATTACK_1]) {
        action[ATTACK_1] = true;
    }
}

// Start defending.
void Character::defend(void)
{
    action[MOVE] = false;
    action[DEFEND] = true;
}

// Start performing a jump.
void Character::jump(void)
{
    if ( (action[JUMP] || action[FALL]) && !has_double_jumped && !action[DEFEND]) {
        stopAction(JUMP);
        stopAction(FALL);
        action[DOUBLE_JUMP] = true;
        jumping_time = 0;
        has_double_jumped = true;
    } else if (on_floor) {
        if (action[IDLE] || action[MOVE]) {
            action[IDLE] = false;
            action[JUMP] = true;
        }
    }
}

// Start moving left.
void Character::moveLeft(void)
{
    if (!action[DEFEND]) {
        action[MOVE] = true;
        direction = 1;
    }
}

// Start performing an action.
void Character::moveRight(void)
{
    if (!action[DEFEND]) {
        action[MOVE] = true;
        direction = -1;
    }
}

// Start moving right.
void Character::specialAttack(void)
{
    if (action[DEFEND] && !action[ATTACK_2]) {
        action[SPECIAL_ATTACK_2] = true;
    } else if (on_floor && !action[LAND] && !action[ATTACK_1]) {
        action[SPECIAL_ATTACK_1] = true;
    }
}

// Stop defending.
void Character::stopDefending(void)
{
    action[DEFEND] = false;
}

// Stop moving.
void Character::stopMoving(void)
{
    action[MOVE] = false;
}

// Detects and solves collisions of the character with the battle ground.
void Character::recoverFromPenetration(const std::list<Object*> &objects)
{
    on_floor = false;

    BOOST_FOREACH(Object *obj, objects) {
        switch (collision_box->detectCollision(obj->getCollisionBox())) {
        case RIGHT_COLLISION:
        case LEFT_COLLISION:
            stopAction(MOVE);
            break;
        case TOP_COLLISION:
            stopAction(JUMP);
            stopAction(DOUBLE_JUMP);
            action[FALL] = true;
            break;
        case BOTTOM_COLLISION:
            on_floor = true;
            if (action[FALL]) {
                stopAction(FALL);
                action[LAND] = true;
                jumping_time = 0;
                has_double_jumped = false;
            }
            break;
        default:
            break;
        }
    }
}

// Function that's called at the beginning of every frame.
bool Character::frameStarted(const Ogre::FrameEvent &event)
{
    animate(event);
    move(event);
    return true;
}

// Prepares all animations so they can be used.
void Character::prepareAnimations(void)
{
    createAnimation(ATTACK_1, "SliceVertical");
    createAnimation(ATTACK_2, "SliceHorizontal");
    createAnimation(DEFEND, "DrawSwords");
    createAnimation(DOUBLE_JUMP, "JumpStart");
    createAnimation(FALL, "JumpLoop");
    createAnimation(IDLE, "IdleTop", true);
    createAnimation(IDLE, "IdleBase", true);
    createAnimation(LAND, "JumpEnd");
    createAnimation(JUMP, "JumpStart");
    createAnimation(MOVE, "RunTop", true);
    createAnimation(MOVE, "RunBase", true);
    createAnimation(SPECIAL_ATTACK_1, "SliceVertical");
    createAnimation(SPECIAL_ATTACK_2, "SliceHorizontal");
}

// Funtion that needs to be called every frame for the character to be updated.
void Character::animate(const Ogre::FrameEvent &event)
{
    // Disable all animations
    for (int i=0; i<NUM_STATES; i++)
        BOOST_FOREACH(Ogre::AnimationState *anim, animations[i])
            anim->setEnabled(false);
    // Check what animations need to be enabled
    if (action[ATTACK_1] || action[ATTACK_2] || action[SPECIAL_ATTACK_1] || action[SPECIAL_ATTACK_2]) {
        // Check what attack is the player performing
        int i;
        if (action[ATTACK_1])
            i = ATTACK_1;
        else if (action[ATTACK_2])
            i = ATTACK_2;
        else if (action[SPECIAL_ATTACK_1])
            i = SPECIAL_ATTACK_1;
        else if (action[SPECIAL_ATTACK_2])
            i = SPECIAL_ATTACK_2;
        // Animate
        if (performAnimation(i, event))
            stopAction(i);
    } else if (action[DEFEND] && !action[LAND]) {
        performAnimation(DEFEND, event);
    } else if (action[DOUBLE_JUMP] || action[JUMP]) {
        // Check what jump is the player performing
        int i = (action[JUMP]) ? JUMP : DOUBLE_JUMP;
        performAnimation(i, event);
    } else if (action[FALL]) {
        performAnimation(FALL, event);
    } else if (action[LAND]) {
        if (performAnimation(LAND, event))
            stopAction(LAND);
    } else if (action[MOVE]) {
        performAnimation(MOVE, event);
    } else {
        action[IDLE] = true;
        performAnimation(IDLE, event);
    }
}

// Funtion that needs to be called every frame for the character to be updated.
void Character::move(const Ogre::FrameEvent &event)
{
    if (action[MOVE]) {
        if ( !(action[ATTACK_1] || action[ATTACK_2] || action[SPECIAL_ATTACK_1] || action[SPECIAL_ATTACK_2] || action[LAND]) ) {
            translate(direction*10*event.timeSinceLastFrame, 0, 0);
            node->setDirection(0,0,-direction,Ogre::Node::TS_PARENT);
            node->yaw(Ogre::Degree(90));
        }
    }
    if (action[DOUBLE_JUMP] || action[JUMP]) {
        jumping_time += event.timeSinceLastFrame;
        if (jumping_time > 1.5) {
            stopAction(JUMP);
            stopAction(DOUBLE_JUMP);
        }
        translate(0, 10*event.timeSinceLastFrame, 0);
    } else if (!on_floor) {
        action[FALL] = true;
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
