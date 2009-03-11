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
}

// 
void Character::update(const Ogre::FrameEvent& event) {
  checkInput();
  animate(event);
}

// 
void Character::setAnimations(void) {
  animations[ATTACK] = entity->getAnimationState("attackforward1");
  animations[ATTACK]->setLoop(false);
  animations[ATTACK]->setEnabled(false);
  animations[IDLE] = entity->getAnimationState("idle1");
  animations[IDLE]->setLoop(true);
  animations[IDLE]->setEnabled(false);
  animations[JUMP] = entity->getAnimationState("jump1");
  animations[JUMP]->setLoop(false);
  animations[JUMP]->setEnabled(false);
  animations[RUN] = entity->getAnimationState("run1");
  animations[RUN]->setLoop(true);
  animations[RUN]->setEnabled(false);
}

// 
void Character::checkInput(void) {
  using input::keyboard;

  if (!key[::ATTACK] && !action[::ATTACK]) action[::ATTACK] = keyboard[OIS::KC_A];
  if (!key[::JUMP  ] && !action[::JUMP  ]) action[::JUMP  ] = keyboard[OIS::KC_S];

  action[::MOVE_LEFT ] = keyboard[OIS::KC_LEFT ];
  action[::MOVE_RIGHT] = keyboard[OIS::KC_RIGHT];

  key[::ATTACK    ] = keyboard[OIS::KC_A    ];
  key[::JUMP      ] = keyboard[OIS::KC_S    ];
  key[::MOVE_LEFT ] = keyboard[OIS::KC_LEFT ];
  key[::MOVE_RIGHT] = keyboard[OIS::KC_RIGHT];
}

// 
void Character::animate(const Ogre::FrameEvent& event) {
  if (action[::MOVE_LEFT] || action[::MOVE_RIGHT]) {
    animations[IDLE]->setEnabled(false);
    animations[RUN]->setEnabled(true);
    animations[RUN]->addTime(event.timeSinceLastFrame);
  } else {
    animations[RUN]->setEnabled(false);
    animations[IDLE]->setEnabled(true);
    animations[IDLE]->addTime(event.timeSinceLastFrame);
  }

  if (action[::ATTACK]) {
    animations[IDLE]->setEnabled(false);
    animations[RUN]->setEnabled(false);
    animations[ATTACK]->setEnabled(true);
    animations[ATTACK]->addTime(event.timeSinceLastFrame);
    if (animations[ATTACK]->hasEnded()) {
      animations[ATTACK]->setEnabled(false);
      animations[ATTACK]->setTimePosition(0);
      action[::ATTACK] = false;
    }
  }
  if (action[::JUMP]) {
    animations[IDLE]->setEnabled(false);
    animations[RUN]->setEnabled(false);
    animations[JUMP]->setEnabled(true);
    animations[JUMP]->addTime(event.timeSinceLastFrame);
    if (animations[JUMP]->hasEnded()) {
      animations[JUMP]->setEnabled(false);
      animations[JUMP]->setTimePosition(0);
      action[::JUMP] = false;
    }
  }
}
