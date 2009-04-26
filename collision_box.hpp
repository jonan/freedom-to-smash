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

namespace Ogre {
class SceneNode;
}

/// Collisions types.
enum { NO_COLLISION,
       LEFT_COLLISION,
       RIGHT_COLLISION,
       TOP_COLLISION,
       BOTTOM_COLLISION };

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
    explicit CollisionBox( const float max_x   = 0, const float min_x   = 0,
                           const float max_y   = 0, const float min_y   = 0,
                           const float point_x = 0, const float point_y = 0 ); // Constructor

    // @{
    /// Functions to set the object's values.
    void setReferencePoint (const Ogre::SceneNode &pos);
    void setRelativeBoxPos (const float max_x, const float min_x, const float max_y, const float min_y);
    // @}

    /// Detects the collision with the given box and returns the type of collision.
    int detectCollision(const CollisionBox &box) const;

  private:
    // Returns if the CollisionBox is null or not.
    bool isNull(void) const {return !(max_x || min_x || max_y || min_y);}

    // @{
    // Functions to get all the positions in world coordinates.
    float getMaxX (void) const {return point_x + max_x;}
    float getMinX (void) const {return point_x + min_x;}
    float getMaxY (void) const {return point_y + max_y;}
    float getMinY (void) const {return point_y + min_y;}
    // @}

    // Returns the intersection with the given CollisionBox.
    CollisionBox getIntersectionBox(const CollisionBox &box) const;

    float max_x, min_x, max_y, min_y;
    float point_x, point_y;
    float width, height;
};

#endif // COLLISION_BOX_HPP
