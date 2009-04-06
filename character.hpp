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

#include <OIS/OIS.h>

#include "object.hpp"

namespace Ogre {
class AnimationState;
class Entity;
class FrameEvent;
class SceneNode;
class SceneManager;
}

enum CharacterType {KID};

/// 
class Character : public Object, public OIS::KeyListener {
  public:
    Character(Ogre::SceneManager &scene_manager, CharacterType type, const int num_player); // Constructor

    /// 
    void update(const Ogre::FrameEvent& event);

    // @{
    /// 
    virtual bool keyPressed  (const OIS::KeyEvent& key);
    virtual bool keyReleased (const OIS::KeyEvent& key);
    // @}

    /// 
    void recoverFromPenetration(Object &obj);

  private:
    // Types of animations
    enum {ATTACK_ANIMATION, FALL_ANIMATION, IDLE_ANIMATION, JUMP_ANIMATION, RUN_ANIMATION, NUM_ANIMATIONS};
    // Current action(s)
    enum {ATTACKING, FALLING, JUMPING, MOVING_LEFT, MOVING_RIGHT, NUM_ACTIONS};

    // 
    void setAnimations(void);

    // 
    void animate(const Ogre::FrameEvent &event);
    // 
    void move(const Ogre::FrameEvent &event);

    bool action[NUM_ACTIONS]; // active actions
    bool on_floor;

    Ogre::AnimationState *animations[NUM_ANIMATIONS];

    // Controls
    int attack_key, jump_key, move_left_key, move_right_key;

    DISALLOW_COPY_AND_ASSIGN(Character);
};

#endif // CHARACTER_HPP
