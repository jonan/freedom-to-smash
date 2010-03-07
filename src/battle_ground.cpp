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
#include "input.hpp"

// Constructor
BattleGround::BattleGround(void)
        : end(false)
{
    // Default settings
    setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    setAmbientLight(Ogre::ColourValue(2.0,2.0,2.0));
    // Create camera
    int cam = addCamera("BattleGround Camera", Ogre::Vector3(0,0,-50), Ogre::Vector3(0,4,0));
    useCamera(cam);
    // Ground
    Object *ground = new Object(*manager);
    ground->setEntity("cube");
    ground->setPosition(Ogre::Vector3(0,-5,0));
    ground->setScale(Ogre::Vector3(10,1,1));
    ground->setCollisionBoxSize(25,-25,2.5,-2.5);
    objects.push_back(ground);
    ground = new Object(*manager);
    ground->setEntity("cube");
    ground->setPosition(Ogre::Vector3(-23,7,0));
    ground->setScale(Ogre::Vector3(3,0.5,1));
    ground->setCollisionBoxSize(7.5,-7.5,1.25,-1.25);
    objects.push_back(ground);
    ground = new Object(*manager);
    ground->setEntity("cube");
    ground->setPosition(Ogre::Vector3(23,7,0));
    ground->setScale(Ogre::Vector3(3,0.5,1));
    ground->setCollisionBoxSize(7.5,-7.5,1.25,-1.25);
    objects.push_back(ground);
}

// Destructor
BattleGround::~BattleGround(void)
{
    Input::getInstance()->removeKeyListener(*this);
    BOOST_FOREACH(Object *obj, objects)
        delete obj;
    BOOST_FOREACH(Character *character, players)
        delete character;
}

// Adds a player to the battle ground.
void BattleGround::addPlayer(const int num_player)
{
    players.push_back(new Character(*manager, KID, num_player));
}

// Starts the battle.
void BattleGround::start(void)
{
    Ogre::Root::getSingleton().addFrameListener(this);
    Input::getInstance()->addKeyListener(*this);
    Ogre::Root::getSingleton().startRendering();
}

// Function that's called at the beginning of every frame.
bool BattleGround::frameStarted(const Ogre::FrameEvent &event)
{
    BOOST_FOREACH(Character *character, players)
        character->recoverFromPenetration(objects);
    return !end;
}

// Function to update the keyboard's state.
bool BattleGround::keyReleased(const OIS::KeyEvent &key)
{
    if (key.key == OIS::KC_ESCAPE)
        end = true;
    return true;
}
