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
/// The CollisionBox class.
/// @author Jonan

#ifndef COLLISION_BOX_HPP
#define COLLISION_BOX_HPP

#include "macros.hpp"

namespace Ogre {
class SceneNode;
}

/// Collisions types.
enum CollisionType { NO_COLLISION,
                     LEFT_COLLISION,
                     RIGHT_COLLISION,
                     TOP_COLLISION,
                     BOTTOM_COLLISION,
                     FULL_COLLISION   };

/// Box used to detect collisions.
/// The box is stored as a reference point that can be located
/// anywhere and the maximum and minimum positions relative to that point.
class CollisionBox {
  public:
    /// @param[in] max_x   Maximum X position relative to the reference point.
    /// @param[in] min_x   Minimum X position relative to the reference point.
    /// @param[in] max_y   Maximum Y position relative to the reference point.
    /// @param[in] min_y   Minimum Y position relative to the reference point.
    /// @param[in] point_x X coordinate of the reference point.
    /// @param[in] point_y Y coordinate of the reference point.
    explicit CollisionBox( const Real &max_x   = 0, const Real &min_x   = 0,
                           const Real &max_y   = 0, const Real &min_y   = 0,
                           const Real &point_x = 0, const Real &point_y = 0 ); // Constructor

    // @{
    /// Functions to set the object's values.
    void setReferencePoint (const Ogre::SceneNode &pos);
    void setReferencePoint (const Real &point_x, const Real &point_y);
    void setRelativeBoxPos (const Real &max_x, const Real &min_x, const Real &max_y, const Real &min_y);
    // @}

    /// Detects the collision with the given box and returns the type of collision.
    CollisionType detectCollision(const CollisionBox &box) const;

  private:
    // Returns if the CollisionBox is null or not.
    bool isNull(void) const {return !(rel_max_x || rel_min_x || rel_max_y || rel_min_y);}

    // @{
    //
    void calculateWidthHeight(void);
    void calculateMaxSize(void);
    // @}

    // Returns the intersection with the given CollisionBox.
    CollisionBox getIntersectionBox(const CollisionBox &box) const;

    Real rel_max_x, rel_min_x, rel_max_y, rel_min_y;
    Real max_x, min_x, max_y, min_y;
    Real point_x, point_y;
    Real width, height;

    DISALLOW_COPY_AND_ASSIGN(CollisionBox);
};

#endif // COLLISION_BOX_HPP
