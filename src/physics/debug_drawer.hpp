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
/// The physics::DebugDrawer class.
/// @author Jonan

#ifndef PHYSICS_DEBUG_DRAWER_HPP
#define PHYSICS_DEBUG_DRAWER_HPP

#include <btBulletCollisionCommon.h>

#include "util.hpp"

namespace Ogre {
    class ManualObject;
    class SceneManager;
}

namespace physics {

/// Draws the physic world for debug purposes.
class DebugDrawer : public btIDebugDraw {
  public:
    /// @param[in] scene_manager SceneManager of the scene where the object will be.
    explicit DebugDrawer(Ogre::SceneManager &scene_manager); // Constructor
    ~DebugDrawer(void); // Destructor

    /// Draws all the stored debug lines.
    void draw(void);

  private:
    // @{
    // Set and Get methods.
    virtual void setDebugMode (int mode)       {debug_mode = mode;}
    virtual int  getDebugMode (void    ) const {return debug_mode;}
    // @}

    // Adds a new line to the drawing queue.
    virtual void drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color);

    // @{
    // Abstract inherited functions.
    virtual void drawContactPoint(const btVector3 &point_on_b, const btVector3 &normal_on_b, btScalar distance, int life_time, const btVector3 &color) {}
    virtual void reportErrorWarning(const char *warning_string) {}
    virtual void draw3dText(const btVector3 &location, const char *text_string) {}
    // @}

    int debug_mode;
    bool restart;
    Ogre::ManualObject *debug_lines;

    DISALLOW_COPY_AND_ASSIGN(DebugDrawer);
};

} // namespace physics

#endif // PHYSICS_DEBUG_DRAWER_HPP
