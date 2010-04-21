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

#include "shapes_manager.hpp"

// Boost
#include <boost/foreach.hpp>
// Bullet
#include <btBulletCollisionCommon.h>

namespace physics {

// Singleton pattern constructor
ShapesManager* ShapesManager::getInstance(void) {
    static ShapesManager instance;
    return &instance;
}

// Function to get a box shape.
btCollisionShape* ShapesManager::getBoxShape(const btVector3 &size) {
    btBoxShape *temp = findBoxShape(size);
    if (!temp) {
        temp = new btBoxShape(size/2);
        box_shapes.push_back(temp);
    }
    return temp;
}

// Destructor
ShapesManager::~ShapesManager(void) {
    BOOST_FOREACH(btBoxShape *shape, box_shapes)
        delete shape;
}

// Functions to find a given box shape.
btBoxShape* ShapesManager::findBoxShape(const btVector3 &size) {
    btBoxShape *temp = NULL;
    btVector3 half_size = size/2;
    BOOST_FOREACH(btBoxShape *shape, box_shapes) {
        if (!temp) {
            if (half_size == shape->getHalfExtentsWithMargin())
                temp = shape;
        }
    }
    return temp;
}

} // namespace physics
