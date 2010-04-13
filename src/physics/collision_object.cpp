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

#include "collision_object.hpp"

#include <btBulletCollisionCommon.h>

namespace physics {

// Constructor
CollisionObject::CollisionObject(void)
        : offset(new btTransform)
        , collision_object(new btCollisionObject)
{

}

// Desctructor
CollisionObject::~CollisionObject(void)
{
    delete offset;
    delete collision_object;
}

// Set function.
void CollisionObject::setShape(btCollisionShape &shape, const btTransform &center_offset)
{
    collision_object->setCollisionShape(&shape);
    *offset = center_offset;
}

// Detects the collision with another object.
CollisionType CollisionObject::detectCollision(const CollisionObject &obj) const
{
    return NO_COLLISION;
}

}
