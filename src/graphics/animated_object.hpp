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
/// The AnimatedObject class.
/// @author Jonan

#ifndef GRAPHICS_ANIMATED_OBJECT_HPP
#define GRAPHICS_ANIMATED_OBJECT_HPP

#include <list>

#include "object.hpp"

namespace Ogre {
    class AnimationState;
}

namespace graphics {

/// An AnimatedObject is a normal Object with animations.
class AnimatedObject : public Object {
public:
    AnimatedObject(Ogre::SceneManager &scene_manager, const int num_animations); // Constructor
    ~AnimatedObject(void); // Destructor

    /// Attachs an new entity to a bone of the objects main entity.
    /// @param[in] entity_name Name of the new entity.
    /// @param[in] bone_name Name of the main entity's bone.
    void attachEntityToBone(const String &entity_name, const String &bone_name);

protected:
    //
    void createAnimation(const int type, const String &name, const bool loop = false, const bool enabled = false);

    //
    bool performAnimation(const int type, const Ogre::FrameEvent &event);

    std::list<Ogre::AnimationState*> *animations;
    std::list<Ogre::Entity*> attached_entities;

private:
    DISALLOW_COPY_AND_ASSIGN(AnimatedObject);
};

} // namespace graphics

#endif // GRAPHICS_ANIMATED_OBJECT_HPP
