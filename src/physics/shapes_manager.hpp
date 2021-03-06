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
/// The physics::ShapesManager class.
/// @author Jonan

#ifndef PHYSICS_SHAPES_MANAGER_HPP
#define PHYSICS_SHAPES_MANAGER_HPP

// C++
#include <list>

// FtS
#include <util.hpp>

// Bullet
class btBoxShape;
class btCollisionShape;
class btVector3;

namespace physics {

/// Stores all physic shapes to make sure none are duplicated.
class ShapesManager {
public:
    static ShapesManager& getInstance(void); // Singleton pattern constructor

    // @{
    /// Functions to get the different physic shapes.
    btCollisionShape& getBoxShape(const btVector3 &size);
    // @}

private:
    ShapesManager(void) {} // Constructor
    ~ShapesManager(void); // Destructor

    // @{
    // Functions to find a given shape.
    btBoxShape* findBoxShape(const btVector3 &size);
    // @}

    std::list<btBoxShape*> box_shapes;

    DISALLOW_COPY_AND_ASSIGN(ShapesManager);
};

} // namespace physics

#endif // PHYSICS_SHAPES_MANAGER_HPP
