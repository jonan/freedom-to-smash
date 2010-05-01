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

// Ogre
#include <OgreRenderWindow.h>
#include <OgreRoot.h>

#if USE_CAELUM
#include <caelum/Caelum.h>
#endif

#if USE_HYDRAX
#include <hydrax/Hydrax.h>
#include <hydrax/Noise/Perlin/Perlin.h>
#include <hydrax/Modules/ProjectedGrid/ProjectedGrid.h>
#endif

#if USE_SKYX
#include <SkyX.h>
#endif

namespace graphics {

// Constructor
Scene::Scene(void)

#if USE_CAELUM
        : mCaelumSystem(NULL)
#endif

#if USE_HYDRAX
        , mHydrax(NULL)
#endif

#if USE_SKYX
        , mSkyX(NULL)
#endif

{
    manager = Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC);
    viewport = Ogre::Root::getSingleton().getAutoCreatedWindow()->addViewport(NULL);

    createCaelumSky();
    createSkyX();
    createHydraxWater();
}

// Constructor
Scene::~Scene(void)
{
#if USE_CAELUM
    delete mCaelumSystem;
#endif

#if USE_HYDRAX
    delete mHydrax;
#endif
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

// Use the given camera.
void Scene::useCamera(const int num_camera) {
    camera[num_camera]->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
    viewport->setCamera(camera[num_camera]);
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

// Creates a dynamic sky using the Caelum plugin.
void Scene::createCaelumSky(void)
{
#if USE_CAELUM
    // Create the sky
    mCaelumSystem = new Caelum::CaelumSystem(Ogre::Root::getSingletonPtr(), scene_manager,
        (Caelum::CaelumSystem::CaelumComponent)(
        Caelum::CaelumSystem::CaelumComponent::CAELUM_COMPONENT_SKY_DOME
        | Caelum::CaelumSystem::CaelumComponent::CAELUM_COMPONENT_SUN
        | Caelum::CaelumSystem::CaelumComponent::CAELUM_COMPONENT_CLOUDS
        /*| Caelum::CaelumSystem::CaelumComponent::CAELUM_COMPONENT_MOON*/
        | Caelum::CaelumSystem::CaelumComponent::CAELUM_COMPONENT_IMAGE_STARFIELD
        /*| Caelum::CaelumSystem::CaelumComponent::CAELUM_COMPONENT_PRECIPITATION*/
        ));

    mCaelumSystem->setGlobalFogDensityMultiplier(0);

    // Some of the following settings seem to be supported by DX but NOT by OGL.
    // They are hence commented out for now.

    //mCaelumSystem->setSceneFogDensityMultiplier(0);
    //mCaelumSystem->setManageSceneFog(false);
    //mCamera->setFarClipDistance(100000000);
    //mCaelumSystem->setTimeScale(4000);

    //Caelum::FlatCloudLayer * clouds = mCaelumSystem->getCloudSystem()->getLayer(0);
    //clouds->setCloudCover(0.6);
    //clouds->setCloudBlendTime(1);

    //mCaelumSystem->getPrecipitationController()->createViewportInstance(viewport);
    //mCaelumSystem->getPrecipitationController()->setIntensity(0.05);
    //mCaelumSystem->getPrecipitationController()->setCameraSpeedScale(0.001);
#endif
}

// Creates an infinite water plane using the Hydrax plugin.
void Scene::createHydraxWater(void)
{
#if USE_HYDRAX
    mHydrax = new Hydrax::Hydrax(scene_manager, camera, viewport);

    Hydrax::Module::ProjectedGrid * module
        = new Hydrax::Module::ProjectedGrid(
        mHydrax,
        new Hydrax::Noise::Perlin(),
        Ogre::Plane(Ogre::Vector3(0,1,0), Ogre::Vector3(0,0,0)),
        Hydrax::MaterialManager::NM_RTT,
        Hydrax::Module::ProjectedGrid::Options());

    mHydrax->setModule(static_cast<Hydrax::Module::Module*>(module));

    mHydrax->loadCfg("HydraxDemo.hdx");

    mHydrax->create();

    mHydrax->setGlobalTransparency(0.9);


    //#ifdef USE_CAELUM
    //Ogre::MaterialPtr mat = mTerrain->getMaterial();
    //Ogre::Technique * tech = mat->createTechnique();
    //mHydrax->getMaterialManager()->addDepthTechnique(
    //	tech);
    //#endif
#endif
}

// Creates a dynamic sky using the SkyX plugin.
void Scene::createSkyX(void)
{
#if USE_SKYX
    /* CREATE SKYX */
    mSkyX = new SkyX::SkyX(scene_manager, camera);
    mSkyX->create();
    mSkyX->getVCloudsManager()->create();
    SkyX::AtmosphereManager::Options atOpt = mSkyX->getAtmosphereManager()->getOptions();
    atOpt.RayleighMultiplier = 0.0045f;
    mSkyX->getAtmosphereManager()->setOptions(atOpt);
#endif
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
