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

#include "scene.hpp"

#include <btBulletCollisionCommon.h>

#include "collision_object.hpp"
#if DEBUG_PHYSIC_SHAPES
#include "debug_drawer.hpp"
#endif

namespace physics {

// Constructor
Scene::Scene(void)
        : configuration(new btDefaultCollisionConfiguration)
        , dispatcher(new btCollisionDispatcher(configuration))
#if DEBUG_PHYSIC_SHAPES
        , debug_drawer(NULL)
#endif
{
    broadphase = new btAxisSweep3(btVector3(-1000,-1000,-1000), btVector3(1000,1000,1000));
    world = new btCollisionWorld(dispatcher, broadphase, configuration);
}

// Destructor
Scene::~Scene(void) {
    while (!collision_objects.empty())
        removeCollisionObject(collision_objects.front());
    delete world;
    delete broadphase;
    delete dispatcher;
    delete configuration;
#if DEBUG_PHYSIC_SHAPES
    delete debug_drawer;
#endif
}

#if DEBUG_PHYSIC_SHAPES
// Creates a debug drawer that draws the physic shapes.
void Scene::createDebugDrawer(Ogre::SceneManager &scene_manager)
{
    if (!debug_drawer) {
        debug_drawer = new DebugDrawer(scene_manager);
        world->setDebugDrawer(debug_drawer);
    }
}

// Draws the physic shapes.
void Scene::drawDebugLines(void)
{
    if (debug_drawer) {
        world->debugDrawWorld();
        debug_drawer->draw();
    }
}
#endif

// Add an objects to the scene.
void Scene::addCollisionObject(CollisionObject *obj)
{
    obj->setScene(this);
    world->addCollisionObject(obj->getCollisionObject());
    collision_objects.push_back(obj);
}

// Remove an objects from the scene.
void Scene::removeCollisionObject(CollisionObject *obj)
{
    obj->setScene(NULL);
    world->removeCollisionObject(obj->getCollisionObject());
    collision_objects.remove(obj);
}

// Detects all the collisions between the objects in the scene.
void Scene::detectCollisions(void)
{
    world->performDiscreteCollisionDetection();
#if DEBUG_PHYSIC_SHAPES
    drawDebugLines();
#endif
}

} // namespace physics
