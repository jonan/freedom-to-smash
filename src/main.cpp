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
/// The main function.
/// @author Jonan

#include <stdexcept>
#include <iostream>

// FtS
#include <battle_ground.hpp>
#include <boot.hpp>
#include <player.hpp>

int main(int argc, char *argv[])
{
	try 
	{

		boot();
		Player *player = new Player(1);
		BattleGround *battle = new BattleGround;
		player->setBattleground(*battle);
		player->setCharacter();
		player = new Player(2);
		player->setBattleground(*battle);
		player->setCharacter();
		battle->start();
		delete battle;
		quit();
	} 
	catch(std::exception & e)
	{
		std::cerr << "Fatal exception caught on main: " << e.what() << std::endl;
	}
}
