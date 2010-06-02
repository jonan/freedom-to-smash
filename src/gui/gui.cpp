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

// Destroys the GUI system.
void Gui::destroy(void)
{
    delete QuickGUI::Root::getSingletonPtr();
}

// Creates a GUI from a sheet.
void Gui::loadSheet(const String &name)
{
    QuickGUI::Sheet *sheet = QuickGUI::SheetManager::getSingleton().createSheet("menu_sheets/" + name,true);
    gui_manager->setActiveSheet(sheet);
}

// Constructor
Gui::Gui(void)
{
    new QuickGUI::Root();
    QuickGUI::SkinTypeManager::getSingleton().loadTypes();
    QuickGUI::GUIManagerDesc manager_description;
    gui_manager = QuickGUI::Root::getSingletonPtr()->createGUIManager(manager_description);
}

} // namespace gui
