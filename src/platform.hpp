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

/// @file
/// The Platform class
/// @author Jonan

#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <OgreFrameListener.h>

#include "object.hpp"

class Character;

///
class Platform : public Object, public Ogre::FrameListener {
public:
    explicit Platform(Ogre::SceneManager &scene_manager); // Constructor
    ~Platform(void); // Destructor

    ///
    virtual ObjectType getType(void) const {return PLATFORM;}

    ///
    void addPoint(const Real &x, const Real &y);

private:
    //
    virtual bool frameStarted(const Ogre::FrameEvent &event);

    std::list<Ogre::Vector2*> points;
    std::list<Character*>     characters;

    Ogre::Vector2 *move_direction;

    DISALLOW_COPY_AND_ASSIGN(Platform);
};

#endif // PLATFORM_HPP
