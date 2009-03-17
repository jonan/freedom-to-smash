# This file is part of Freedom to Smash.
# Copyright (C) 2009 Jon Ander Peñalba <jonan88@gmail.com>
#
# Freedom to Smash is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 3 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>

# Global variables
OBJECTS = battle_ground.o boot.o character.o input.o main.o server.o
LIBRARIES = OGRE OIS
CC = g++ -Wall -Wno-deprecated -g -c
CFLAGS = $(shell pkg-config --cflags $(LIBRARIES))
LIBS = $(shell pkg-config --libs $(LIBRARIES)) -lenet

# Headers dependencies
BATTLE_GROUND = battle_ground.hpp $(MACROS)
BOOT = boot.hpp
CHARACTER = character.hpp $(MACROS)
INPUT = input.hpp $(MACROS)
INPUT_SYSTEMS = input_systems.hpp
MACROS = macros.hpp
SERVER = server.hpp $(BATTLEGROUND) $(MACROS)

# Build dependencies
freedom-to-smash: $(OBJECTS)
	g++ -Wall -Wno-deprecated -g $(OBJECTS) $(CFLAGS) $(LIBS) -o freedom-to-smash

battle_ground.o: battle_ground.cpp $(BATTLE_GROUND) $(CHARACTER) $(INPUT_SYSTEMS)
	$(CC) $(CFLAGS) battle_ground.cpp

boot.o: boot.cpp $(BOOT) $(INPUT)
	$(CC) $(CFLAGS) boot.cpp

character.o: character.cpp $(CHARACTER) $(INPUT_SYSTEMS)
	$(CC) $(CFLAGS) character.cpp

input.o: input.cpp $(INPUT) $(INPUT_SYSTEMS)
	$(CC) $(CFLAGS) input.cpp

main.o: main.cpp $(BOOT) $(SERVER)
	$(CC) $(CFLAGS) main.cpp

server.o: server.cpp $(SERVER)
	$(CC) $(CFLAGS) server.cpp

# Make options
.PHONY : all clean

all: clean
	make

clean:
	rm -f freedom-to-smash *~ *.o
