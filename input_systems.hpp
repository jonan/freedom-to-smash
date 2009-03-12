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
/// Variables to access all the different input systems.
/// @author Jonan

#ifndef INPUT_SYSTEMS_HPP
#define INPUT_SYSTEMS_HPP

#include <vector>

#include <OIS/OIS.h>

namespace input {

extern std::vector<bool> keyboard;
extern OIS::MouseState mouse;
extern OIS::JoyStickState joystick;

} // namespace input

#endif // INPUT_SYSTEMS_HPP
