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
/// 
/// @author Jonan

#ifndef BATTLE_GROUND_HPP
#define BATTLE_GROUND_HPP

#include <OgreFrameListener.h>

#include <OIS/OIS.h>

#include <vector>

#include "macros.hpp"

class Character;
class Object;

/// 
class BattleGround : public Ogre::FrameListener, public OIS::KeyListener {
  public:
    BattleGround(void); // Constructor
    ~BattleGround(void); // Destructor

    /// 
    void addPlayer(const int num_player);

    /// 
    void start(void);

  private:
    // 
    virtual bool frameStarted(const Ogre::FrameEvent& event);

    // @{
    // 
    virtual bool keyPressed  (const OIS::KeyEvent& key);
    virtual bool keyReleased (const OIS::KeyEvent& key);
    // @}

    Ogre::SceneManager *scene_manager;
    Ogre::Viewport *viewport;
    Ogre::Camera *camera;

    std::vector<Object*> objects;
    std::vector<Character*> players;

    bool end;

    DISALLOW_COPY_AND_ASSIGN(BattleGround);
};

#endif // BATTLE_GROUND_HPP
