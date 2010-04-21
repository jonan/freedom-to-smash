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

/// @file
/// The physics::CollisionObject class.
/// @author Jonan

#ifndef PHYSICS_COLLISION_OBJECT_HPP
#define PHYSICS_COLLISION_OBJECT_HPP

#include "util.hpp"

#include <LinearMath/btTransform.h>

class btCollisionObject;
class btCollisionShape;

namespace physics {

class Scene;

/// Collisions types.
enum { NO_COLLISION     = 0    ,
       LEFT_COLLISION   = 1<<0 ,
       RIGHT_COLLISION  = 1<<1 ,
       TOP_COLLISION    = 1<<2 ,
       BOTTOM_COLLISION = 1<<3 };

/// Class to create object that will be able to collide.
class CollisionObject {
public:
    CollisionObject(void); // Constructor
    virtual ~CollisionObject(void); // Destructor

    // @{
    /// Set functions.
    void setShape(btCollisionShape &shape, const btTransform &center_offset = btTransform::getIdentity());
    void setScene(Scene *scene) {this->scene = scene;}
    void setPosition(const btTransform &pos);
    // @}

    // @{
    /// Get functions.
    btCollisionObject* getCollisionObject(void) {return collision_object;}
    // @}

    /// Detects the collision with another object.
    /// @param[in] obj Object.
    /// @return Type of collision.
    int detectCollision(const CollisionObject &obj) const;

private:
    btTransform *offset;
    btCollisionObject *collision_object;

    Scene *scene;

    DISALLOW_COPY_AND_ASSIGN(CollisionObject);
};

}

#endif // PHYSICS_COLLISION_OBJECT_HPP
