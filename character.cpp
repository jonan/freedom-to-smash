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
  direction = 1;
  jumping_time = 0;
  has_double_jumped = false;
  setEntity("kid");
  setPosition(Ogre::Vector3(0,5,0));
  prepareAnimations();
  // Start with no action active
  for (int i=0; i < NUM_STATES; i++) action[i] = false;
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
  // Initialize variables
  on_floor = false;
  Input::getInstance()->addKeyListener(this);
}

// Destructor
Character::~Character(void) {
  Input::getInstance()->removeKeyListener(this);
}

// Updates the character.
void Character::update(const Ogre::FrameEvent& event) {
  animate(event);
  move(event);
}

// Detects and solves collisions of the character with the battle ground.
void Character::recoverFromPenetration(std::vector<Object*>& objects) {
  Ogre::AxisAlignedBox intersection_box, object_box;
  Ogre::AxisAlignedBox character_box = *getBoundingBox();
  on_floor = false;

  for (unsigned int i=0; i<objects.size() && !on_floor; i++) {
    object_box = *objects[i]->getBoundingBox();
    intersection_box = character_box.intersection(object_box);
    if (!intersection_box.isNull()) {
      // Collision detected
      double offset_x = node->getPosition().x-getBoundingBox()->getMinimum().x;
      double offset_y = node->getPosition().y-getBoundingBox()->getMinimum().y;
      double width    = getBoundingBox()->getMaximum().x-getBoundingBox()->getMinimum().x;
      double height   = getBoundingBox()->getMaximum().y-getBoundingBox()->getMinimum().y;

      double intersection_width  = intersection_box.getMaximum().x - intersection_box.getMinimum().x;
      double intersection_height = intersection_box.getMaximum().y - intersection_box.getMinimum().y;

      if (intersection_box.getMaximum().x == object_box.getMaximum().x && intersection_height > intersection_width) {
        node->setPosition(intersection_box.getMaximum().x+offset_x,node->getPosition().y,node->getPosition().z);
      } else if (intersection_box.getMinimum().x == object_box.getMinimum().x && intersection_height > intersection_width) {
        node->setPosition(intersection_box.getMinimum().x-width+offset_x,node->getPosition().y,node->getPosition().z);
      } else if (intersection_box.getMaximum().y == object_box.getMaximum().y) {
        on_floor = true;
        node->setPosition(node->getPosition().x,intersection_box.getMaximum().y+offset_y,node->getPosition().z);
      } else if (intersection_box.getMinimum().y == object_box.getMinimum().y) {
        node->setPosition(node->getPosition().x,intersection_box.getMinimum().y-height+offset_y,node->getPosition().z);
      }
    } else if ( ( object_box.getMaximum().y == character_box.getMinimum().y &&
                  object_box.getMaximum().x >  character_box.getMinimum().x &&
                  object_box.getMinimum().x <  character_box.getMaximum().x    )
                                                                                 ) {
      on_floor = true;
    }
  }

  if (on_floor && action[FALL]) {
    stopAction(FALL);
    action[LAND] = true;
    jumping_time = 0;
    has_double_jumped = false;
  }
}

// Prepares all animations so they can be used.
void Character::prepareAnimations(void) {
  animations[ATTACK_1] = entity->getAnimationState("attackforward1");
  animations[ATTACK_1]->setLoop(false);
  animations[ATTACK_1]->setEnabled(false);
  animations[ATTACK_2] = entity->getAnimationState("attackneutral1");
  animations[ATTACK_2]->setLoop(false);
  animations[ATTACK_2]->setEnabled(false);
  animations[DEFEND] = entity->getAnimationState("hurt1");
  animations[DEFEND]->setLoop(false);
  animations[DEFEND]->setEnabled(false);
  animations[DOUBLE_JUMP] = entity->getAnimationState("jump1");
  animations[DOUBLE_JUMP]->setLoop(false);
  animations[DOUBLE_JUMP]->setEnabled(false);
  animations[FALL] = entity->getAnimationState("fall1");
  animations[FALL]->setLoop(false);
  animations[FALL]->setEnabled(false);
  animations[IDLE] = entity->getAnimationState("idle1");
  animations[IDLE]->setLoop(true);
  animations[IDLE]->setEnabled(false);
  animations[LAND] = entity->getAnimationState("land1");
  animations[LAND]->setLoop(false);
  animations[LAND]->setEnabled(false);
  animations[JUMP] = animations[DOUBLE_JUMP];
  animations[MOVE] = entity->getAnimationState("run1");
  animations[MOVE]->setLoop(true);
  animations[MOVE]->setEnabled(false);
  animations[SPECIAL_ATTACK_1] = entity->getAnimationState("attackup1");
  animations[SPECIAL_ATTACK_1]->setLoop(false);
  animations[SPECIAL_ATTACK_1]->setEnabled(false);
  animations[SPECIAL_ATTACK_2] = entity->getAnimationState("attackdown1");
  animations[SPECIAL_ATTACK_2]->setLoop(false);
  animations[SPECIAL_ATTACK_2]->setEnabled(false);
}

