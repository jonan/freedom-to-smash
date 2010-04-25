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

#include <object.hpp>

// Ogre
#include <Ogre.h>

// FtS
#include <physics/converter_functions.hpp>
#include <physics/shapes_manager.hpp>

// Constructor
Object::Object(Ogre::SceneManager &scene_manager, const int num_animations)
        : graphics::Object(scene_manager, num_animations)
{

}

// Set function.
void Object::setEntity(const String &name)
{
    graphics::Object::setEntity(name);
    // Create a physic shape from the entity's bounding box
    Ogre::AxisAlignedBox bounding_box = entity->getBoundingBox();
    btVector3 size = physics::vector3(bounding_box.getMaximum() - bounding_box.getMinimum());
    btCollisionShape *shape = &physics::ShapesManager::getInstance().getBoxShape(size);
    setShape(*shape);
}

// Set function.
void Object::setPosition(const Ogre::Vector3 &pos)
{
    graphics::Object::setPosition(pos);
    physics::Object::setPosition(btTransform(btQuaternion(0,0,0,1), btVector3(pos.x, pos.y, pos.z)));
}

// Set function.
void Object::setScale(const Ogre::Vector3 &scale)
{
    graphics::Object::setScale(scale);
    // Update the physic shape
    Ogre::AxisAlignedBox bounding_box = entity->getBoundingBox();
    btVector3 size = physics::vector3(bounding_box.getMaximum() - bounding_box.getMinimum());
    size *= physics::vector3(scale);
    btCollisionShape *shape = &physics::ShapesManager::getInstance().getBoxShape(size);
    setShape(*shape);
}

// Move the object.
void Object::translate(const Real &x, const Real &y, const Real &z)
{
    graphics::Object::translate(x, y, z);
    physics::Object::setPosition(btTransform(btQuaternion(0,0,0,1), physics::vector3(node->getPosition())));
}
