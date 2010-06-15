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

// Ogre
#include <OgreVector3.h>

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
    explicit Object(const char *entity, Ogre::SceneManager &scene_manager, const int num_animations = 0); // Constructor
    virtual ~Object(void) {} // Destructor

    // @{
    /// Set functions.
    virtual void setPosition          (const Ogre::Vector3 &pos);
    virtual void setGraphicalPosition (const Ogre::Vector3 &pos);
    virtual void setGraphicalRotation (const Ogre::Quaternion &rot);
    // @}

    // @{
    /// Get functions.
    virtual void getGraphicalPosition (Ogre::Vector3 &pos)    const;
    virtual void getGraphicalRotation (Ogre::Quaternion &rot) const;
    // @}

    /// Creates the physic object that can then be added to a physic scene.
    /// @param[in] mass The object's mass.
    /// @param[in] center_offset Offset between the center of the physic object and the graphical position.
    /// @param[in] size Size of the physic object (only needed when the object has no entity).
    void createPhysicObject(const Real &mass,
                            const Ogre::Vector3 &center_offset = Ogre::Vector3::ZERO,
                            const Ogre::Vector3 &size = Ogre::Vector3::ZERO);

private:
    DISALLOW_COPY_AND_ASSIGN(Object);
};

#endif // OBJECT_HPP
