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

#include <iostream>

#include <boost/foreach.hpp>

#include <btBulletCollisionCommon.h>

namespace physics {

// Singleton pattern constructor
ShapesManager* ShapesManager::getInstance(void) {
    static ShapesManager instance;
    return &instance;
}

// Destructor
ShapesManager::~ShapesManager(void) {
    BOOST_FOREACH(btBoxShape *shape, box_shapes)
        delete shape;
}

// Function to get a box shape.
btBoxShape* ShapesManager::getBoxShape(const Real &width, const Real &height, const Real &depth) {
    btBoxShape* temp = findBoxShape(width, height, depth);
    if (!temp) {
        temp = new btBoxShape(btVector3(width/2, height/2, depth/2));
        box_shapes.push_back(temp);
    }
    return temp;
}

// Functions to find a given box shape.
btBoxShape* ShapesManager::findBoxShape(const Real &width, const Real &height, const Real &depth) {
    btBoxShape* temp = NULL;
    btVector3 half_size;
    BOOST_FOREACH(btBoxShape *shape, box_shapes) {
        if (!temp) {
            half_size = shape->getHalfExtentsWithMargin();
            if (half_size.x() == width/2 && half_size.y() == height/2 && half_size.z() == depth/2)
                temp = shape;
        }
    }
    return temp;
}

} // namespace physics
