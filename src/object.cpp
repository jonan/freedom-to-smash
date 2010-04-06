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

/*
// For debug code!
#include <Ogre.h>
#include <string>
*/

#include "collision_box.hpp"

// Constructor
Object::Object(Ogre::SceneManager &scene_manager)
        : entity(NULL)
        , scene_manager(&scene_manager)
        , collision_box(new CollisionBox)
{
    node = scene_manager.getRootSceneNode()->createChildSceneNode();
}

// Destructor
Object::~Object(void)
{
    delete collision_box;
}

// Set function.
void Object::setEntity(const String &name)
{
    entity = createEntity(name);
    node->attachObject(entity);
}

// Set function.
void Object::setPosition(const Ogre::Vector3 &pos)
{
    node->setPosition(pos);
}

// Set function.
void Object::setScale(const Ogre::Vector3 &scale)
{
    node->setScale(scale);
}

// Set function.
void Object::setCollisionBoxSize(const Real max_x, const Real min_x, const Real max_y, const Real min_y)
{
    collision_box->setRelativeBoxPos(max_x, min_x, max_y, min_y);
    collision_box->setReferencePoint(*node);
    /*
    // Debug code!
    using namespace Ogre;
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

    node->attachObject(myManualObject);
    */
}

// Get function.
const Ogre::Vector3& Object::getPosition(void)
{
    return node->getPosition();
}

// Move the object.
void Object::translate(const Real x, const Real y, const Real z)
{
    // Move object
    node->translate(x, y, z);
    // Update collision box
    collision_box->setReferencePoint(*node);
}

// Creates a new entity and returns a pointer to it.
Ogre::Entity* Object::createEntity(const String &name)
{
    bool done = false;
    Ogre::Entity *entity;
    String mesh_name = name;
    mesh_name += ".mesh";
    String manager_name = name;
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
    return entity;
}
