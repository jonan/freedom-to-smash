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

// C++
#include <list>

// FtS
#include <util.hpp>

// Bullet
class btBroadphaseInterface;
class btCollisionDispatcher;
class btDefaultCollisionConfiguration;
class btDiscreteDynamicsWorld;
class btSequentialImpulseConstraintSolver;

namespace physics {

#define DEBUG_PHYSIC_SHAPES 0

class Object;
#if DEBUG_PHYSIC_SHAPES
class DebugDrawer;
#endif

/// A physic scene with collision detection.
class Scene {
public:
    Scene(void); // Constructor
    virtual ~Scene(void); // Destructor

#if DEBUG_PHYSIC_SHAPES
    /// Creates a debug drawer that draws the physic shapes.
    /// @param[in] scene_manager The SceneManager where to draw.
    void createDebugDrawer(Ogre::SceneManager &scene_manager);

    /// Draws the physic shapes.
    void drawDebugLines(void);
#endif

    // @{
    /// Add or remove objects from the scene.
    void addPhysicObject    (Object &obj);
    void removePhysicObject (Object &obj);
    // @}

    // @{
    /// Get functions.
    btCollisionDispatcher& getDispatcher(void) {return *dispatcher;}
    // @}

    /// Detects all the collisions between the objects in the scene.
    void detectCollisions(void);

    /// Steps the physic simulation.
    /// @param time Time to step.
    void simulate(const Real &time);

private:
    btDiscreteDynamicsWorld *world;
    std::list<Object*> physic_objects;

    btDefaultCollisionConfiguration *configuration;
    btCollisionDispatcher *dispatcher;
    btBroadphaseInterface *broadphase;
    btSequentialImpulseConstraintSolver *solver;

#if DEBUG_PHYSIC_SHAPES
    DebugDrawer *debug_drawer;
#endif

    DISALLOW_COPY_AND_ASSIGN(Scene);
};

} // namespace physics

#endif // PHYSICS_SCENE_HPP
