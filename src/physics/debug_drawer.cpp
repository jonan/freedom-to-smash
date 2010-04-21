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

#include "debug_drawer.hpp"

// Ogre
#include <OgreManualObject.h>
#include <OgreMaterialManager.h>
#include <OgreSceneManager.h>

#include "converter_functions.hpp"

namespace physics {

// Constructor
DebugDrawer::DebugDrawer(Ogre::SceneManager &scene_manager)
        : debug_mode(DBG_DrawWireframe)
        , restart(false)
        , debug_lines(new Ogre::ManualObject("PhysicsDebugDrawer lines"))
{
  debug_lines->setDynamic(true);

  String material_name = "PhysicsDebugDrawer material";
  Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getDefaultSettings()->clone(material_name);
  material->setReceiveShadows(false);
  material->getTechnique(0)->setLightingEnabled(false);

  debug_lines->begin(material_name, Ogre::RenderOperation::OT_LINE_LIST);
  debug_lines->position(Ogre::Vector3::ZERO);
  debug_lines->colour(Ogre::ColourValue::Blue);

  scene_manager.getRootSceneNode()->attachObject(debug_lines);
}

// Destructor
DebugDrawer::~DebugDrawer(void)
{
  delete debug_lines;
}

// Draws all the stored debug lines.
void DebugDrawer::draw(void)
{
  if (debug_mode > 0) debug_lines->end();
  restart = true;
}

// Adds a new line to the drawing queue.
void DebugDrawer::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color)
{
  if (restart) {
    debug_lines->beginUpdate(0);
    restart = false;
  }
  Ogre::ColourValue colour(color.getX(), color.getY(), color.getZ());
  colour.saturate();
  debug_lines->position(vector3(from));
  debug_lines->colour(colour);
  debug_lines->position(vector3(to));
  debug_lines->colour(colour);
}

} // namespace physics
