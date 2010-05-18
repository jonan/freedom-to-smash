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

#include <gui/gui.hpp>

// QuickGUI
#include <QuickGUI.h>

namespace gui {

    // Singleton pattern constructor
Gui& Gui::getInstance(void)
{
    static Gui instance;
    return instance;
}

// Registers the script reader.
void Gui::registerScriptReader(void)
{
    QuickGUI::registerScriptReader();
}

// Constructor
Gui::Gui(void)
{
    new QuickGUI::Root();
}

// Destructor
Gui::~Gui(void)
{
    delete QuickGUI::Root::getSingletonPtr();
}

} // namespace gui
