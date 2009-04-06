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
/// The input::Input class.
/// @author Jonan

#ifndef INPUT_HPP
#define INPUT_HPP

#include <OgreFrameListener.h>

#include <OIS/OIS.h>

#include "macros.hpp"

/// 
class Input : public Ogre::FrameListener {
  public:
    static Input* getInstance(void); // Singleton pattern constructor
    ~Input(void); // Destructor

    /// Changes the listeners.
    /// @param[in] keyboard New keyboard listener.
    /// @param[in] joystick New joystick listener.
    void setListeners( OIS::KeyListener      *keyboard = NULL ,
                       OIS::JoyStickListener *joystick = NULL );

  private:
    Input(void); // Constructor

    // Setups OIS and all the input objects detected.
    void setupOIS(void);

    // Checks input after every frame.
    virtual bool frameEnded(const Ogre::FrameEvent& event);

    OIS::InputManager *manager;
    OIS::Keyboard     *keyboard;
    OIS::JoyStick     *joystick;

    DISALLOW_COPY_AND_ASSIGN(Input);
};

#endif // INPUT_HPP
