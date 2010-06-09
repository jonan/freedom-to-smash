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
Object::Object(const String &entity, Ogre::SceneManager &scene_manager, const int num_animations)
        : graphics::Object(scene_manager, num_animations)
{
    graphics::Object::setEntity(entity);
}

// Set function.
void Object::setPosition(const Ogre::Vector3 &pos)
{
    physics::Object::setPosition(pos.x, pos.y, pos.z);
}

// Set function.
void Object::setGraphicalPosition(const Ogre::Vector3 &pos)
{
    graphics::Object::setPosition(pos);
}

// Get function.
const Ogre::Vector3& Object::getGraphicalPosition(void) const
{
    return graphics::Object::getPosition();
}

// Creates the physic object that can then be added to a physic scene.
void Object::createPhysicObject(void)
{
    Ogre::AxisAlignedBox bounding_box = entity->getBoundingBox();
    btVector3 size = physics::vector3(bounding_box.getMaximum() - bounding_box.getMinimum());
    size *= physics::vector3(node->getScale());
    btCollisionShape *shape = &physics::ShapesManager::getInstance().getBoxShape(size);
    createBody(0, *shape, this);
}
