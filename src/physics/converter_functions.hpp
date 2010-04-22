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
/// Ogre-Bullet converter functions.
/// @author Jonan

#ifndef PHYSICS_CONVERTER_FUNCTIONS_HPP
#define PHYSICS_CONVERTER_FUNCTIONS_HPP

// Bullet
#include <LinearMath/btQuaternion.h>
// Ogre
#include <OgreVector3.h>

namespace physics {

// @{
/// Functions to convert between Ogre's and Bullet's types.
inline btQuaternion quaternion (const Ogre::Quaternion &q) {return btQuaternion(q.x, q.y, q.z, q.w);}
inline btVector3    vector3    (const Ogre::Vector3    &v) {return btVector3(v.x, v.y, v.z);        }

inline Ogre::Quaternion quaternion (const btQuaternion &q) {return Ogre::Quaternion(q.w(), q.x(), q.y(), q.z());}
inline Ogre::Vector3    vector3    (const btVector3    &v) {return Ogre::Vector3(v.x(), v.y(), v.z());          }
// @}

} // namespace physics

#endif // PHYSICS_CONVERTER_FUNCTIONS_HPP
