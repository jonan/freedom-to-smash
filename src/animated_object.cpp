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

#include <boost/foreach.hpp>

#include <OgreAnimationState.h>
#include <OgreEntity.h>
#include <OgreFrameListener.h>

// Constructor
AnimatedObject::AnimatedObject(Ogre::SceneManager &scene_manager, const int num_animations)
        : Object(scene_manager)
{
    animations = new std::list<Ogre::AnimationState*>[num_animations];
}

// Destructor
AnimatedObject::~AnimatedObject(void)
{
    delete [] animations;
}

// Attachs an new entity to a bone of the objects main entity.
void AnimatedObject::attachEntityToBone(const String &entity_name, const String &bone_name)
{
    attached_entities.push_back(createEntity(entity_name));
    entity->attachObjectToBone(bone_name, attached_entities.back());
}

//
void AnimatedObject::createAnimation(const int type, const char *name, const bool loop, const bool enabled)
{
    animations[type].push_back(entity->getAnimationState(name));
    animations[type].back()->setLoop(loop);
    animations[type].back()->setEnabled(enabled);
}

//
bool AnimatedObject::performAnimation(const int type, const Ogre::FrameEvent &event)
{
    bool end = false;
    BOOST_FOREACH(Ogre::AnimationState *anim, animations[type]) {
        anim->setEnabled(true);
        anim->addTime(event.timeSinceLastFrame);
        if (anim->hasEnded()) {
            end = true;
        }
    }
    return end;
}
