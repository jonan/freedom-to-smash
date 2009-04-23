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
  this->max_x = max_x;
  this->min_x = min_x;
  this->max_y = max_y;
  this->min_y = min_y;

  width = max_x-min_x;
  height = max_y-min_y;

  this->point_x = point_x;
  this->point_y = point_y;
}

// 
void CollisionBox::setReferencePoint(const Ogre::SceneNode &pos) {
  point_x = pos.getPosition().x;
  point_y = pos.getPosition().y;
}

// 
void CollisionBox::setRelativeBoxPos(const float max_x, const float min_x,
                                     const float max_y, const float min_y
                                    ) {
  this->max_x = max_x;
  this->min_x = min_x;
  this->max_y = max_y;
  this->min_y = min_y;

  width = max_x-min_x;
  height = max_y-min_y;
}

// 
CollisionBox CollisionBox::intersection(const CollisionBox &box) {
  CollisionBox intersection;

  if (!(this->isNull() || box.isNull())) {
    float intersection_max_x;
    float intersection_min_x;
    float intersection_max_y;
    float intersection_min_y;

    intersection_max_x = minimum(this->getMaxX(), box.getMaxX());
    intersection_min_x = maximum(this->getMinX(), box.getMinX());
    intersection_max_y = minimum(this->getMaxY(), box.getMaxY());
    intersection_min_x = maximum(this->getMinY(), box.getMinY());

    // Check if there's an intersection
    if ( intersection_max_x > intersection_min_x &&
         intersection_max_y > intersection_min_y    )
      intersection.setRelativeBoxPos(intersection_max_x, intersection_min_x,
                                     intersection_max_y, intersection_min_y);
  }

  return intersection;
}
