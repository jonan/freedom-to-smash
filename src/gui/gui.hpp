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

// OIS
#include <OIS/OIS.h>

// FtS
#include <util.hpp>

namespace QuickGUI {class GUIManager;}

namespace gui {

///
class Gui : public OIS::KeyListener, public OIS::MouseListener {
public:
    static Gui& getInstance(void); // Singleton pattern constructor

    /// Registers the script reader.
    /// Must be called before initializing the resources.
    static void registerScriptReader(void);

    /// Destroys the GUI system.
    /// Must be called before deleting Ogre.
    void destroy(void);

    /// Creates a GUI from a sheet.
    /// @param[in] name Name of the sheet
    void loadSheet(const String &name);

    /// Temporal method to hard-code GUIs.
    /// The GUI is then saved as sheet.gui.
    void createSheet(void);

private:
    Gui(void); // Constructor

    // @{
    // Functions to update the keyboard's state.
    virtual bool keyPressed  (const OIS::KeyEvent &key);
    virtual bool keyReleased (const OIS::KeyEvent &key);
    // @}

    // @{
    // Functions to update the mouse's state.
    virtual bool mouseMoved    (const OIS::MouseEvent &arg);
    virtual bool mousePressed  (const OIS::MouseEvent &arg, OIS::MouseButtonID key);
    virtual bool mouseReleased (const OIS::MouseEvent &arg, OIS::MouseButtonID key);
    // @}

    QuickGUI::GUIManager *gui_manager;

    DISALLOW_COPY_AND_ASSIGN(Gui);
};

} // namespace gui

#endif // GUI_GUI_HPP
