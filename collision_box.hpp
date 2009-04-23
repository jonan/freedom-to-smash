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

#ifndef COLLISION_BOX_HPP
#define COLLISION_BOX_HPP

namespace Ogre {
class SceneNode;
}

/// 
class CollisionBox {
  public:
    CollisionBox( const float max_x   = 0, const float min_x   = 0,
                  const float max_y   = 0, const float min_y   = 0,
                  const float point_x = 0, const float point_y = 0 ); // Constructor

    // @{
    /// 
    void setReferencePoint (const Ogre::SceneNode &pos);
    void setRelativeBoxPos (const float max_x, const float min_x, const float max_y, const float min_y);
    // @}

    // @{
    /// 
    float getMaxX   (void) const {return point_x + max_x;}
    float getMinX   (void) const {return point_x + min_x;}
    float getMaxY   (void) const {return point_y + max_y;}
    float getMinY   (void) const {return point_y + min_y;}
    float getWidth  (void) const {return width;          }
    float getHeight (void) const {return height;         }
    // @}

    /// 
    bool isNull(void) const {return !(max_x || min_x || max_y || min_y);}

    /// 
    CollisionBox intersection(const CollisionBox &box);

  private:
    float max_x, min_x, max_y, min_y;
    float point_x, point_y;
    float width, height;
};

#endif // COLLISION_BOX_HPP
