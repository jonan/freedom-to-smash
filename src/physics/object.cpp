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
#include <btBulletCollisionCommon.h>

// FtS
#include <physics/scene.hpp>

namespace physics {

// Constructor
Object::Object(void)
        : offset(new btTransform)
        , collision_object(new btCollisionObject)
        , scene(NULL)
{

}

// Desctructor
Object::~Object(void)
{
    if (scene) scene->removeCollisionObject(*this);
    delete offset;
    delete collision_object;
}

// Set function.
void Object::setShape(btCollisionShape &shape, const btTransform &center_offset)
{
    collision_object->setCollisionShape(&shape);
    *offset = center_offset;
}

// Set function.
void Object::setPosition(const btTransform &pos)
{
    collision_object->setWorldTransform(pos);
}

// Detects collisions with the given object.
int Object::detectCollision(const Object &obj) const
{
    int collision_type = NO_COLLISION;
    if (scene) {
        btCollisionDispatcher *dispatcher = &scene->getDispatcher();
        int num_manifolds = dispatcher->getNumManifolds();
        btPersistentManifold *contact;
        btCollisionObject *obj_0, *obj_1;
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
                btVector3 average(0,0,0);
                for (int j=0; j<num_contacts; j++) {
                    if (obj_num==1)
                        average += contact->getContactPoint(j).m_localPointA;
                    else
                        average += contact->getContactPoint(j).m_localPointB;
                }
                if (average.getX() > 0 && abs(average.getY()) < abs(average.getX()))
                    collision_type |= LEFT_COLLISION;
                if (average.getX() < 0 && abs(average.getY()) < abs(average.getX()))
                    collision_type |= RIGHT_COLLISION;
                if (average.getY() < 0 && abs(average.getX()) < abs(average.getY()))
                    collision_type |= BOTTOM_COLLISION;
                if (average.getY() > 0 && abs(average.getX()) < abs(average.getY()))
                    collision_type |= TOP_COLLISION;
            }
        }
    }
    return collision_type;
}

} // namespace physics
