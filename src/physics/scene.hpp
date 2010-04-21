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
/// The physics::Scene class.
/// @author Jonan

#ifndef PHYSICS_SCENE_HPP
#define PHYSICS_SCENE_HPP

#include <list>

#include "util.hpp"

class btAxisSweep3;
class btCollisionDispatcher;
class btCollisionWorld;
class btDefaultCollisionConfiguration;

namespace physics {

#define DEBUG_PHYSIC_SHAPES 1

#if DEBUG_PHYSIC_SHAPES
class DebugDrawer;
#endif

class CollisionObject;

/// A physic scene with collision detection.
class Scene {
public:
    // @{
    ///
    void addCollisionObject    (CollisionObject *obj);
    void removeCollisionObject (CollisionObject *obj);
    // @}

    ///
    btCollisionDispatcher* getDispatcher(void) {return dispatcher;}

    ///
    void detectCollisions(void);

protected:
    Scene(void); // Constructor
    ~Scene(void); // Destructor

#if DEBUG_PHYSIC_SHAPES
    // Creates a debug drawer that draws the physic shapes.
    void createDebugDrawer(Ogre::SceneManager &scene_manager);

    // Draws the physic shapes.
    void drawDebugLines(void);
#endif

private:
    btCollisionWorld *world;
    std::list<CollisionObject*> collision_objects;

    btDefaultCollisionConfiguration *configuration;
    btCollisionDispatcher *dispatcher;
    btAxisSweep3 *broadphase;

#if DEBUG_PHYSIC_SHAPES
    DebugDrawer *debug_drawer;
#endif

    DISALLOW_COPY_AND_ASSIGN(Scene);
};

} // namespace physics

#endif // PHYSICS_SCENE_HPP
