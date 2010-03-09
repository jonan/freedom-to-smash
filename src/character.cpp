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
Character::Character(Ogre::SceneManager &scene_manager, const CharacterType type, const int num_player)
        : AnimatedObject(scene_manager)
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
    // Define controls
    switch (num_player) {
    case 1:
        attack_key         = OIS::KC_NUMPAD1;
        defend_key         = OIS::KC_DOWN;
        jump_key           = OIS::KC_UP;
        move_left_key      = OIS::KC_LEFT;
        move_right_key     = OIS::KC_RIGHT;
        special_attack_key = OIS::KC_NUMPAD2;
        break;
    case 2:
        attack_key         = OIS::KC_G;
        defend_key         = OIS::KC_S;
        jump_key           = OIS::KC_W;
        move_left_key      = OIS::KC_A;
        move_right_key     = OIS::KC_D;
        special_attack_key = OIS::KC_H;
        break;
    default:
        attack_key         = OIS::KC_A;
        defend_key         = OIS::KC_DOWN;
        jump_key           = OIS::KC_UP;
        move_left_key      = OIS::KC_LEFT;
        move_right_key     = OIS::KC_RIGHT;
        special_attack_key = OIS::KC_S;
        break;
    }
    Ogre::Root::getSingleton().addFrameListener(this);
    Input::getInstance()->addKeyListener(*this);
}

// Destructor
Character::~Character(void)
{
    Ogre::Root::getSingleton().removeFrameListener(this);
    Input::getInstance()->removeKeyListener(*this);
}

// Detects and solves collisions of the character with the battle ground.
void Character::recoverFromPenetration(const std::list<Object*> &objects)
{
    on_floor = false;

    BOOST_FOREACH(Object *obj, objects) {
        switch (collision_box->detectCollision(*obj->getCollisionBox())) {
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

// Function to update the keyboard's state.
bool Character::keyPressed(const OIS::KeyEvent &key)
{
    if (key.key == attack_key) {
        if (action[DEFEND] && !action[SPECIAL_ATTACK_2]) {
            action[ATTACK_2] = true;
        } else if (on_floor && !action[LAND]  && !action[SPECIAL_ATTACK_1]) {
            action[ATTACK_1] = true;
        }
    } else if (key.key == defend_key) {
        action[MOVE] = false;
        action[DEFEND] = true;
    } else if (key.key == jump_key) {
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
    } else if (key.key == move_left_key || key.key == move_right_key) {
        if (!action[DEFEND]) {
            action[MOVE] = true;
            direction = (key.key == move_left_key) ? 1 : -1;
        }
    } else if (key.key == special_attack_key) {
        if (action[DEFEND] && !action[ATTACK_2]) {
            action[SPECIAL_ATTACK_2] = true;
        } else if (on_floor && !action[LAND] && !action[ATTACK_1]) {
            action[SPECIAL_ATTACK_1] = true;
        }
    }
    return true;
}

// Function to update the keyboard's state.
bool Character::keyReleased(const OIS::KeyEvent &key)
{
    if (key.key == defend_key) {
        action[DEFEND] = false;
    } else if ( (key.key == move_left_key  && direction == 1 ) ||
                (key.key == move_right_key && direction == -1)    ) {
        action[MOVE] = false;
    }
    return true;
}
