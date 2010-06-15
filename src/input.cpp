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

#include <input.hpp>

// Boost
#include <boost/foreach.hpp>
// Ogre
#include <OgreRenderWindow.h>
#include <OgreRoot.h>

// Singleton pattern constructor
Input* Input::getInstance(void)
{
    static Input instance;
    return &instance;
}

// Destructor
Input::~Input(void)
{
    if (keyboard) manager->destroyInputObject(keyboard);
    if (mouse) manager->destroyInputObject(mouse);
    if (joystick) manager->destroyInputObject(joystick);
    OIS::InputManager::destroyInputSystem(manager);
}

// Constructor
Input::Input(void)
{
    setupOIS();
    if (keyboard) keyboard->setEventCallback(this);
    if (mouse) mouse->setEventCallback(this);
    if (joystick) joystick->setEventCallback(this);
    Ogre::Root::getSingleton().addFrameListener(this);
}

// Setups OIS and all the input objects detected.
void Input::setupOIS(void)
{
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
        const OIS::MouseState &mouse_state = mouse->getMouseState();
        window->getMetrics(width, height, depth, left, top);
        mouse_state.width = width;
        mouse_state.height = height;
    }
}

// Checks input after every frame.
bool Input::frameEnded(const Ogre::FrameEvent &/*event*/)
{
    if (keyboard) keyboard->capture();
    if (mouse) mouse->capture();
    if (joystick) joystick->capture();
    return true;
}

// Function to update the keyboard's state.
bool Input::keyPressed(const OIS::KeyEvent &event)
{
    BOOST_FOREACH(OIS::KeyListener *listener, key_listeners)
        listener->keyPressed(event);
    return true;
}

// Function to update the keyboard's state.
bool Input::keyReleased(const OIS::KeyEvent &event)
{
    BOOST_FOREACH(OIS::KeyListener *listener, key_listeners)
        listener->keyReleased(event);
    return true;
}

// Functions to update the mouse's state.
bool Input::mouseMoved(const OIS::MouseEvent &event)
{
    BOOST_FOREACH(OIS::MouseListener *listener, mouse_listeners)
        listener->mouseMoved(event);
    return true;
}

// Functions to update the mouse's state.
bool Input::mousePressed(const OIS::MouseEvent &event, OIS::MouseButtonID key)
{
    BOOST_FOREACH(OIS::MouseListener *listener, mouse_listeners)
        listener->mousePressed(event, key);
    return true;
}

// Functions to update the mouse's state.
bool Input::mouseReleased(const OIS::MouseEvent &event, OIS::MouseButtonID key)
{
    BOOST_FOREACH(OIS::MouseListener *listener, mouse_listeners)
        listener->mouseReleased(event, key);
    return true;
}
