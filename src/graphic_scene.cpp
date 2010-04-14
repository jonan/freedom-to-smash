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

#include "graphic_scene.hpp"

#include <boost/foreach.hpp>

#include <OgreRenderWindow.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreViewport.h>

#include "object.hpp"

// Constructor
GraphicScene::GraphicScene(void)
{
    manager = Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC);
    viewport = Ogre::Root::getSingleton().getAutoCreatedWindow()->addViewport(NULL);
}

// Destructor
GraphicScene::~GraphicScene(void)
{
    BOOST_FOREACH(Object *obj, objects)
        delete obj;
}

// Adds an object to the scene.
void GraphicScene::addObject(const String &entity, const Ogre::Vector3 &position)
{
    Object *obj = new Object(*manager);
    obj->setEntity(entity);
    obj->setPosition(position);
    objects.push_back(obj);
}

// Adds a static camera.
int GraphicScene::addCamera(const Ogre::String &name, const Ogre::Vector3 &position,
                            const Ogre::Vector3 &look_at,
                            const unsigned int near_clip, const unsigned int far_clip)
{
    Ogre::Camera *cam = createCamera(name, position, near_clip, far_clip);
    cam->lookAt(look_at);

    return camera.size()-1;
}

// Adds a static camera that follows a given node.
int GraphicScene::addCamera(const Ogre::String &name, const Ogre::Vector3 &position,
                            Ogre::SceneNode &look_at, const unsigned int near_clip,
                            const unsigned int far_clip)
{
    Ogre::Camera *cam = createCamera(name, position, near_clip, far_clip);
    cam->setAutoTracking(true, &look_at);

    return camera.size()-1;
}

// Use the given camera.
void GraphicScene::useCamera(const int num_camera) {
    camera[num_camera]->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
    viewport->setCamera(camera[num_camera]);
}

// Adds a light.
void GraphicScene::addLight(const Ogre::String &name, const Ogre::Vector3 &position,
                     const Ogre::Light::LightTypes &type)
{
    light.push_back(manager->createLight(name));
    light.back()->setPosition(position);
    light.back()->setType(type);
}

// Sets the ambient light.
void GraphicScene::setAmbientLight(const Ogre::ColourValue &colour)
{
    manager->setAmbientLight(colour);
}

// Sets the type of technique to use when creating the scene's shadows.
void GraphicScene::setShadowTechnique(const Ogre::ShadowTechnique technique)
{
    manager->setShadowTechnique(technique);
}

// Creates a camera for the scene.
Ogre::Camera* GraphicScene::createCamera(const Ogre::String &name, const Ogre::Vector3 &position,
                                         const unsigned int near_clip, const unsigned int far_clip)
{
    Ogre::Camera *cam = manager->createCamera(name);
    cam->setPosition(position);
    cam->setNearClipDistance(near_clip);
    cam->setFarClipDistance(far_clip);
    cam->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
    camera.push_back(cam);

    return cam;
}
