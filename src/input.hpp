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
/// The Input class.
/// @author Jonan

#ifndef INPUT_HPP
#define INPUT_HPP

// Ogre
#include <OgreFrameListener.h>
// OIS
#include <OIS/OIS.h>

// FtS
#include <util.hpp>

/// Class to control all input and who is listening to it.
/// @todo Add joystick support.
class Input : public Ogre::FrameListener, public OIS::KeyListener, public OIS::JoyStickListener {
public:
    static Input* getInstance(void); // Singleton pattern constructor
    ~Input(void); // Destructor

    // @{
    /// Functions to add listeners.
    void addKeyListener      (OIS::KeyListener &listener)      {key_listeners.push_back(&listener);     }
    void addJoyStickListener (OIS::JoyStickListener &listener) {joystick_listeners.push_back(&listener);}
    // @}

    // @{
    /// Functions to remove listeners.
    void removeKeyListener      (OIS::KeyListener &listener)      {key_listeners.remove(&listener);     }
    void removeJoyStickListener (OIS::JoyStickListener &listener) {joystick_listeners.remove(&listener);}
    // @}

private:
    Input(void); // Constructor

    // Setups OIS and all the input objects detected.
    void setupOIS(void);

    // Checks input after every frame.
    virtual bool frameEnded(const Ogre::FrameEvent &event);

    // @{
    // Functions to update the keyboard's state.
    virtual bool keyPressed  (const OIS::KeyEvent &key);
    virtual bool keyReleased (const OIS::KeyEvent &key);
    // @}

    // @{
    // Joystick not yet supported.
    virtual bool buttonPressed  (const OIS::JoyStickEvent&, int) {return true;}
    virtual bool buttonReleased (const OIS::JoyStickEvent&, int) {return true;}
    virtual bool axisMoved      (const OIS::JoyStickEvent&, int) {return true;}
    // @}

    OIS::InputManager *manager;
    OIS::Keyboard     *keyboard;
    OIS::JoyStick     *joystick;

    std::list<OIS::KeyListener*>      key_listeners;
    std::list<OIS::JoyStickListener*> joystick_listeners;

    DISALLOW_COPY_AND_ASSIGN(Input);
};

#endif // INPUT_HPP
