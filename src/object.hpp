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

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "physics/collision_object.hpp"
#include "util.hpp"

namespace Ogre {
    class Entity;
    class SceneNode;
    class SceneManager;
    class Vector3;
}

/// General object class.
class Object : public physics::CollisionObject {
public:
    explicit Object(Ogre::SceneManager &scene_manager); // Constructor
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

protected:
    // Creates a new entity and returns a pointer to it.
    Ogre::Entity* createEntity(const String &name);

    Ogre::Entity *entity;
    Ogre::SceneNode *node;
    Ogre::SceneManager *scene_manager;

private:
    DISALLOW_COPY_AND_ASSIGN(Object);
};

#endif // OBJECT_HPP
