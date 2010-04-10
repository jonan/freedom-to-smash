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
/// The physics::CollisionObject class.
/// @author Jonan

#ifndef PHYSICS_COLLISION_OBJECT_HPP
#define PHYSICS_COLLISION_OBJECT_HPP

#include "util.hpp"

namespace physics {

/// Collisions types.
enum CollisionType { NO_COLLISION,
                     LEFT_COLLISION,
                     RIGHT_COLLISION,
                     TOP_COLLISION,
                     BOTTOM_COLLISION,
                     FULL_COLLISION   };

/// General object class.
class CollisionObject {
public:
    CollisionObject(void); // Constructor
    virtual ~CollisionObject(void) {} // Destructor

    /// Detects the collision with another object.
    /// @param[in] obj Object.
    /// @return Type of collision.
    CollisionType detectCollision(const CollisionObject &obj) const;

private:
    DISALLOW_COPY_AND_ASSIGN(CollisionObject);
};

}

#endif // PHYSICS_COLLISION_OBJECT_HPP
