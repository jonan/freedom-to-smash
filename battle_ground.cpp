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

#include "character.hpp"
#include "input_systems.hpp"

// Constructor
BattleGround::BattleGround(void) {
  // Initialize variables
  scene_manager = Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC);
  viewport = Ogre::Root::getSingleton().getAutoCreatedWindow()->addViewport(NULL);
  camera = scene_manager->createCamera("BattleGround Camera");
  camera->setPosition(Ogre::Vector3(0,5,-30));
  camera->lookAt(Ogre::Vector3(0,4,0));
  camera->setNearClipDistance(5);
  camera->setFarClipDistance(1000);
  camera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
  viewport->setCamera(camera);
  // Default settings
  scene_manager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
  scene_manager->setAmbientLight(Ogre::ColourValue(1.0,1.0,1.0));
  // Temporal addition of a player
  addPlayer();
}

// Destructor
BattleGround::~BattleGround(void) {
  for (unsigned int i=0; i<players.size(); i++)
    delete players[i];
}

// 
void BattleGround::addPlayer(void) {
  Character *player = new Character(KID, *scene_manager);
  players.push_back(player);
}

// 
void BattleGround::start(void) {
  Ogre::Root::getSingleton().addFrameListener(this);
  Ogre::Root::getSingleton().startRendering();
}

// 
bool BattleGround::frameStarted(const Ogre::FrameEvent& event) {
  for (unsigned int i=0; i<players.size(); i++)
    players[i]->update(event);
  return !input::keyboard[OIS::KC_ESCAPE];
}
