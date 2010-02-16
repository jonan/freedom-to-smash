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

#include "animated_object.hpp"

#include <OgreAnimationState.h>
#include <OgreEntity.h>

// Constructor
AnimatedObject::AnimatedObject(Ogre::SceneManager &scene_manager)
        : Object(scene_manager)
{

}

//
void AnimatedObject::createAnimation(const int type, const char *name, const bool loop, const bool enabled)
{
    animations[type] = entity->getAnimationState(name);
    animations[type]->setLoop(loop);
    animations[type]->setEnabled(enabled);
}
