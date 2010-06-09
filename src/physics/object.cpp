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

// Changes the object's friction.
void Object::setFriction(const Real &friction)
{
    physic_object->setFriction(friction);
}

// Sets a velocity to the object.
void Object::setVelocity(const Real &x, const Real &y, const Real &z)
{
    physic_object->setLinearVelocity(btVector3(x,y,z));
    if (x || y || z)
        physic_object->activate();
}

// Sets the position of the object.
void Object::setPosition(const Real &x, const Real &y, const Real &z)
{
    physic_object->setWorldTransform(btTransform(btQuaternion(0,0,0,1), btVector3(x,y,z)));
    physic_object->clearForces();
    setVelocity(0,0,0);
}

// Get object's vertical speed.
Real Object::getVerticalSpeed(void)
{
    return physic_object->getVelocityInLocalPoint(offset->getOrigin()).getY();
}

// Stops the object from rotating.
void Object::disableRotation(void)
{
    physic_object->setAngularFactor(0);
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

// Apply's a force to the object.
void Object::applyForce(const btVector3 &force)
{
    physic_object->applyCentralImpulse(force);
    physic_object->activate();
}

} // namespace physics
