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

#include "object.hpp"

#include <OgreEntity.h>
#include <OgreSceneManager.h>

#include "collision_box.hpp"

// Constructor
Object::Object(Ogre::SceneManager &scene_manager) {
  this->scene_manager = &scene_manager;
  collision_box = NULL;
}

// Set function.
void Object::setEntity(const char *name) {
  bool done = false;
  std::string mesh_name = name;
  mesh_name += ".mesh";
  std::string manager_name = name;
  while (!done) {
    try {
      done = true;
      manager_name += ".";
      entity = scene_manager->createEntity(manager_name, mesh_name);
    } catch (Ogre::Exception exception) {
      if (exception.getNumber() == Ogre::Exception::ERR_DUPLICATE_ITEM)
        done = false;
      else
        throw exception;
    }
  }
  entity->setCastShadows(true);
}

// Set function.
void Object::setPosition(const Ogre::Vector3 &pos) {
  node = scene_manager->getRootSceneNode()->createChildSceneNode(pos);
  node->attachObject(entity);
}

// Set function.
void Object::setScale(const Ogre::Vector3 &scale) {
  node->setScale(scale);
}

// 
void Object::setCollisionBoxSize(const double max_x, const double min_x, const double max_y, const double min_y) {
  collision_box = new CollisionBox(max_x, min_x, max_y, min_y);
  collision_box->setReferencePoint(*node);
}

// Function to get the bounding box of the object's entity.
const Ogre::AxisAlignedBox* Object::getBoundingBox(void) {
  return &entity->getWorldBoundingBox();
}
