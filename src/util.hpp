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
/// General utilities.
/// @author Jonan

#ifndef UTIL_HPP
#define UTIL_HPP

#include <OgrePrerequisites.h>

using Ogre::Real;
using Ogre::String;

/// A macro to disallow the copy constructor and operator= functions.
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

// @{
/// Maximum and minimum function templates.
template<class T> const T& maximum(const T &a, const T &b)
{
    return (a>b) ? a : b;
}
template<class T> const T& minimum(const T &a, const T &b)
{
    return (a<b) ? a : b;
}
// @}

#endif // UTIL_HPP
