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
Object::Object(const char *entity, Ogre::SceneManager &scene_manager, const int num_animations)
        : graphics::Object(scene_manager, num_animations)
{
    if (entity)
        graphics::Object::setEntity(String(entity));
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

// Set function.
void Object::setGraphicalRotation(const Ogre::Quaternion &rot)
{
    graphics::Object::setRotation(rot);
}

// Get function.
void Object::getGraphicalPosition(Ogre::Vector3 &pos) const
{
    pos = graphics::Object::getPosition();
}

// Get function.
void Object::getGraphicalRotation(Ogre::Quaternion &rot) const
{
    rot = graphics::Object::getRotation();
}

// Creates the physic object that can then be added to a physic scene.
void Object::createPhysicObject(const Real &mass, const Ogre::Vector3 &offset, const Ogre::Vector3 &size)
{
    btVector3 physic_size;
    if (entity) {
        Ogre::AxisAlignedBox bounding_box = entity->getBoundingBox();
        physic_size = physics::vector3(bounding_box.getMaximum() - bounding_box.getMinimum());
        physic_size *= physics::vector3(node->getScale());
    } else {
        physic_size = physics::vector3(size);
    }
    btCollisionShape *shape = &physics::ShapesManager::getInstance().getBoxShape(physic_size);
    createBody(mass, *shape, this);
}
