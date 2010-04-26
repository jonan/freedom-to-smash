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

#include <battle_ground.hpp>

// Boost
#include <boost/foreach.hpp>
// Ogre
#include <OgreRenderWindow.h>
#include <OgreRoot.h>

// FtS
#include <character.hpp>

#ifdef USE_CAELUM
#include <caelum/Caelum.h>
#endif

#ifdef USE_HYDRAX
#include <hydrax/Hydrax.h>
#include <hydrax/Noise/Perlin/Perlin.h>
#include <hydrax/Modules/ProjectedGrid/ProjectedGrid.h>
#endif

#ifdef USE_SKYX
#include <SkyX.h>
#endif

// Constructor
BattleGround::BattleGround(void)
        :

#ifdef USE_CAELUM
        mCaelumSystem(NULL),
#endif

#ifdef USE_HYDRAX
        mHydrax(NULL),
#endif

#ifdef USE_SKYX
        mSkyX(NULL),
#endif

        end(false)
{
    // Default settings
    setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    setAmbientLight(Ogre::ColourValue(2.0,2.0,2.0));
    // Create camera
    cam_node = getManager().getRootSceneNode()->createChildSceneNode();
    int cam = addCamera("BattleGround Camera", Ogre::Vector3(0,0,-50), *cam_node);
    useCamera(cam);
    // Ground
    addObject("cube", Ogre::Vector3(0,-5,0));
    objects.back()->setScale(Ogre::Vector3(10,1,1));
    addObject("cube", Ogre::Vector3(-23,7,0));
    objects.back()->setScale(Ogre::Vector3(3,0.5,1));
    addObject("cube", Ogre::Vector3(23,7,0));
    objects.back()->setScale(Ogre::Vector3(3,0.5,1));
#if DEBUG_PHYSIC_SHAPES
    createDebugDrawer(getManager());
#endif

    // Create the sky
    createCaelumSky();

    // Create the sky
    createSkyX();

    // Create hydrax water plane
    createHydraxWater();
}


void BattleGround::createSkyX()
{
#ifdef USE_SKYX

    /* CREATE SKYX */
    mSkyX = new SkyX::SkyX(scene_manager, camera);
    mSkyX->create();
    mSkyX->getVCloudsManager()->create();
    SkyX::AtmosphereManager::Options atOpt = mSkyX->getAtmosphereManager()->getOptions();
    atOpt.RayleighMultiplier = 0.0045f;
    mSkyX->getAtmosphereManager()->setOptions(atOpt);

#endif
}


void BattleGround::createHydraxWater()
{
#ifdef USE_HYDRAX

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


void BattleGround::createCaelumSky()
{
    #ifdef USE_CAELUM

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

// Destructor
BattleGround::~BattleGround(void)
{
#ifdef USE_CAELUM
    // Destroy Caelum sky
    delete mCaelumSystem;
#endif

#ifdef USE_HYDRAX
    // Destroy Hydrax
    delete mHydrax;
#endif

    BOOST_FOREACH(Character *character, players)
        delete character;
}

// Creates a character and adds it to the battle ground.
Character* BattleGround::createCharacter(void)
{
    Character *character = new Character(getManager());
    players.push_back(character);
    physics::Scene::addCollisionObject(*character);
    return character;
}

// Starts the battle.
void BattleGround::start(void)
{
    Ogre::Root::getSingleton().addFrameListener(this);
    Ogre::Root::getSingleton().startRendering();
}

// Function that's called at the beginning of every frame.
bool BattleGround::frameStarted(const Ogre::FrameEvent &event)
{
    detectCollisions();
    Ogre::Vector3 average(0,0,0);
    BOOST_FOREACH(Character *character, players) {
        character->recoverFromPenetration(objects);
        average += character->getPosition();
    }
    average /= players.size();
    cam_node->setPosition(average);

    #ifdef USE_CAELUM
    // Update Caelum
    mCaelumSystem->notifyCameraChanged(this->camera);
    mCaelumSystem->updateSubcomponents(event.timeSinceLastFrame * 1000);
    #endif

    #ifdef USE_HYDRAX
    // Update Hydrax
    mHydrax->update(event.timeSinceLastFrame);
    #endif

    #ifdef USE_SKYX
    // Update SkyX
    mSkyX->update(event.timeSinceLastFrame);
    #endif
    return !end;
}
