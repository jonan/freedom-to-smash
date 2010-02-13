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

#include "input.hpp"

#include <iostream>

#include <OgreRenderWindow.h>
#include <OgreRoot.h>

// Singleton pattern constructor
Input* Input::getInstance(void) {
  static Input instance;
  return &instance;
}

// Destructor
Input::~Input(void) {
  if (keyboard) manager->destroyInputObject(keyboard);
  if (joystick) manager->destroyInputObject(joystick);
  OIS::InputManager::destroyInputSystem(manager);
}

// Constructor
Input::Input(void) {
  setupOIS();
  if (keyboard) keyboard->setEventCallback(this);
  if (joystick) joystick->setEventCallback(this);
  Ogre::Root::getSingleton().addFrameListener(this);
}

// Setups OIS and all the input objects detected.
void Input::setupOIS(void) {
  using std::cout;
  using std::endl;

  // Give OIS the window handle OGRE is rendering in
  size_t window_handle;
  Ogre::RenderWindow *window = Ogre::Root::getSingleton().getAutoCreatedWindow();

  window->getCustomAttribute("WINDOW", &window_handle);
  manager = OIS::InputManager::createInputSystem(window_handle);

  // Setup keyboard, mouse and joystick
  try {
    cout << "Creating keyboard... ";
    keyboard = static_cast<OIS::Keyboard*>(manager->createInputObject(OIS::OISKeyboard, true));
  } catch (const OIS::Exception &exception) {
    // No keyboard
    cout << "FAILED";
    keyboard = NULL;
  }
  cout << endl;
  try {
    cout << "Creating joystick... ";
    joystick = static_cast<OIS::JoyStick*>(manager->createInputObject(OIS::OISJoyStick, true));
  } catch (const OIS::Exception &exception) {
    // No joystick
    cout << "FAILED";
    joystick = NULL;
  }
  cout << endl;
}

// Checks input after every frame.
bool Input::frameEnded(const Ogre::FrameEvent& /*event*/) {
  if (keyboard) keyboard->capture();
  if (joystick) joystick->capture();
  return true;
}

// Function to update the keyboard's state.
bool Input::keyPressed(const OIS::KeyEvent& key) {
  std::list<OIS::KeyListener*>::iterator it;
  for (it = key_listeners.begin(); it != key_listeners.end(); it++)
    (*it)->keyPressed(key);
  return true;
}

// Function to update the keyboard's state.
bool Input::keyReleased(const OIS::KeyEvent& key) {
  std::list<OIS::KeyListener*>::iterator it;
  for (it = key_listeners.begin(); it != key_listeners.end(); it++)
    (*it)->keyReleased(key);
  return true;
}
