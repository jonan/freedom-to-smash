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

// Set function.
void Object::createBody(const Real &mass, btCollisionShape &shape, const btTransform &center_offset)
{
    btVector3 inertia;
    shape.calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo info(mass, NULL, &shape, inertia);
    physic_object = new btRigidBody(info);
    this->shape = &shape;
    *offset = center_offset;
}

// Set function.
void Object::setPosition(const btTransform &pos)
{
    //collision_object->setWorldTransform(pos);
}

// Detects collisions with the given object.
/*int Object::detectCollision(const Object &obj) const
{
    int collision_type = NO_COLLISION;
    if (scene) {
        btPersistentManifold *contact;
        btCollisionObject *obj_0, *obj_1;
        btVector3 average,aabb_min, aabb_max;
        btCollisionDispatcher *dispatcher = &scene->getDispatcher();
        int num_manifolds = dispatcher->getNumManifolds();
        for (int i=0; i<num_manifolds; i++) {
            contact = dispatcher->getManifoldByIndexInternal(i);
            obj_0 = static_cast<btCollisionObject*>(contact->getBody0());
            obj_1 = static_cast<btCollisionObject*>(contact->getBody1());

            int obj_num = 0;
            if (obj_0 == collision_object && obj_1 == obj.collision_object)
                obj_num = 1;
            else if (obj_1 == collision_object && obj_0 == obj.collision_object)
                obj_num = 2;

            if (obj_num) {
                int num_contacts = contact->getNumContacts();
                average.setValue(0,0,0);
                for (int j=0; j<num_contacts; j++) {
                    if (obj_num==1)
                        average += contact->getContactPoint(j).m_localPointA;
                    else
                        average += contact->getContactPoint(j).m_localPointB;
                }
                average /= num_contacts;
                shape->getAabb(*offset, aabb_min, aabb_max);
                const Real half_width = (aabb_max.x() - aabb_min.x())/2;
                const Real half_height = (aabb_max.y() - aabb_min.y())/2;
                const bool up_down = half_height-abs(average.getY()) < half_width-abs(average.getX());
                if (up_down) {
                    if (average.getY() < 0)
                        collision_type |= BOTTOM_COLLISION;
                    else
                        collision_type |= TOP_COLLISION;
                } else {
                    if (average.getX() > 0)
                        collision_type |= LEFT_COLLISION;
                    else
                        collision_type |= RIGHT_COLLISION;
                }
            }
        }
    }
    return collision_type;
}*/

} // namespace physics
