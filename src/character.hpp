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

#include <OgreFrameListener.h>

#include "animated_object.hpp"

/// Class to control a character.
class Character : public AnimatedObject, public Ogre::FrameListener {
public:
    Character(Ogre::SceneManager &scene_manager); // Constructor
    ~Character(void); // Destructor

    // @{
    /// Start performing an action.
    void attack        (void);
    void defend        (void);
    void jump          (void);
    void moveLeft      (void);
    void moveRight     (void);
    void specialAttack (void);
    // @}

    // @{
    /// Stop performing an action.
    void stopDefending (void);
    void stopMoving    (void);
    // @}

    /// Detects and solves collisions of the character with the battle ground.
    /// This function must be called every frame.
    /// @param[in] objects All the objects in the battle ground.
    void recoverFromPenetration(const std::list<Object*> &objects);

private:
    // All the different states of a character.
    enum {ATTACK_1, ATTACK_2, DEFEND, DOUBLE_JUMP, FALL, IDLE, JUMP,
          LAND, MOVE, SPECIAL_ATTACK_1, SPECIAL_ATTACK_2, NUM_STATES};

    // Function that's called at the beginning of every frame.
    virtual bool frameStarted(const Ogre::FrameEvent &event);

    // Prepares all animations so they can be used.
    void prepareAnimations(void);

    // @{
    // Funtions that need to be called every frame for the character to be updated.
    void animate (const Ogre::FrameEvent &event);
    void move    (const Ogre::FrameEvent &event);
    // @}

    // Player stops performing an action
    void stopAction(const int type);

    bool action[NUM_STATES]; // active actions

    bool on_floor, has_double_jumped;
    Real jumping_time;

    int direction;

    // Controls
    int attack_key, defend_key, jump_key, move_left_key, move_right_key, special_attack_key;

    DISALLOW_COPY_AND_ASSIGN(Character);
};

#endif // CHARACTER_HPP
