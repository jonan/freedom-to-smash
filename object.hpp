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

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "macros.hpp"

namespace Ogre {
class AxisAlignedBox;
class Entity;
class SceneNode;
class SceneManager;
class Vector3;
}

/// 
class Object {
  public:
    Object(Ogre::SceneManager &scene_manager) : scene_manager(&scene_manager) {} // Constructor

    // @{
    /// 
    void setEntity   (const char *name);
    void setPosition (const Ogre::Vector3 &pos);
    void setScale    (const Ogre::Vector3 &scale);
    // @}

    /// 
    const Ogre::AxisAlignedBox* getBoundingBox(void);

  protected:
    Ogre::Entity *entity;
    Ogre::SceneNode *node;
    Ogre::SceneManager *scene_manager;

    DISALLOW_COPY_AND_ASSIGN(Object);
};

#endif // OBJECT_HPP
