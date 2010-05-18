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

#include <scene.hpp>

// Boost
#include <boost/foreach.hpp>

// FtS
#include <graphics/object.hpp>
#include <object.hpp>

// Destructor
Scene::~Scene(void)
{
    BOOST_FOREACH(Object *obj, objects)
        delete obj;
}

// Adds an object to the scene.
void Scene::addObject(const String &entity, const Ogre::Vector3 &position)
{
    Object *obj = new Object(getManager());
    obj->setEntity(entity);
    obj->setPosition(position);
    physics::Scene::addCollisionObject(*obj);
    objects.push_back(obj);
}

// Function that's called at the beginning of every frame.
bool Scene::frameStarted(const Ogre::FrameEvent &event)
{
    simulate(event.timeSinceLastFrame);
    return true;
}
