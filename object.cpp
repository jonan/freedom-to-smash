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

// For debug code!!!!
/*#include <Ogre.h>
#include <string>*/

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
  // Debug code!!!!!
  /*using namespace Ogre;
  std::string name1, name2, name3, name = entity->getName();
  name1 = name+"manual1";
  name2 = name+"material";
  name3 = name+"debugger";
  ManualObject* myManualObject =  scene_manager->createManualObject(name1.c_str());

  MaterialPtr myManualObjectMaterial = MaterialManager::getSingleton().create(name2.c_str(),name3.c_str());
  myManualObjectMaterial->setReceiveShadows(false);
  myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true);
  myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(0,0,1,0);
  myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(0,0,1);
  myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(0,0,1);

  myManualObject->begin("manual1Material", Ogre::RenderOperation::OT_LINE_LIST);
  myManualObject->position(min_x, min_y, 0);
  myManualObject->position(max_x, min_y, 0);
  myManualObject->position(max_x, min_y, 0);
  myManualObject->position(max_x, max_y, 0);
  myManualObject->position(max_x, max_y, 0);
  myManualObject->position(min_x, max_y, 0);
  myManualObject->position(min_x, max_y, 0);
  myManualObject->position(min_x, min_y, 0);
  myManualObject->end();

  node->attachObject(myManualObject);*/
}
