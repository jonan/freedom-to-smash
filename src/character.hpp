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
    Character(const String &name, Ogre::SceneManager &scene_manager); // Constructor
    virtual ~Character(void); // Destructor

    /// All the different states of a character.
    enum {ATTACK, DEFEND, FALL, IDLE, JUMP, LAND, MOVE, NUM_STATES};

    // @{
    /// Set functions.
    void setInitialPos(Ogre::Vector3 *pos);
    // @}

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

    ///
    void reset(void);

    /// Loads a character script.
    /// @param[in] file Path of the script to load.
    void handleScript(const String &file);

private:
    // This method needs to be defined this way to ignore
    // the rotation of the character's physical representation.
    virtual void setGraphicalRotation (const Ogre::Quaternion &/*rot*/) {}

    // Function that's called at the beginning of every frame.
    virtual bool frameStarted(const Ogre::FrameEvent &event);

    // @{
    // Funtions that need to be called every frame for the character to be updated.
    void frameAttack    (void);
    void frameCheck     (void);
    void frameMovement  (void);
    void frameAnimation (const Ogre::FrameEvent &event);
    // @}

    // Player stops performing an action
    void stopAction(const int type);

    bool action[NUM_STATES]; // active actions

    bool on_floor, has_double_jumped;
    Real yaw;
    bool collision_right, collision_left;
    double jump_force;
    double walk_speed;

    physics::Object *attack_obj;
    btCollisionShape *attack_shape;

    Ogre::Vector3 *initial_pos;

    MoveDirection direction;

    DISALLOW_COPY_AND_ASSIGN(Character);
};

#endif // CHARACTER_HPP
