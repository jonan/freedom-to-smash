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

#include "platform.hpp"

#include <OgreRoot.h>
#include <OgreSceneNode.h>
#include <OgreVector2.h>
#include <OgreVector3.h>

#include "collision_box.hpp"

// Constructor
Platform::Platform(Ogre::SceneManager &scene_manager)
        : Object(scene_manager)
{
    Ogre::Root::getSingleton().addFrameListener(this);
}

// Destructor
Platform::~Platform(void)
{
    Ogre::Root::getSingleton().removeFrameListener(this);
    std::list<Ogre::Vector2*>::iterator it;
    for (it = points.begin(); it != points.end(); it++)
        delete (*it);
}

//
void Platform::addPoint(const Real &x, const Real &y)
{
    points.push_back(new Ogre::Vector2(x, y));
}

//
bool Platform::frameStarted(const Ogre::FrameEvent &event)
{
    // Move object
    node->translate(Ogre::Vector3(-0.5*event.timeSinceLastFrame,0,0));
    // Update collision box
    collision_box->setReferencePoint(*node);
    return true;
}
