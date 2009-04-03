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

// 
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

// 
void Object::setPosition(const Ogre::Vector3 &pos) {
  node = scene_manager->getRootSceneNode()->createChildSceneNode(pos);
  node->attachObject(entity);
  node->showBoundingBox(true);
}

// 
void Object::setScale(const Ogre::Vector3 &scale) {
  node->setScale(scale);
}

// 
const Ogre::AxisAlignedBox* Object::getBoundingBox(void) {
  return &entity->getWorldBoundingBox();
}
