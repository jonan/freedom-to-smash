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

#include "collision_box.hpp"

#include <OgreSceneNode.h>

#include "util.hpp"

// Constructor
CollisionBox::CollisionBox(const float max_x,   const float min_x,
                           const float max_y,   const float min_y,
                           const float point_x, const float point_y
                          ) {
  setRelativeBoxPos(max_x, min_x, max_y, min_y);
  setReferencePoint(point_x, point_y);
}

// Function to set the object's values.
void CollisionBox::setReferencePoint(const Ogre::SceneNode &pos) {
  setReferencePoint( pos.getPosition().x, pos.getPosition().y );
}

// Function to set the object's values.
void CollisionBox::setReferencePoint(const float point_x, const float point_y) {
  this->point_x = point_x;
  this->point_y = point_y;

  max_x = point_x + rel_max_x;
  min_x = point_x + rel_min_x;
  max_y = point_y + rel_max_y;
  min_y = point_y + rel_min_y;
}

// Function to set the object's values.
void CollisionBox::setRelativeBoxPos(const float max_x, const float min_x,
                                     const float max_y, const float min_y
                                    ) {
  rel_max_x = max_x;
  rel_min_x = min_x;
  rel_max_y = max_y;
  rel_min_y = min_y;

  width  = rel_max_x-rel_min_x;
  height = rel_max_y-rel_min_y;
}

// Detects the collision with the given box and returns the type of collision.
int CollisionBox::detectCollision(const CollisionBox &box) const {
  int collision_type = NO_COLLISION;

  CollisionBox intersection_box = getIntersectionBox(box);

  if (!intersection_box.isNull()) {
    // Collision detected
    if ( (intersection_box.width == width     && intersection_box.height == height    ) ||
         (intersection_box.width == box.width && intersection_box.height == box.height) ||
         (intersection_box.width == width     && intersection_box.height == box.height) ||
         (intersection_box.width == box.width && intersection_box.height == height    )    ) {
      collision_type = FULL_COLLISION;
    } else if (intersection_box.max_x == box.max_x && intersection_box.height > intersection_box.width) {
      collision_type = RIGHT_COLLISION;
    } else if (intersection_box.min_x == box.min_x && intersection_box.height > intersection_box.width) {
      collision_type = LEFT_COLLISION;
    } else if (intersection_box.max_y == box.max_y) {
      collision_type = BOTTOM_COLLISION;
    } else if (intersection_box.min_y == box.min_y) {
      collision_type = TOP_COLLISION;
    }
  }

  return collision_type;
}

// Returns the intersection with the given object.
CollisionBox CollisionBox::getIntersectionBox(const CollisionBox &box) const {
  CollisionBox intersection;

  if (!(this->isNull() || box.isNull())) {
    float intersection_max_x = minimum(max_x, box.max_x);
    float intersection_min_x = maximum(min_x, box.min_x);
    float intersection_max_y = minimum(max_y, box.max_y);
    float intersection_min_y = maximum(min_y, box.min_y);

    // Check if there's an intersection
    if ( intersection_max_x > intersection_min_x &&
         intersection_max_y > intersection_min_y    )
      intersection.setRelativeBoxPos(intersection_max_x, intersection_min_x,
                                     intersection_max_y, intersection_min_y);
      intersection.setReferencePoint(0,0);
  }

  return intersection;
}
