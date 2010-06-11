/*
 *  This file is part of Freedom to Smash.
 *  Copyright (c) 2009-2010 David G. Miguel <noxwings@gmail.com>
 *
 *  Freedom to Smash is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Freedom to Smash is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Freedom to Smash.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "soundbuffer.hpp"

#include <string.h>
#include "soundloader.hpp"

#include <stdio.h>

using namespace audio;

SoundBuffer::SoundBuffer(const char* name, const char* path)
{
    this->mName = strdup(name);
    printf("%s\n",path);

    // Generate Buffer
    alGenBuffers(1, &mBuffer);
    // Load & decode
    SoundLoader::loadOgg(path, mBuffer);
}

SoundBuffer::~SoundBuffer()
{
    alDeleteBuffers(1, &mBuffer);
}
