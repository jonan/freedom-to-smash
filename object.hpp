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

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "macros.hpp"

namespace Ogre {
class Entity;
class SceneNode;
class SceneManager;
class Vector3;
}

class CollisionBox;

/// General object class.
class Object {
  public:
    explicit Object(Ogre::SceneManager &scene_manager); // Constructor

    // @{
    /// Set functions.
    void setEntity           (const char *name);
    void setPosition         (const Ogre::Vector3 &pos);
    void setScale            (const Ogre::Vector3 &scale);
    void setCollisionBoxSize (const double max_x, const double min_x, const double max_y, const double min_y);
    // @}

    /// 
    const CollisionBox* getCollisionBox(void) {return collision_box;}

  protected:
    Ogre::Entity *entity;
    Ogre::SceneNode *node;
    Ogre::SceneManager *scene_manager;

    CollisionBox *collision_box;

    DISALLOW_COPY_AND_ASSIGN(Object);
};

#endif // OBJECT_HPP
