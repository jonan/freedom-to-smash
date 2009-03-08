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
OBJECTS = boot.o main.o
LIBRARIES = OGRE
CC = g++ -Wall -Wno-deprecated -g -c
CFLAGS = $(shell pkg-config --cflags $(LIBRARIES))
LIBS = $(shell pkg-config --libs $(LIBRARIES))

# Headers dependencies
BOOT = boot.hpp

# Build dependencies
freedom-to-smash: $(OBJECTS)
	g++ -Wall -Wno-deprecated -g $(OBJECTS) $(CFLAGS) $(LIBS) -o freedom-to-smash

boot.o: boot.cpp $(BOOT)
	$(CC) $(CFLAGS) boot.cpp

main.o: main.cpp $(BOOT)
	$(CC) $(CFLAGS) main.cpp

# Make options
.PHONY : all clean

all: clean
	make

clean:
	rm -f freedom-to-smash *~ *.o
