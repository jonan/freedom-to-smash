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
/// The Menu class.
/// @author Jonan

#ifndef MENU_HPP
#define MENU_HPP

// Ogre
#include <OgreFrameListener.h>

// FtS
#include <graphics/scene.hpp>

namespace QuickGUI {class EventArgs;}

///
class Menu : public graphics::Scene, public Ogre::FrameListener {
public:
    Menu(void); // Constructor
    virtual ~Menu(void) {} // Destructor

    ///
    void start(void);
    ///
    void exit(const QuickGUI::EventArgs& /*args*/) {end = true;}

private:
    // This function is called at the beginnig of every frame.
    virtual bool frameStarted(const Ogre::FrameEvent &event);

    bool end;

    DISALLOW_COPY_AND_ASSIGN(Menu);
};

#endif // MENU_HPP
