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
/// @author LRG

#ifndef BATTLE_GROUND_HPP
#define BATTLE_GROUND_HPP

#include <OgreFrameListener.h>
#include <OIS/OIS.h>

#include "macros.hpp"

class Character;
class Object;

namespace Caelum { class CaelumSystem; }
namespace Hydrax { class Hydrax; }
namespace SkyX { class SkyX; }

/// Class to control all that happens in a battle ground.
class BattleGround : public Ogre::FrameListener, public OIS::KeyListener {
public:
    BattleGround(void); // Constructor
    
	~BattleGround(void); // Destructor

    /// Adds a player to the battle ground.
    /// @param[in] num_player Number of the player.
    void addPlayer(const int num_player);

    /// Starts the battle.
    void start(void);

private:
    // Function that's called at the beginning of every frame.
    virtual bool frameStarted(const Ogre::FrameEvent &event);

    // @{
    // Functions to update the keyboard's state.
    virtual bool keyPressed  (const OIS::KeyEvent &key) {return true;}
    virtual bool keyReleased (const OIS::KeyEvent &key);
    // @}

	//! Creates a dynamic sky using the Caelum plugin.
	//! The caelum system must then be updated periodically and eventually destroyed.
	void createCaelumSky();

	//! Creates an infinite water plane using the Hydrax plugin.
	//! The hydrax system must then be updated periodically and eventually destroyed.
	void createHydraxWater();

	//! Creates a dynamic sky using the SkyX plugin.
	//! The SkyX system must be updated periodically and eventually destroyed.
	void createSkyX();

    Ogre::SceneManager *scene_manager;
    Ogre::Viewport *viewport;
    Ogre::Camera *camera;

    std::list<Object*> objects;
    std::list<Character*> players;

#ifdef USE_CAELUM
	Caelum::CaelumSystem * mCaelumSystem;
#endif
	
#ifdef USE_HYDRAX
	Hydrax::Hydrax * mHydrax;
#endif

#ifdef USE_SKYX
	SkyX::SkyX * mSkyX;
#endif

    bool end;

    DISALLOW_COPY_AND_ASSIGN(BattleGround);
};

#endif // BATTLE_GROUND_HPP
