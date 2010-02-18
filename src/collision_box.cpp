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
CollisionBox::CollisionBox( const Real &max_x,   const Real &min_x,
                            const Real &max_y,   const Real &min_y,
                            const Real &point_x, const Real &point_y )
{
    setRelativeBoxPos(max_x, min_x, max_y, min_y);
    setReferencePoint(point_x, point_y);
}

// Function to set the object's values.
void CollisionBox::setReferencePoint(const Ogre::SceneNode &pos)
{
    setReferencePoint( pos.getPosition().x, pos.getPosition().y );
}

// Function to set the object's values.
void CollisionBox::setReferencePoint(const Real &point_x, const Real &point_y)
{
    this->point_x = point_x;
    this->point_y = point_y;

    calculateMaxSize();
}

// Function to set the object's values.
void CollisionBox::setRelativeBoxPos( const Real &max_x, const Real &min_x,
                                      const Real &max_y, const Real &min_y )
{
    rel_max_x = max_x;
    rel_min_x = min_x;
    rel_max_y = max_y;
    rel_min_y = min_y;

    calculateWidthHeight();
    calculateMaxSize();
}

// Detects the collision with the given box and returns the type of collision.
CollisionType CollisionBox::detectCollision(const CollisionBox &box) const
{
    CollisionType collision_type = NO_COLLISION;

    CollisionBox *intersection_box = getIntersectionBox(box);
    if (!intersection_box->isNull()) {
        // Collision detected
        if ( (intersection_box->width == width     && intersection_box->height == height    ) ||
             (intersection_box->width == box.width && intersection_box->height == box.height) ||
             (intersection_box->width == width     && intersection_box->height == box.height) ||
             (intersection_box->width == box.width && intersection_box->height == height    )    ) {
            collision_type = FULL_COLLISION;
        } else if (intersection_box->max_x == box.max_x && intersection_box->height > intersection_box->width) {
            collision_type = RIGHT_COLLISION;
        } else if (intersection_box->min_x == box.min_x && intersection_box->height > intersection_box->width) {
            collision_type = LEFT_COLLISION;
        } else if (intersection_box->max_y == box.max_y) {
            collision_type = BOTTOM_COLLISION;
        } else if (intersection_box->min_y == box.min_y) {
            collision_type = TOP_COLLISION;
        }
    }
    delete intersection_box;

    return collision_type;
}

//
void CollisionBox::calculateWidthHeight(void)
{
    width  = rel_max_x-rel_min_x;
    height = rel_max_y-rel_min_y;
}

//
void CollisionBox::calculateMaxSize(void)
{
    max_x = point_x + rel_max_x;
    min_x = point_x + rel_min_x;
    max_y = point_y + rel_max_y;
    min_y = point_y + rel_min_y;
}

// Returns the intersection with the given CollisionBox (needs to be deleted).
CollisionBox* CollisionBox::getIntersectionBox(const CollisionBox &box) const
{
    /// @todo Don't return a pointer to a dynamically allocated object.
    CollisionBox *intersection = new CollisionBox;

    if (!(this->isNull() || box.isNull())) {
        Real intersection_max_x = minimum(max_x, box.max_x);
        Real intersection_min_x = maximum(min_x, box.min_x);
        Real intersection_max_y = minimum(max_y, box.max_y);
        Real intersection_min_y = maximum(min_y, box.min_y);

        // Check if there's an intersection
        if ( (intersection_max_x > intersection_min_x) && (intersection_max_y > intersection_min_y) )
            intersection->setRelativeBoxPos(intersection_max_x, intersection_min_x,
                                            intersection_max_y, intersection_min_y);
    }

    return intersection;
}
