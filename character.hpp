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
class Entity;
class SceneNode;
class SceneManager;
}

/// 
class Character {
  public:
    Character(Ogre::SceneManager &scene_manager); // Constructor

  private:
    Ogre::SceneNode *node;
    Ogre::Entity *entity;

    DISALLOW_COPY_AND_ASSIGN(Character);
};

#endif // CHARACTER_HPP