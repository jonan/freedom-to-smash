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

#include <graphics/scene.hpp>

// Ogre
#include <OgreRenderWindow.h>
#include <OgreRoot.h>
// Hydrax
#include <hydrax/Hydrax.h>
#include <hydrax/Noise/Perlin/Perlin.h>
#include <hydrax/Modules/ProjectedGrid/ProjectedGrid.h>
// SkyX
#include <skyx/SkyX.h>

namespace graphics {

// Constructor
Scene::Scene(void)
        : hydrax(NULL)
        , skyx(NULL)
{
    manager = Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC);
    viewport = Ogre::Root::getSingleton().getAutoCreatedWindow()->addViewport(NULL);
}

// Constructor
Scene::~Scene(void)
{
    delete hydrax;
    delete skyx;
}

// Adds a static camera.
int Scene::addCamera(const Ogre::String &name, const Ogre::Vector3 &position,
                     const Ogre::Vector3 &look_at,
                     const unsigned int near_clip, const unsigned int far_clip)
{
    Ogre::Camera *cam = &createCamera(name, position, near_clip, far_clip);
    cam->lookAt(look_at);

    return camera.size()-1;
}

// Adds a static camera that follows a given node.
int Scene::addCamera(const Ogre::String &name, const Ogre::Vector3 &position,
                     Ogre::SceneNode &look_at, const unsigned int near_clip,
                     const unsigned int far_clip)
{
    Ogre::Camera *cam = &createCamera(name, position, near_clip, far_clip);
    cam->setAutoTracking(true, &look_at);

    return camera.size()-1;
}

// Adds a dynamic camera.
int Scene::addCamera(const Ogre::String &name, Ogre::SceneNode &position,
                     const Ogre::Vector3 &look_at,
                     const unsigned int near_clip, const unsigned int far_clip)
{
    addCamera(name, Ogre::Vector3(0,0,0), look_at, near_clip, far_clip);
    position.attachObject(camera.back());
    return camera.size()-1;
}

// Adds a dynamic camera that follows a given node.
int Scene::addCamera(const Ogre::String &name, Ogre::SceneNode &position,
                     Ogre::SceneNode &look_at, const unsigned int near_clip,
                     const unsigned int far_clip)
{
    addCamera(name, Ogre::Vector3(0,0,0), look_at, near_clip, far_clip);
    position.attachObject(camera.back());
    return camera.size()-1;
}

// Use the given camera.
void Scene::useCamera(const int num_camera)
{
    camera[num_camera]->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
    viewport->setCamera(camera[num_camera]);
}

// Returns the active camera.
Ogre::Camera& Scene::getCurrentCamera(void)
{
    return *viewport->getCamera();
}

// Adds a light.
void Scene::addLight(const Ogre::String &name, const Ogre::Vector3 &position,
                     const Ogre::Light::LightTypes &type)
{
    light.push_back(manager->createLight(name));
    light.back()->setPosition(position);
    light.back()->setType(type);
}

// Sets the ambient light.
void Scene::setAmbientLight(const Ogre::ColourValue &colour)
{
    manager->setAmbientLight(colour);
}

// Sets the type of technique to use when creating the scene's shadows.
void Scene::setShadowTechnique(const Ogre::ShadowTechnique technique)
{
    manager->setShadowTechnique(technique);
}

// Creates an infinite water plane.
void Scene::createWaterPlane(void)
{
    hydrax = new Hydrax::Hydrax(manager, &getCurrentCamera(), viewport);

    Hydrax::Module::ProjectedGrid *module
            = new Hydrax::Module::ProjectedGrid(
                    hydrax,
                    new Hydrax::Noise::Perlin(),
                    Ogre::Plane(Ogre::Vector3(0,1,0),
                                Ogre::Vector3(0,0,0)),
                    Hydrax::MaterialManager::NM_RTT,
                    Hydrax::Module::ProjectedGrid::Options());

    hydrax->setModule(static_cast<Hydrax::Module::Module*>(module));
    hydrax->loadCfg("HydraxDemo.hdx");
    hydrax->create();
    hydrax->setGlobalTransparency(0.9);
}

// Updates the water plane.
void Scene::updateWaterPlane(const Real &time)
{
    if (hydrax) hydrax->update(time);
}

// Creates a dynamic sky.
void Scene::createSky(void)
{
    skyx = new SkyX::SkyX(manager, &getCurrentCamera());
    skyx->create();
    skyx->getVCloudsManager()->create();
    SkyX::AtmosphereManager::Options options = skyx->getAtmosphereManager()->getOptions();
    options.RayleighMultiplier = 0.0045f;
    skyx->getVCloudsManager()->setWindSpeed(80);

    skyx->getAtmosphereManager()->setOptions(options);
}

// Updates the dynamic sky.
void Scene::updateSky(const Real &time)
{
    if (skyx) skyx->update(time);
}

// Creates a static camera for the scene.
Ogre::Camera& Scene::createCamera(const String &name, const Ogre::Vector3 &position,
                                  const unsigned int near_clip, const unsigned int far_clip)
{
    Ogre::Camera *cam = manager->createCamera(name);
    cam->setPosition(position);
    cam->setNearClipDistance(near_clip);
    cam->setFarClipDistance(far_clip);
    cam->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
    camera.push_back(cam);

    return *cam;
}

} // namespace graphics
