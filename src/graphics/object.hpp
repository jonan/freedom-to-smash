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
/// The Object class.
/// @author Jonan

#ifndef GRAPHICS_OBJECT_HPP
#define GRAPHICS_OBJECT_HPP

#include <list>

#include "physics/object.hpp"
#include "util.hpp"

namespace Ogre {
    class Entity;
    class SceneNode;
    class SceneManager;
    class Vector3;
}

namespace graphics {

/// General object class.
class Object : public physics::Object {
public:
    explicit Object(Ogre::SceneManager &scene_manager, const int num_animations = 0); // Constructor
    virtual ~Object(void); // Destructor

    // @{
    /// Set functions.
    void setEntity   (const String &name);
    void setPosition (const Ogre::Vector3 &pos);
    void setScale    (const Ogre::Vector3 &scale);
    // @}

    // @{
    /// Get functions.
    const Ogre::Vector3& getPosition (void) const;
    // @}

    /// Move the object.
    /// @param[in] x Units to move in the x axes.
    /// @param[in] y Units to move in the y axes.
    /// @param[in] z Units to move in the z axes.
    void translate(const Real &x, const Real &y, const Real &z);

    /// Attachs an new entity to a bone of the objects main entity.
    /// @param[in] entity_name Name of the new entity.
    /// @param[in] bone_name Name of the main entity's bone.
    void attachEntityToBone(const String &entity_name, const String &bone_name);

protected:
    // Creates a new entity and returns a pointer to it.
    Ogre::Entity* createEntity(const String &name);

    //
    void createAnimation(const int type, const String &name, const bool loop = false, const bool enabled = false);

    //
    bool performAnimation(const int type, const Ogre::FrameEvent &event);

    Ogre::Entity *entity;
    Ogre::SceneNode *node;
    Ogre::SceneManager *scene_manager;

    std::list<Ogre::AnimationState*> *animations;
    std::list<Ogre::Entity*> attached_entities;

private:
    DISALLOW_COPY_AND_ASSIGN(Object);
};

} // namespace graphics

#endif // GRAPHICS_OBJECT_HPP
