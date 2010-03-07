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
///
/// @author Jonan

#ifndef SCENE_HPP
#define SCENE_HPP

#include <list>
#include <vector>

#include <OgreFrameListener.h>
#include <OgreLight.h>
#include <OgreSceneNode.h>

#include "macros.hpp"

namespace Ogre {
    class Camera;
    class ColourValue;
    class Vector3;
}

class Object;

///
class Scene : public Ogre::FrameListener {
public:
    Scene(void); // Constructor
    ~Scene(void); // Destructor

protected:
    // Adds an object to the scene.
    void addObject(const char *entity, const Ogre::Vector3 &position);

    // Adds a static camera.
    int addCamera(const Ogre::String &name, const Ogre::Vector3 &position,
                  const Ogre::Vector3 &look_at = Ogre::Vector3(0,0,0),
                  const unsigned int near_clip = 5, const unsigned int far_clip = 1000);
    // Adds a static camera that follows a given node.
    int addCamera(const Ogre::String &name, const Ogre::Vector3 &position,
                  Ogre::SceneNode &look_at, const unsigned int near_clip = 5,
                  const unsigned int far_clip = 1000);

    // Use the given camera.
    void useCamera(const unsigned int num_camera = 0);

    // Adds a light.
    void addLight(const Ogre::String &name, const Ogre::Vector3 &position,
                  const Ogre::Light::LightTypes &type = Ogre::Light::LT_POINT);
    // Sets the ambient light.
    void setAmbientLight(const Ogre::ColourValue &colour);

    // Sets the type of technique to use when creating the scene's shadows.
    void setShadowTechnique(const Ogre::ShadowTechnique technique);

    // This function is called at the beginnig of every frame.
    virtual bool frameStarted(const Ogre::FrameEvent &event) = 0;

    Ogre::SceneManager *manager;
    std::vector<Ogre::Camera*> camera;
    Ogre::Viewport *viewport;
    std::list<Ogre::Light*> light;

    std::list<Object*> objects;

private:
    DISALLOW_COPY_AND_ASSIGN(Scene);
};

#endif // SCENE_HPP
