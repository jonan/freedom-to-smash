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

#include "input_systems.hpp"

namespace input {

// Declare the input systems
bool keyboard[238];
OIS::MouseState mouse;
OIS::JoyStickState joystick;

// Singleton pattern constructor
Input* Input::getInstance(void) {
  static Input instance;
  return &instance;
}

// Destructor
Input::~Input(void) {
  if (keyboard) manager->destroyInputObject(keyboard);
  if (mouse) manager->destroyInputObject(mouse);
  if (joystick) manager->destroyInputObject(joystick);
  OIS::InputManager::destroyInputSystem(manager);
  // Delete the Ogre Root object here because it needs to me deleted after the mouse.
  delete Ogre::Root::getSingletonPtr();
}

// Changes the listeners.
void Input::setListeners(OIS::KeyListener *keyboard,
                         OIS::MouseListener *mouse,
                         OIS::JoyStickListener *joystick
                        ) {
  if (this->keyboard) this->keyboard->setEventCallback(keyboard);
  if (this->mouse) this->mouse->setEventCallback(mouse);
  if (this->joystick) this->joystick->setEventCallback(joystick);
}

// Constructor
Input::Input(void) {
  for (int i=0; i<238; i++) input::keyboard[i] = false;
  setupOIS();
  setListeners(this);
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
    cout << "Creating mouse... ";
    mouse = static_cast<OIS::Mouse*>(manager->createInputObject(OIS::OISMouse, true));
  } catch (const OIS::Exception &exception) {
    // No mouse
    cout << "FAILED";
    mouse = NULL;
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
  // Tell OIS the dimensions of the window (only needed when using mouse)
  if (mouse) {
    unsigned int width, height, depth;
    int left, top;
    const OIS::MouseState& mouse_state = mouse->getMouseState();
    window->getMetrics(width, height, depth, left, top);
    mouse_state.width = width;
    mouse_state.height = height;
  }
}

// Updates variables when a key is pressed.
bool Input::keyPressed(const OIS::KeyEvent& key) {
  input::keyboard[key.key]=true;
  return true;
}

// Updates variables when a key is released.
bool Input::keyReleased(const OIS::KeyEvent& key) {
  input::keyboard[key.key]=false;
  return true;
}

// Checks input after every frame.
bool Input::frameEnded(const Ogre::FrameEvent& /*event*/) {
  if (keyboard) keyboard->capture();
  if (mouse) {
    mouse->capture();
    input::mouse = mouse->getMouseState();
  }
  if (joystick) {
    joystick->capture();
    input::joystick = joystick->getJoyStickState();
  }
  return true;
}

} // namespace input
