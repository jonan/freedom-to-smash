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

#include <boost/foreach.hpp>

#include <OgreRoot.h>

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
    BOOST_FOREACH(Ogre::Vector2 *p, points)
        delete p;
}

// Adds a point to where to move.
void Platform::addPoint(const Real &x, const Real &y)
{
    points.push_back(new Ogre::Vector2(x, y));
}

// Function that's called at the beginning of every frame.
bool Platform::frameStarted(const Ogre::FrameEvent &event)
{
    translate(-0.5*event.timeSinceLastFrame, 0, 0);
    return true;
}
