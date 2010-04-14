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

#include "physics/converter_functions.hpp"
#include "physics/shapes_manager.hpp"

// Constructor
Object::Object(Ogre::SceneManager &scene_manager)
        : entity(NULL)
        , scene_manager(&scene_manager)
{
    node = scene_manager.getRootSceneNode()->createChildSceneNode();
}

// Destructor
Object::~Object(void)
{

}

// Set function.
void Object::setEntity(const String &name)
{
    entity = createEntity(name);
    node->attachObject(entity);
    // Create a physic shape from the entity's bounding box
    Ogre::AxisAlignedBox bounding_box = entity->getWorldBoundingBox();
    btVector3 size = physics::vector3(bounding_box.getMaximum() - bounding_box.getMinimum());
    btCollisionShape *shape = physics::ShapesManager::getInstance()->getBoxShape(size);
    setShape(*shape);
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

// Get function.
const Ogre::Vector3& Object::getPosition(void) const
{
    return node->getPosition();
}

// Move the object.
void Object::translate(const Real &x, const Real &y, const Real &z)
{
    node->translate(x, y, z);
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
