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

#include <physics/object.hpp>

// Bullet
#include <btBulletDynamicsCommon.h>

// FtS
#include <physics/object_synchronizer.hpp>
#include <physics/scene.hpp>

namespace physics {

// Constructor
Object::Object(void)
        : shape(NULL)
        , offset(new btTransform)
        , physic_object(NULL)
        , scene(NULL)
{

}

// Desctructor
Object::~Object(void)
{
    if (scene) scene->removePhysicObject(*this);
    delete offset;
    delete physic_object;
}

// Creates a physic body for the object.
void Object::createBody(const Real &mass, btCollisionShape &shape,
                        ObjectSynchronizer *synchronizer,
                        const btTransform &center_offset)
{
    btVector3 inertia;
    shape.calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo info(mass, synchronizer, &shape, inertia);
    physic_object = new btRigidBody(info);
    this->shape = &shape;
    *offset = center_offset;
}

} // namespace physics
