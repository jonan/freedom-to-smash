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

#include <physics/object_synchronizer.hpp>

// FtS
#include <physics/converter_functions.hpp>

namespace physics {

// Get the object's position.
void ObjectSynchronizer::getWorldTransform(btTransform &transform) const
{
    transform.setOrigin(vector3(getGraphicalPosition()));
}

// Set the object's position.
void ObjectSynchronizer::setWorldTransform(const btTransform &transform)
{
    setGraphicalPosition(vector3(transform.getOrigin()));
}

} // namespace physics
