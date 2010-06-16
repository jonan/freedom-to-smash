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

#include <menu.hpp>

// Ogre
#include <OgreRoot.h>

#include <fts_evaluator.hpp>
#include <script_manager.hpp>

// FtS
#include <gui/gui.hpp>
#include <battle_ground.hpp>
#include <player.hpp>

// Constructor
Menu::Menu(void)
        : end(false)
{
    // Default settings
    //setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    setAmbientLight(Ogre::ColourValue(1,1,1));
    // Create camera
    useCamera(addCamera("Menu Camera", Ogre::Vector3(0,0,-10)));
    // GUI
    //gui::Gui::getInstance().loadSheet("main_menu", this);
    gui::Gui::getInstance().createSheet(this);
}

//
void Menu::start(void)
{
    Ogre::Root::getSingleton().addFrameListener(this);
    Ogre::Root::getSingleton().startRendering();
    Ogre::Root::getSingleton().removeFrameListener(this);
}

//
void Menu::player1(const QuickGUI::EventArgs& /*args*/)
{
    std::string player1, player2;
    FtsEvaluator ev(ScriptManager::get().getL());
    ev.evalString("Config.Player1", player1);
    ev.evalString("Config.Player2", player2);

    Player *player = new Player(1);
    BattleGround *battle = new BattleGround;
    player->setBattleground(*battle);
    player->setCharacter(player1);
    player = new Player(2);
    player->setBattleground(*battle);
    player->setCharacter(player2);
    battle->start();
    delete battle;
}

//
void Menu::player2(const QuickGUI::EventArgs& /*args*/)
{

}

// Function that's called at the beginning of every frame.
bool Menu::frameStarted(const Ogre::FrameEvent& /*event*/)
{
    return !end;
}
