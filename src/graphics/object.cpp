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

#include <graphics/object.hpp>

// Boost
#include <boost/foreach.hpp>
// Ogre
#include <OgreEntity.h>
#include <OgreFrameListener.h>
#include <OgreSceneManager.h>

namespace graphics {

// Constructor
Object::Object(Ogre::SceneManager &scene_manager, const int num_animations)
        : entity(NULL)
        , animations(NULL)
        , scene_manager(&scene_manager)
{
    node = scene_manager.getRootSceneNode()->createChildSceneNode();
    if (num_animations)
        animations = new std::list<Ogre::AnimationState*>[num_animations];
}

// Destructor
Object::~Object(void)
{
    delete [] animations;
}

// Set function.
void Object::setEntity(const String &name)
{
    entity = &createEntity(name);
    node->attachObject(entity);
}

// Set function.
void Object::setPosition(const Ogre::Vector3 &pos)
{
    node->setPosition(pos);
}

// Set function.
void Object::setScale(const Ogre::Vector3 &scale)
{
    node->setScale(scale);
}

// Get function.
const Ogre::Vector3& Object::getPosition(void) const
{
    return node->getPosition();
}

// Attachs an new entity to a bone of the objects main entity.
void Object::attachEntityToBone(const String &entity_name, const String &bone_name)
{
    attached_entities.push_back(&createEntity(entity_name));
    entity->attachObjectToBone(bone_name, attached_entities.back());
}

// Move the object.
void Object::translate(const Real &x, const Real &y, const Real &z)
{
    node->translate(x, y, z);
}

// Creates a new entity and returns a pointer to it.
Ogre::Entity& Object::createEntity(const String &name)
{
    bool done = false;
    Ogre::Entity *entity;
    String mesh_name = name + ".mesh";
    String manager_name = name;
    while (!done) {
        try {
            done = true;
            manager_name += ".";
            entity = scene_manager->createEntity(manager_name, mesh_name);
        } catch (Ogre::Exception exception) {
            if (exception.getNumber() == Ogre::Exception::ERR_DUPLICATE_ITEM)
                done = false;
            else
                throw exception;
        }
    }
    entity->setCastShadows(true);
    return *entity;
}

// Creates a new animation.
void Object::createAnimation(const int type, const String &name, const bool loop, const bool enabled)
{
    animations[type].push_back(entity->getAnimationState(name));
    animations[type].back()->setLoop(loop);
    animations[type].back()->setEnabled(enabled);
}

// Advances the animation and returns true if it has ended.
bool Object::performAnimation(const int type, const Ogre::FrameEvent &event)
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

} // namespace graphics
