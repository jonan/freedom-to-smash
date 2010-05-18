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
/// The gui::Gui class.
/// @author Jonan

#ifndef GUI_GUI_HPP
#define GUI_GUI_HPP

// FtS
#include <util.hpp>

namespace gui {

///
class Gui {
public:
    static Gui& getInstance(void); // Singleton pattern constructor

    // Registers the script reader.
    // Must be called before initializing the resources.
    static void registerScriptReader(void);

private:
    Gui(void); // Constructor
    ~Gui(void); // Destructor

    DISALLOW_COPY_AND_ASSIGN(Gui);
};

} // namespace gui

#endif // GUI_GUI_HPP
