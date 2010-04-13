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
/// The physics::CollisionScene class.
/// @author Jonan

#ifndef PHYSICS_COLLISION_SCENE_HPP
#define PHYSICS_COLLISION_SCENE_HPP

#include "util.hpp"

class btAxisSweep3;
class btCollisionDispatcher;
class btCollisionWorld;
class btDefaultCollisionConfiguration;

namespace physics {

class CollisionObject;

/// A physic scene with collision detection.
class CollisionScene {
public:
    // @{
    ///
    void addCollisionObject    (CollisionObject *obj);
    void removeCollisionObject (CollisionObject *obj);
    // @}

protected:
    CollisionScene(void); // Constructor
    ~CollisionScene(void); // Destructor

private:
    btCollisionWorld *world;

    btDefaultCollisionConfiguration *configuration;
    btCollisionDispatcher *dispatcher;
    btAxisSweep3 *broadphase;

    DISALLOW_COPY_AND_ASSIGN(CollisionScene);
};

} // namespace physics

#endif // PHYSICS_COLLISION_SCENE_HPP
