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

#include "player.hpp"

#include "battle_ground.hpp"
#include "character.hpp"
#include "input.hpp"

// Constructor
Player::Player(void)
        : character(NULL)
        , battle_ground(NULL)
{
    Input::getInstance()->addKeyListener(*this);
    // Controls will be loaded from a config file
    attack_key = OIS::KC_A;
    jump_key   = OIS::KC_S;
    up_key     = OIS::KC_UP;
    down_key   = OIS::KC_DOWN;
    right_key  = OIS::KC_RIGHT;
    left_key   = OIS::KC_LEFT;
}

// Destructor
Player::~Player(void)
{
    Input::getInstance()->removeKeyListener(*this);
}

//
void Player::setCharacter(void)
{
    character = battle_ground->createCharacter();
}

// Function to update the keyboard's state.
bool Player::keyPressed(const OIS::KeyEvent &key)
{
    if (key.key == attack_key)
        character->attack();
    else if (key.key == jump_key)
        character->jump();
    else if (key.key == down_key)
        character->defend();
    else if (key.key == right_key)
        character->move(true);
    else if (key.key == left_key)
        character->move(false);
    return true;
}

// Function to update the keyboard's state.
bool Player::keyReleased(const OIS::KeyEvent &key)
{
    if (key.key == OIS::KC_ESCAPE)
        battle_ground->quit();
    else if (key.key == down_key)
        character->stopDefending();
    else if (key.key == right_key || key.key == left_key)
        character->stopMoving();
    return true;
}
