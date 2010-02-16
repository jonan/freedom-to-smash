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
/// The Object class.
/// @author Jonan

#ifndef ANIMATED_OBJECT_HPP
#define ANIMATED_OBJECT_HPP

#include "object.hpp"

namespace Ogre {
    class AnimationState;
}

class AnimatedObject : public Object {
public:
    AnimatedObject(Ogre::SceneManager &scene_manager); // Constructor

protected:
    // All the different states of the player
    enum {ATTACK_1, ATTACK_2, DEFEND, DOUBLE_JUMP, FALL, IDLE, JUMP,
          LAND, MOVE, SPECIAL_ATTACK_1, SPECIAL_ATTACK_2, NUM_STATES};

    void createAnimation(const int type, const char *name, const bool loop = false, const bool enabled = false);

    Ogre::AnimationState *animations[NUM_STATES];
};

#endif // ANIMATED_OBJECT_HPP
