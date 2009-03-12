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

#include <Ogre.h>

#include "input_systems.hpp"

// Constructor
Character::Character(Ogre::SceneManager &scene_manager) {
  entity = scene_manager.createEntity("Kid", "kid.mesh");
  entity->setCastShadows(true);
  node = scene_manager.getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0,1,0));
  node->attachObject(entity);
  setAnimations();
  // Start with no action active
  for (int i=0; i < NUM_ACTIONS; i++) action[i] = false;
  // Define controls
  attack_key     = OIS::KC_A;
  jump_key       = OIS::KC_S;
  move_left_key  = OIS::KC_LEFT;
  move_right_key = OIS::KC_RIGHT;
}

// 
void Character::update(const Ogre::FrameEvent& event) {
  checkInput();
  animate(event);
}

// 
void Character::setAnimations(void) {
  animations[ATTACK_ANIMATION] = entity->getAnimationState("attackforward1");
  animations[ATTACK_ANIMATION]->setLoop(false);
  animations[ATTACK_ANIMATION]->setEnabled(false);
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
void Character::checkInput(void) {
  using input::keyboard;

  if (!key[ATTACK_KEY] && !action[ATTACKING] && !action[JUMPING])
    action[ATTACKING] = keyboard[attack_key];
  if (!action[ATTACKING]) {
    if (!key[JUMP_KEY] && !action[JUMPING]) action[JUMPING] = keyboard[jump_key];
    action[MOVING_LEFT ] = keyboard[move_left_key ];
    if (!keyboard[move_left_key]) action[MOVING_RIGHT] = keyboard[move_right_key];
  } else {
    action[MOVING_LEFT] = action[MOVING_RIGHT] = false;
  }

  // Store keyboard state
  key[ATTACK_KEY    ] = keyboard[attack_key    ];
  key[JUMP_KEY      ] = keyboard[jump_key      ];
  key[MOVE_LEFT_KEY ] = keyboard[move_left_key ];
  key[MOVE_RIGHT_KEY] = keyboard[move_right_key];
}

// 
void Character::animate(const Ogre::FrameEvent& event) {
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
