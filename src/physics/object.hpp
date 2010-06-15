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

// FtS
#include <util.hpp>

// Bullet
class btCollisionShape;
class btRigidBody;
class btVector3;

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
    void setScene    (Scene *scene) {this->scene = scene;}
    void setFriction (const Real &friction);
    void setVelocity (const Real &x, const Real &y, const Real &z = 0);
    void setPosition (const Real &x, const Real &y, const Real &z = 0);
    // @}

    // @{
    /// Get functions.
    btRigidBody&       getPhysicObject  (void) {return *physic_object;}
    const btVector3&   getVelocity      (void) const;
    // @}

    /// Stops the object from rotating.
    void disableRotation(void);

    /// Creates a physic body for the object.
    /// @param[in] mass Object's mass.
    /// @param[in] shape Object's physical shape.
    /// @param[in] synchronizer Synchronizer used to coordinate the physic object.
    void createBody(const Real &mass, btCollisionShape &shape,
                    ObjectSynchronizer &synchronizer);

    /// Apply's a force to the object.
    void applyForce(const btVector3 &force);

private:
    btCollisionShape *shape;
    btRigidBody *physic_object;

    Scene *scene;

    DISALLOW_COPY_AND_ASSIGN(Object);
};

} // namespace physics

#endif // PHYSICS_OBJECT_HPP
