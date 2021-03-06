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
/// The Scene class.
/// @author Jonan

#ifndef SCENE_HPP
#define SCENE_HPP

// Ogre
#include <OgreFrameListener.h>

// FtS
#include <physics/scene.hpp>
#include <graphics/scene.hpp>

// FtS
class Object;

/// Class to control the graphical and physic objects in a scene.
class Scene : protected physics::Scene, protected graphics::Scene, public Ogre::FrameListener {
public:
    Scene(void) {} // Constructor
    virtual ~Scene(void); // Destructor

protected:
    // @{
    // Adds an object to the scene.
    void addObject(const String &entity, const Ogre::Vector3 &position,
                   const Ogre::Vector3 &scale = Ogre::Vector3::ZERO, const Real &mass = 0,
                   const Ogre::Vector3 &center_offset = Ogre::Vector3::ZERO);
    void addPhysicObject(const Ogre::Vector3 &position, const Ogre::Vector3 &size, const Real &mass);
    void addGraphicObject(const char *entity, const Ogre::Vector3 &position,
                          const Ogre::Vector3 &scale = Ogre::Vector3::ZERO);
    // @}

    // This function is called at the beginnig of every frame.
    virtual bool frameStarted(const Ogre::FrameEvent &event);

private:
    std::list<Object*> objects;

    DISALLOW_COPY_AND_ASSIGN(Scene);
};

#endif // SCENE_HPP
