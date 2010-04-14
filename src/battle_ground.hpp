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
/// The BattleGround class.
/// @author Jonan

#ifndef BATTLE_GROUND_HPP
#define BATTLE_GROUND_HPP

#include <OIS/OIS.h>

#include "physics/collision_scene.hpp"
#include "graphic_scene.hpp"
#include "util.hpp"

class Character;
class Object;

/// Class to control all that happens in a battle ground.
class BattleGround : public GraphicScene, public physics::CollisionScene, public OIS::KeyListener {
public:
    BattleGround(void); // Constructor
    ~BattleGround(void); // Destructor

    /// Creates a character and adds it to the battle ground.
    /// @return Created character.
    Character* createCharacter(void);

    /// Starts the battle.
    void start(void);
    /// Quits the battle.
    void quit(void) {end=true;}

private:
    // Function that's called at the beginning of every frame.
    virtual bool frameStarted(const Ogre::FrameEvent &event);

    // @{
    // Functions to update the keyboard's state.
    virtual bool keyPressed  (const OIS::KeyEvent &key) {return true;}
    virtual bool keyReleased (const OIS::KeyEvent &key);
    // @}

    std::list<Character*> players;
    Ogre::SceneNode *cam_node;

    bool end;

    DISALLOW_COPY_AND_ASSIGN(BattleGround);
};

#endif // BATTLE_GROUND_HPP
