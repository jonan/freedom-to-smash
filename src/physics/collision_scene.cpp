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

#include "collision_scene.hpp"

namespace physics {

// Constructor
CollisionScene::CollisionScene(void)
        : configuration(new btDefaultCollisionConfiguration)
        , dispatcher(new btCollisionDispatcher(configuration))
{
    broadphase = new btAxisSweep3(btVector3(-1000,-1000,-1000), btVector3(1000,1000,1000));
    world = new btCollisionWorld(dispatcher, broadphase, configuration);
}

// Destructor
CollisionScene::~CollisionScene(void) {
    delete world;
    delete broadphase;
    delete dispatcher;
    delete configuration;
}

} // namespace physics