// Funtion that needs to be called every frame for the character to be updated.
void Character::animate(const Ogre::FrameEvent &event) {
  // Disable all animations
  for (int i=0; i<NUM_STATES; i++) if (animations[i]) animations[i]->setEnabled(false);
  // Check what animations need to be enabled
  if (action[ATTACK_1] || action[ATTACK_2] || action[SPECIAL_ATTACK_1] || action[SPECIAL_ATTACK_2]) {
    // Check what attack is the player performing
    int i;
         if (action[ATTACK_1])         i = ATTACK_1;
    else if (action[ATTACK_2])         i = ATTACK_2;
    else if (action[SPECIAL_ATTACK_1]) i = SPECIAL_ATTACK_1;
    else if (action[SPECIAL_ATTACK_2]) i = SPECIAL_ATTACK_2;
    // Animate
    animations[i]->setEnabled(true);
    animations[i]->addTime(event.timeSinceLastFrame);
    if (animations[i]->hasEnded())
      stopAction(i);
  } else if (action[DEFEND] && !action[LAND]) {
    animations[DEFEND]->setEnabled(true);
    animations[DEFEND]->addTime(event.timeSinceLastFrame);
  } else if (action[DOUBLE_JUMP] || action[JUMP]) {
    // Check what jump is the player performing
    int i = (action[JUMP]) ? JUMP : DOUBLE_JUMP;
    animations[i]->setEnabled(true);
    animations[i]->addTime(event.timeSinceLastFrame);
  } else if (action[FALL]) {
    animations[FALL]->setEnabled(true);
    animations[FALL]->addTime(event.timeSinceLastFrame);
  } else if (action[LAND]) {
    animations[LAND]->setEnabled(true);
    animations[LAND]->addTime(event.timeSinceLastFrame);
    if (animations[LAND]->hasEnded())
      stopAction(LAND);
  } else if (action[MOVE]) {
    animations[MOVE]->setEnabled(true);
    animations[MOVE]->addTime(event.timeSinceLastFrame);
  } else {
    action[IDLE] = true;
    animations[IDLE]->setEnabled(true);
    animations[IDLE]->addTime(event.timeSinceLastFrame);
  }
}

// Funtion that needs to be called every frame for the character to be updated.
void Character::move(const Ogre::FrameEvent &event) {
  using Ogre::Vector3;
  if (action[MOVE]) {
    if ( !(action[ATTACK_1] || action[ATTACK_2] || action[SPECIAL_ATTACK_1] || action[SPECIAL_ATTACK_2] || action[LAND]) ) {
      node->translate(Vector3(direction*5*event.timeSinceLastFrame,0,0));
      node->setDirection(0,0,-direction,Ogre::Node::TS_PARENT);
    }
  }
  if (action[DOUBLE_JUMP] || action[JUMP]) {
    jumping_time += event.timeSinceLastFrame;
    if (jumping_time > 1.5) {
      stopAction(JUMP);
      stopAction(DOUBLE_JUMP);
    }
    node->translate(Vector3(0,5*event.timeSinceLastFrame,0));
  } else if (!on_floor) {
    action[FALL] = true;
    node->translate(Vector3(0,-5*event.timeSinceLastFrame,0));
  }
}

// Player stops performing an action
void Character::stopAction(const int type) {
  animations[type]->setTimePosition(0);
  action[type] = false;
}

// Function to update the keyboard's state.
bool Character::keyPressed(const OIS::KeyEvent& key) {
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
bool Character::keyReleased(const OIS::KeyEvent& key) {
  if (key.key == defend_key) {
    action[DEFEND] = false;
  } else if ( (key.key == move_left_key  && direction == 1 ) || 
              (key.key == move_right_key && direction == -1)    ) {
    action[MOVE] = false;
  }
  return true;
}
