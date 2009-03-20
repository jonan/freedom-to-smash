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

#include "server.hpp"

#include <enet/enet.h>

// Singleton pattern constructor
Server* Server::getInstance(void) {
  static Server instance;
  return &instance;
}

// Destructor
Server::~Server(void) {
  enet_deinitialize();
  enet_host_destroy(host_server);
}

// 
void Server::start(void) {
  Ogre::Root::getSingleton().addFrameListener(this);
  ground->start();
}

// Constructor
Server::Server(void) {
  enet_initialize();
  address = new ENetAddress;
  address->host = ENET_HOST_ANY;
  address->port = 3366;
  host_server = enet_host_create(address,4,0,0);
  ground = new BattleGround;
}

// 
bool Server::frameStarted(const Ogre::FrameEvent& /*event*/) {
  ENetEvent event;

  while ( enet_host_service(host_server, &event, 0) > 0 ) {
    switch (event.type) {
      case ENET_EVENT_TYPE_CONNECT:
        peers.push_back(event.peer);
        break;
      case ENET_EVENT_TYPE_RECEIVE:
        enet_packet_destroy(event.packet);
        break;
      case ENET_EVENT_TYPE_DISCONNECT:
        break;
      case ENET_EVENT_TYPE_NONE:
        // Impossible case, just to avoid compiler warnings
        break;
    }
  }

  return true;
}
