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

#include <OgreRenderWindow.h>
#include <OgreRoot.h>

#include "character.hpp"
#include "input.hpp"

// Constructor
BattleGround::BattleGround(void) {
  end = false;
  // Initialize variables
  scene_manager = Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC);
  viewport = Ogre::Root::getSingleton().getAutoCreatedWindow()->addViewport(NULL);
  camera = scene_manager->createCamera("BattleGround Camera");
  camera->setPosition(Ogre::Vector3(0,0,-50));
  camera->lookAt(Ogre::Vector3(0,4,0));
  camera->setNearClipDistance(5);
  camera->setFarClipDistance(1000);
  camera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
  viewport->setCamera(camera);
  // Default settings
  scene_manager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
  scene_manager->setAmbientLight(Ogre::ColourValue(2.0,2.0,2.0));
  // Ground
  Object *ground = new Object(*scene_manager);
  ground->setEntity("cube");
  ground->setPosition(Ogre::Vector3(0,-5,0));
  ground->setScale(Ogre::Vector3(10,1,1));
  objects.push_back(ground);
  ground = new Object(*scene_manager);
  ground->setEntity("cube");
  ground->setPosition(Ogre::Vector3(-23,7,0));
  ground->setScale(Ogre::Vector3(3,0.5,1));
  objects.push_back(ground);
  ground = new Object(*scene_manager);
  ground->setEntity("cube");
  ground->setPosition(Ogre::Vector3(23,7,0));
  ground->setScale(Ogre::Vector3(3,0.5,1));
  objects.push_back(ground);
}

// Destructor
BattleGround::~BattleGround(void) {
  for (unsigned int i=0; i<objects.size(); i++)
    delete objects[i];
  for (unsigned int i=0; i<players.size(); i++)
    delete players[i];
  Input::getInstance()->removeKeyListener(this);
}

// Adds a player to the battle ground.
void BattleGround::addPlayer(const int num_player) {
  Character *player = new Character(*scene_manager, KID, num_player);
  players.push_back(player);
}

// Starts the battle.
void BattleGround::start(void) {
  Ogre::Root::getSingleton().addFrameListener(this);
  Input::getInstance()->addKeyListener(this);
  Ogre::Root::getSingleton().startRendering();
}

// Function that's called at the beginning of every frame.
bool BattleGround::frameStarted(const Ogre::FrameEvent& event) {
  for (unsigned int i=0; i<players.size(); i++) {
    players[i]->recoverFromPenetration(objects);
    players[i]->update(event);
  }
  return !end;
}

// Function to update the keyboard's state.
bool BattleGround::keyReleased(const OIS::KeyEvent& key) {
  if (key.key == OIS::KC_ESCAPE) {
    end = true;
  }
  return true;
}
