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

/// @file
/// 
/// @author Jonan

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "macros.hpp"

namespace Ogre {
class AnimationState;
class Entity;
class FrameEvent;
class SceneNode;
class SceneManager;
}

enum action_types {ATTACK,
                   JUMP,
                   MOVE_LEFT,
                   MOVE_RIGHT,
                   NUM_ACTIONS};

/// 
class Character {
  public:
    Character(Ogre::SceneManager &scene_manager); // Constructor

    /// 
    void update(const Ogre::FrameEvent& event);

  private:
    // Types of animations
    enum {ATTACK, IDLE, JUMP, RUN, NUM_ANIMATIONS};

    // 
    void setAnimations(void);

    // 
    void checkInput(void);
    // 
    void animate(const Ogre::FrameEvent& event);

    bool action[NUM_ACTIONS]; // active actions
    bool key[NUM_ACTIONS];    // last frame input

    Ogre::SceneNode *node;
    Ogre::Entity *entity;

    Ogre::AnimationState *animations[NUM_ANIMATIONS];

    DISALLOW_COPY_AND_ASSIGN(Character);
};

#endif // CHARACTER_HPP
