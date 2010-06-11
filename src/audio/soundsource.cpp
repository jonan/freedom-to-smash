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

#include "soundsource.hpp"

#include <string.h>
using namespace audio;

SoundSource::SoundSource(const char* name, ALuint *buffer)
{
    this->name = strdup(name);
    alGenSources(1, &mSource);
    alSourcei(mSource, AL_BUFFER, *buffer);
    setVolume(1.0f);
}

SoundSource::~SoundSource()
{
    alSourceStop(mSource);
    alDeleteSources(1, &mSource);
}
