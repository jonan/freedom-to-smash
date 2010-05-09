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
/// The Character class.
/// @author Jonan

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

// Ogre
#include <OgreFrameListener.h>

// FtS
#include <object.hpp>

enum MoveDirection {RIGHT, LEFT};

/// Class to control a character.
class Character : public Object, public Ogre::FrameListener {
public:
    explicit Character(Ogre::SceneManager &scene_manager); // Constructor
    ~Character(void); // Destructor

    // @{
    /// Get functions.
    MoveDirection getDirection(void) {return direction;}
    // @}

    // @{
    /// Start performing an action.
    void attack (void);
    void jump   (void);
    void defend (void);
    void move   (const MoveDirection direction);
    // @}

    // @{
    /// Stop performing an action.
    void stopDefending (void) {stopAction(DEFEND);}
    void stopMoving    (void) {stopAction(MOVE);  }
    // @}

    /// Detects and solves collisions of the character with the battle ground.
    /// This function must be called every frame.
    /// @param[in] objects All the objects in the battle ground.
    void recoverFromPenetration(const std::list<Object*> &objects);

    ///
    void reset(void);

	//! Loads a character script.
	//!
	//! @param file Absolute or relative path to the lua script.
	void handleScript(std::string const & file);

private:
    // All the different states of a character.
    enum {ATTACK, DEFEND, FALL, IDLE, JUMP, LAND, MOVE, NUM_STATES};

    // Function that's called at the beginning of every frame.
    virtual bool frameStarted(const Ogre::FrameEvent &event);

    // Prepares all animations so they can be used.
    void prepareAnimations(void);

    // @{
    // Funtions that need to be called every frame for the character to be updated.
    void frameCheck     (void);
    void frameAnimation (const Ogre::FrameEvent &event);
    void frameMovement  (const Ogre::FrameEvent &event);
    // @}

    // Player stops performing an action
    void stopAction(const int type);

    // Calculates the current vertical speed.
    const Real calculateVerticalSpeed(const Real &start_speed);

    bool action[NUM_STATES]; // active actions

    bool on_floor, has_double_jumped;
    bool collision_right, collision_left;
    Real jumping_time;

    MoveDirection direction;

    DISALLOW_COPY_AND_ASSIGN(Character);
};

#endif // CHARACTER_HPP
