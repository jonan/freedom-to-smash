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
/// The boot and quit functions.
/// @author Jonan

#ifndef BOOT_HPP
#define BOOT_HPP

/// Loads all the necessary things for the game to run.
/// It has to be called first thing in the program.
void boot(void);
/// Shuts down all the systems and frees memory.
/// It has to be called last thing in the program.
void quit(void);

//! Runs the config script and parses it.
//! As of now, the config script doesn't have much use other than
//! testing the DDL system.
void HandleConfigScript();

#endif // BOOT_HPP
