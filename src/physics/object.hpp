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
/// The physics::Object class.
/// @author Jonan

#ifndef PHYSICS_OBJECT_HPP
#define PHYSICS_OBJECT_HPP

// Bullet
#include <LinearMath/btTransform.h>

// FtS
#include <util.hpp>

// Bullet
class btCollisionShape;
class btRigidBody;

namespace physics {

class ObjectSynchronizer;
class Scene;

/// Class to create object that will be able to collide.
class Object {
public:
    Object(void); // Constructor
    virtual ~Object(void); // Destructor

    // @{
    /// Set functions.
    void setScene    (Scene *scene)         {this->scene = scene;}
    void setFriction (const Real &friction);
    // @}

    // @{
    /// Get functions.
    btRigidBody& getPhysicObject  (void) {return *physic_object;}
    Real         getVerticalSpeed (void);
    // @}

    /// Stops the object from rotating.
    void disableRotation(void);

    /// Creates a physic body for the object.
    /// @param[in] mass Object's mass.
    /// @param[in] shape Object's physical shape.
    /// @param[in] synchronizer Synchronizer used to coordinate the physic object.
    /// @param[in] center_offset Offset to the center of the object.
    void createBody(const Real &mass, btCollisionShape &shape,
                    ObjectSynchronizer *synchronizer = NULL,
                    const btTransform &center_offset = btTransform::getIdentity());

    /// Apply's a force to the object.
    void applyForce(const btVector3 &force);

    /// Move the object.
    /// @param[in] x Units to move in the x axes.
    /// @param[in] y Units to move in the y axes.
    /// @param[in] z Units to move in the z axes.
    void translate(const Real &x, const Real &y, const Real &z);

private:
    btCollisionShape *shape;
    btTransform *offset;
    btRigidBody *physic_object;

    Scene *scene;

    DISALLOW_COPY_AND_ASSIGN(Object);
};

} // namespace physics

#endif // PHYSICS_OBJECT_HPP
