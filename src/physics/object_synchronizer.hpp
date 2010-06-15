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
/// The physics::ObjectSynchronizer class.
/// @author Jonan

#ifndef PHYSICS_OBJECT_SYNCHRONIZER_HPP
#define PHYSICS_OBJECT_SYNCHRONIZER_HPP

// Bullet
#include <LinearMath/btMotionState.h>

// FtS
#include <util.hpp>

namespace physics {

/// Class to synchronize a physic object.
class ObjectSynchronizer : public btMotionState {
public:
    ObjectSynchronizer(void); // Constructor
    virtual ~ObjectSynchronizer(void); // Destructor

    // @{
    /// Set functions.
    void setCenterOffset(const btVector3 &center_offset);
    // @}

    // @{
    /// The physics system will call this methods when convenient.
    virtual void getGraphicalPosition (Ogre::Vector3 &pos)    const = 0;
    virtual void getGraphicalRotation (Ogre::Quaternion &rot) const = 0;

    virtual void setGraphicalPosition (const Ogre::Vector3 &pos)    = 0;
    virtual void setGraphicalRotation (const Ogre::Quaternion &rot) = 0;
    // @}

private:
    // @{
    // Bullet's methods to manage the object's position.
    virtual void getWorldTransform (btTransform &transform) const;
    virtual void setWorldTransform (const btTransform &transform);
    // @}

    btVector3 *offset;

    DISALLOW_COPY_AND_ASSIGN(ObjectSynchronizer);
};

} // namespace physics

#endif // PHYSICS_OBJECT_SYNCHRONIZER_HPP
