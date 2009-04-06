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

#include <string>

#include <OgreAnimationState.h>
#include <OgreEntity.h>
#include <OgreFrameListener.h>
#include <OgreSceneNode.h>

#include "input.hpp"

// Constructor
Character::Character(Ogre::SceneManager &scene_manager, CharacterType type, const int num_player) : Object(scene_manager) {
  setEntity("kid");
  setPosition(Ogre::Vector3(0,5,0));
  setAnimations();
  // Start with no action active
  for (int i=0; i < NUM_ACTIONS; i++) action[i] = false;
  // Define controls
  switch (num_player) {
    case 1:
      attack_key     = OIS::KC_N;
      jump_key       = OIS::KC_M;
      move_left_key  = OIS::KC_LEFT;
      move_right_key = OIS::KC_RIGHT;
      break;
    case 2:
      attack_key     = OIS::KC_F;
      jump_key       = OIS::KC_G;
      move_left_key  = OIS::KC_A;
      move_right_key = OIS::KC_S;
      break;
    default:
      attack_key     = OIS::KC_A;
      jump_key       = OIS::KC_S;
      move_left_key  = OIS::KC_LEFT;
      move_right_key = OIS::KC_RIGHT;
      break;
  }
  // Initialize variables
  on_floor = false;
}

// 
void Character::update(const Ogre::FrameEvent& event) {
  animate(event);
  move(event);
}

// 
bool Character::keyPressed(const OIS::KeyEvent& key) {
  if (key.key == attack_key && on_floor) {
    action[ATTACKING] = true;
  } else if (key.key == jump_key && on_floor && !action[ATTACKING]) {
    action[JUMPING] = true;
  } else if (key.key == move_left_key) {
    action[MOVING_LEFT] = true;
  } else if (key.key == move_right_key) {
    action[MOVING_RIGHT] = true;
  }
  return true;
}

// 
bool Character::keyReleased(const OIS::KeyEvent& key) {
  if (key.key == move_left_key) {
    action[MOVING_LEFT] = false;
  } else if (key.key == move_right_key) {
    action[MOVING_RIGHT] = false;
  }
  return true;
}

// 
void Character::recoverFromPenetration(Object &obj) {
  if (getBoundingBox()->intersects(*obj.getBoundingBox())) {
    if (!on_floor) {
      on_floor = true;
      action[FALLING] = false;
      animations[FALL_ANIMATION]->setTimePosition(0);
      double offset_y = node->getPosition().y-getBoundingBox()->getMinimum().y;
      node->setPosition(node->getPosition().x,obj.getBoundingBox()->getMaximum().y+offset_y,node->getPosition().z);
    }
  } else {
    on_floor = false;
  }
}

// 
void Character::setAnimations(void) {
  animations[ATTACK_ANIMATION] = entity->getAnimationState("attackforward1");
  animations[ATTACK_ANIMATION]->setLoop(false);
  animations[ATTACK_ANIMATION]->setEnabled(false);
  animations[FALL_ANIMATION] = entity->getAnimationState("fall1");
  animations[FALL_ANIMATION]->setLoop(false);
  animations[FALL_ANIMATION]->setEnabled(false);
  animations[IDLE_ANIMATION] = entity->getAnimationState("idle1");
  animations[IDLE_ANIMATION]->setLoop(true);
  animations[IDLE_ANIMATION]->setEnabled(false);
  animations[JUMP_ANIMATION] = entity->getAnimationState("jump1");
  animations[JUMP_ANIMATION]->setLoop(false);
  animations[JUMP_ANIMATION]->setEnabled(false);
  animations[RUN_ANIMATION] = entity->getAnimationState("run1");
  animations[RUN_ANIMATION]->setLoop(true);
  animations[RUN_ANIMATION]->setEnabled(false);
}

// 
void Character::animate(const Ogre::FrameEvent &event) {
  // Disable all animations
  for (int i=0; i<NUM_ANIMATIONS; i++) animations[i]->setEnabled(false);
  // Check what animations need to be enabled
  if (action[ATTACKING]) {
    animations[ATTACK_ANIMATION]->setEnabled(true);
    animations[ATTACK_ANIMATION]->addTime(event.timeSinceLastFrame);
    if (animations[ATTACK_ANIMATION]->hasEnded()) {
      animations[ATTACK_ANIMATION]->setTimePosition(0);
      action[ATTACKING] = false;
    }
  } else if (action[FALLING]) {
    animations[FALL_ANIMATION]->setEnabled(true);
    animations[FALL_ANIMATION]->addTime(event.timeSinceLastFrame);
  } else if (action[JUMPING]) {
    animations[JUMP_ANIMATION]->setEnabled(true);
    animations[JUMP_ANIMATION]->addTime(event.timeSinceLastFrame);
    if (animations[JUMP_ANIMATION]->hasEnded()) {
      animations[JUMP_ANIMATION]->setTimePosition(0);
      action[JUMPING] = false;
    }
  } else if (action[MOVING_LEFT] || action[MOVING_RIGHT]) {
    animations[RUN_ANIMATION]->setEnabled(true);
    animations[RUN_ANIMATION]->addTime(event.timeSinceLastFrame);
  } else {
    animations[IDLE_ANIMATION]->setEnabled(true);
    animations[IDLE_ANIMATION]->addTime(event.timeSinceLastFrame);
  }
}

// 
void Character::move(const Ogre::FrameEvent &event) {
  using Ogre::Vector3;
  if (action[MOVING_LEFT]) {
    node->translate(Vector3(5*event.timeSinceLastFrame,0,0));
    node->setDirection(0,0,-1,Ogre::Node::TS_PARENT);
  } else if (action[MOVING_RIGHT]) {
    node->translate(Vector3(-5*event.timeSinceLastFrame,0,0));
    node->setDirection(0,0,1,Ogre::Node::TS_PARENT);
  }
  if (action[JUMPING]) {
    node->translate(Vector3(0,5*event.timeSinceLastFrame,0));
  } else if (!on_floor) {
    action[FALLING] = true;
    node->translate(Vector3(0,-5*event.timeSinceLastFrame,0));
  }
}
