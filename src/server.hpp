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
///
/// @author Jonan

#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>

#include <OgreFrameListener.h>

#include "macros.hpp"

class BattleGround;

struct _ENetAddress;
struct _ENetHost;
struct _ENetPeer;

///
class Server : public Ogre::FrameListener {
public:
    static Server* getInstance(void); // Singleton pattern constructor
    ~Server(void); // Destructor

    ///
    void start(void);

private:
    Server(void); // Constructor

    //
    virtual bool frameStarted(const Ogre::FrameEvent &/*event*/);

    BattleGround *ground;

    std::vector<_ENetPeer*> peers;

    _ENetAddress *address;
    _ENetHost *host_server;

    DISALLOW_COPY_AND_ASSIGN(Server);
};

#endif // SERVER_HPP
