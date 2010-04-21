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

#include "physics/collision_scene.hpp"
#include "graphics/graphic_scene.hpp"

/// Class to control all the graphical elements of a scene.
class Scene : protected physics::Scene, protected graphics::GraphicScene {
public:
    Scene(void); // Constructor
    ~Scene(void); // Destructor

protected:
    // Adds an object to the scene.
    virtual void addObject(const String &entity, const Ogre::Vector3 &position);

private:
    DISALLOW_COPY_AND_ASSIGN(Scene);
};

#endif // SCENE_HPP
