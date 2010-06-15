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

// FtS
#include <input.hpp>

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
    Input::getInstance()->removeKeyListener(*this);
    Input::getInstance()->removeMouseListener(*this);
    delete QuickGUI::Root::getSingletonPtr();
}

// Creates a GUI from a sheet.
void Gui::loadSheet(const String &name)
{
    Input::getInstance()->addKeyListener(*this);
    Input::getInstance()->addMouseListener(*this);
    QuickGUI::Sheet *sheet = QuickGUI::SheetManager::getSingleton().createSheet("menu_sheets/" + name,true);
    gui_manager->setActiveSheet(sheet);
}

// Temporal method to hard-code GUIs.
void Gui::createSheet(void)
{
    Input::getInstance()->addKeyListener(*this);
    Input::getInstance()->addMouseListener(*this);
    QuickGUI::SheetDesc *sheet_description = QuickGUI::DescManager::getSingleton().getDefaultSheetDesc();
    QuickGUI::Sheet *sheet = QuickGUI::SheetManager::getSingleton().createSheet(sheet_description);
    //sheet->setMouseCursorVisible(false);
    gui_manager->setActiveSheet(sheet);
    QuickGUI::ButtonDesc* bd = QuickGUI::DescManager::getSingleton().getDefaultButtonDesc();
    bd->textDesc.segments.push_back(QuickGUI::TextSegment("micross.12",QuickGUI::ColourValue::Red,"Click Me!"));
    bd->widget_name = "MyButton";
    bd->widget_dimensions.size = QuickGUI::Size(100,25);
    bd->widget_dimensions.position = QuickGUI::Point(50,50);
    QuickGUI::Button* myButton = sheet->createButton(bd);
    sheet->saveToDisk("sheet.gui");
}

// Constructor
Gui::Gui(void)
{
    new QuickGUI::Root();
    QuickGUI::SkinTypeManager::getSingleton().loadTypes();
    QuickGUI::GUIManagerDesc manager_description;
    gui_manager = QuickGUI::Root::getSingletonPtr()->createGUIManager(manager_description);
}

// Function to update the keyboard's state.
bool Gui::keyPressed(const OIS::KeyEvent &key)
{
    gui_manager->injectChar(static_cast<Ogre::UTFString::unicode_char>(key.text));
    gui_manager->injectKeyDown(static_cast<QuickGUI::KeyCode>(key.key));
    return true;
}

// Function to update the keyboard's state.
bool Gui::keyReleased(const OIS::KeyEvent &key)
{
    gui_manager->injectKeyUp(static_cast<QuickGUI::KeyCode>(key.key));
    return true;
}

// Functions to update the mouse's state.
bool Gui::mouseMoved(const OIS::MouseEvent &event)
{
    gui_manager->injectMousePosition(event.state.X.abs, event.state.Y.abs);

    Real z = event.state.Z.rel;
    if (z != 0)
        gui_manager->injectMouseWheelChange(z);

    return true;
}

// Functions to update the mouse's state.
bool Gui::mousePressed(const OIS::MouseEvent& /*event*/, OIS::MouseButtonID key)
{
    gui_manager->injectMouseButtonDown(static_cast<QuickGUI::MouseButtonID>(key));
    return true;
}

// Functions to update the mouse's state.
bool Gui::mouseReleased(const OIS::MouseEvent& /*event*/, OIS::MouseButtonID key)
{
    gui_manager->injectMouseButtonUp(static_cast<QuickGUI::MouseButtonID>(key));
    return true;
}

} // namespace gui
