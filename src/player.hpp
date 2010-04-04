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
/// The Player class.
/// @author Jonan

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <OIS/OIS.h>

#include "util.hpp"

class BattleGround;
class Character;

///
class Player : public OIS::KeyListener {
public:
    Player(void); // Constructor
    ~Player(void); // Destructor

    ///
    void setBattleground(BattleGround &ground) {battle_ground = &ground;}
    ///
    void setCharacter(void);

private:
    // @{
    // Functions to update the keyboard's state.
    virtual bool keyPressed  (const OIS::KeyEvent &key);
    virtual bool keyReleased (const OIS::KeyEvent &key);
    // @}

    Character *character;
    BattleGround *battle_ground;

    // Controls
    int attack_key, jump_key;
    int up_key, down_key, right_key, left_key;

    DISALLOW_COPY_AND_ASSIGN(Player);
};

#endif // PLAYER_HPP
