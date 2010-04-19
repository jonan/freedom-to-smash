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

#include "battle_ground.hpp"

#include <boost/foreach.hpp>

#include <OgreRenderWindow.h>
#include <OgreRoot.h>

#include "character.hpp"

// Constructor
BattleGround::BattleGround(void)
        : end(false)
{
    // Default settings
    setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    setAmbientLight(Ogre::ColourValue(2.0,2.0,2.0));
    // Create camera
    cam_node = manager->getRootSceneNode()->createChildSceneNode();
    int cam = addCamera("BattleGround Camera", Ogre::Vector3(0,0,-50), *cam_node);
    useCamera(cam);
    // Ground
    addObject("cube", Ogre::Vector3(0,-5,0));
    objects.back()->setScale(Ogre::Vector3(10,1,1));
    addObject("cube", Ogre::Vector3(-23,7,0));
    objects.back()->setScale(Ogre::Vector3(3,0.5,1));
    addObject("cube", Ogre::Vector3(23,7,0));
    objects.back()->setScale(Ogre::Vector3(3,0.5,1));
    createDebugDrawer(*manager);
}

// Destructor
BattleGround::~BattleGround(void)
{
    BOOST_FOREACH(Character *character, players)
        delete character;
}

// Creates a character and adds it to the battle ground.
Character* BattleGround::createCharacter(void)
{
    Character *character = new Character(*manager);
    players.push_back(character);
    physics::CollisionScene::addCollisionObject(character);
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
    drawDebugLines();
    Ogre::Vector3 average;
    BOOST_FOREACH(Character *character, players) {
        character->recoverFromPenetration(objects);
        average += character->getPosition();
    }
    average /= players.size();
    cam_node->setPosition(average);
    return !end;
}
