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
/// The graphics::Scene class.
/// @author Jonan
/// @author LRG

#ifndef GRAPHICS_SCENE_HPP
#define GRAPHICS_SCENE_HPP

// C++
#include <list>
#include <vector>

// Ogre
#include <OgreLight.h>

// FtS
#include <util.hpp>

namespace Caelum {class CaelumSystem;}
namespace Hydrax {class Hydrax;      }
namespace SkyX   {class SkyX;        }

namespace graphics {

#define USE_CAELUM 0

/// Class to control all the graphical elements of a scene.
class Scene {
public:
    Scene(void); // Constructor
    virtual ~Scene(void); // Destructor

protected:
    // @{
    // Get functions.
    Ogre::SceneManager& getManager(void) {return *manager;}
    // @}

    // @{
    // Add static cameras.
    int addCamera(const String &name, const Ogre::Vector3 &position,
                  const Ogre::Vector3 &look_at = Ogre::Vector3(0,0,0),
                  const unsigned int near_clip = 5, const unsigned int far_clip = 1000);
    int addCamera(const String &name, const Ogre::Vector3 &position,
                  Ogre::SceneNode &look_at, const unsigned int near_clip = 5,
                  const unsigned int far_clip = 1000);
    // @}

    // @{
    // Add dynamic cameras.
    int addCamera(const Ogre::String &name, Ogre::SceneNode &position,
                  const Ogre::Vector3 &look_at = Ogre::Vector3(0,0,0),
                  const unsigned int near_clip = 5, const unsigned int far_clip = 1000);
    int addCamera(const Ogre::String &name, Ogre::SceneNode &position,
                  Ogre::SceneNode &look_at, const unsigned int near_clip = 5,
                  const unsigned int far_clip = 1000);
    // @}

    // Use the given camera.
    void useCamera(const int num_camera = 0);
    // Returns the active camera.
    Ogre::Camera& getCurrentCamera(void);

    // Adds a light.
    void addLight(const String &name, const Ogre::Vector3 &position,
                  const Ogre::Light::LightTypes &type = Ogre::Light::LT_POINT);
    // Sets the ambient light.
    void setAmbientLight(const Ogre::ColourValue &colour);

    // Sets the type of technique to use when creating the scene's shadows.
    void setShadowTechnique(const Ogre::ShadowTechnique technique);


    // Creates an infinite water plane.
    void createWaterPlane(void);
    // Updates the water plane.
    void updateWaterPlane(const Real &time);

    // Creates a dynamic sky.
    void createSky(void);
    // Updates the dynamic sky.
    void updateSky(const Real &time);

    // Creates a dynamic sky using the Caelum plugin.
    void createCaelumSky(void);

private:
    // Creates a static camera for the scene.
    Ogre::Camera& createCamera(const String &name, const Ogre::Vector3 &position,
                               const unsigned int near_clip, const unsigned int far_clip);

    Ogre::SceneManager *manager;
    Ogre::Viewport *viewport;
    std::vector<Ogre::Camera*> camera;
    std::list<Ogre::Light*> light;

    Hydrax::Hydrax *hydrax;
    SkyX::SkyX *skyx;

#if USE_CAELUM
    Caelum::CaelumSystem * mCaelumSystem;
#endif

    DISALLOW_COPY_AND_ASSIGN(Scene);
};

} // namespace graphics

#endif // GRAPHICS_GRAPHIC_SCENE_HPP
