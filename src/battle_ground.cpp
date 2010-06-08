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
#include <gui/gui.hpp>
#include <character.hpp>

#include <fts_evaluator.hpp>
#include <script_manager.hpp>

// Constructor
BattleGround::BattleGround(void)
        : end(false)
{
    // Default settings
    //setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    setAmbientLight(Ogre::ColourValue(1,1,1));
    // Create camera
    look_node = getManager().getRootSceneNode()->createChildSceneNode();
    cam_node = getManager().getRootSceneNode()->createChildSceneNode();
    useCamera(addCamera("BattleGround Camera", *cam_node, *look_node));

    // Ground
    addObject("cube", Ogre::Vector3(0,-5,0), Ogre::Vector3(10,1,1));
    addObject("cube", Ogre::Vector3(-23,7,0), Ogre::Vector3(3,0.5,1));
    addObject("cube", Ogre::Vector3(23,7,0), Ogre::Vector3(3,0.5,1));

    // GUI
    gui::Gui::getInstance().loadSheet("main_menu");

#if DEBUG_PHYSIC_SHAPES
    createDebugDrawer(getManager());
#endif

    bool hydrax = false, skyx = false;
    FtsEvaluator ev(ScriptManager::get().getL());
    ev.evalBool("Config.Hydrax", hydrax);
    ev.evalBool("Config.SkyX", skyx);

    if(hydrax)
        createWaterPlane();
    if(skyx)
        createSky();
}

// Destructor
BattleGround::~BattleGround(void)
{
    BOOST_FOREACH(Character *character, players)
        delete character;
}

// Creates a character and adds it to the battle ground.
Character* BattleGround::createCharacter(const String &name)
{
    Character *character = new Character(name, getManager());
    players.push_back(character);
    physics::Scene::addPhysicObject(*character);
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
    Scene::frameStarted(event);
    updateWaterPlane(event.timeSinceLastFrame);
    updateSky(event.timeSinceLastFrame);
    // Check for players out of the battle ground
    BOOST_FOREACH(Character *character, players) {
        if (character->getPosition().y < -100)
            character->reset();
    }
    // Move camera
    Ogre::Vector3 min(players.front()->getPosition());
    Ogre::Vector3 max(players.front()->getPosition());
    BOOST_FOREACH(Character *character, players) {
        if (character->getPosition().x > max.x)
            max = character->getPosition();
        else if (character->getPosition().x < min.x)
            min = character->getPosition();
    }
    Ogre::Vector3 average = (min + max) / 2;

    look_node->setPosition(average);
    cam_node->setPosition(average.x, average.y, -50);

    return !end;
}
