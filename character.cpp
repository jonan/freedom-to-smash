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

#include "character.hpp"

#include <Ogre.h>

// Constructor
Character::Character(Ogre::SceneManager &scene_manager) {
  entity = scene_manager.createEntity("Kid", "kid.mesh");
  entity->setCastShadows(true);
  node = scene_manager.getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0,1,0));
  node->attachObject(entity);
}
