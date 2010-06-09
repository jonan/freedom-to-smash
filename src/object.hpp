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
/// The Object class.
/// @author Jonan

#ifndef OBJECT_HPP
#define OBJECT_HPP

// FtS
#include <graphics/object.hpp>
#include <physics/object.hpp>
#include <physics/object_synchronizer.hpp>

/// General object with graphic and physic properties.
class Object : public graphics::Object, public physics::Object, public physics::ObjectSynchronizer {
public:
    /// @param[in] entity Name of the object's entity.
    /// @param[in] scene_manager Manager of the scene the object will be in.
    /// @param[in] num_animations Number of animations the object has.
    explicit Object(const String &entity, Ogre::SceneManager &scene_manager, const int num_animations = 0); // Constructor
    virtual ~Object(void) {} // Destructor

    // @{
    /// Set functions.
    virtual void setPosition          (const Ogre::Vector3 &pos);
    virtual void setGraphicalPosition (const Ogre::Vector3 &pos);
    // @}

    // @{
    /// Get functions.
    virtual const Ogre::Vector3& getGraphicalPosition (void) const;
    // @}

    /// Creates the physic object that can then be added to a physic scene.
    void createPhysicObject(void);

private:
    DISALLOW_COPY_AND_ASSIGN(Object);
};

#endif // OBJECT_HPP
