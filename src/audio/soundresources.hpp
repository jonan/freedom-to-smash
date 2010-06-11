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

#ifndef AUDIO_SOUNDRESOURCES_HPP
#define AUDIO_SOUNDRESOURCES_HPP

#include "soundbuffer.hpp"
#include <list>
#include <string>


namespace audio {

class SoundResources {
public:
    static SoundResources* getInstance();
    ~SoundResources();

    /// Set the resource folder where load files
    void setResourceFolder(const char* path) { defaultLocation = path;}

    /// Load and especific sound & return its buffer
    /// @return Loaded SoundBuffer
    SoundBuffer* loadSound(const char* fileName);

    /// Look if sound its loaded & return its buffer,
    /// in case the sound its not loaded this funcion will load it
    /// @return Loaded SoundBuffer
    SoundBuffer* getSound(const char* filename);

    void unloadAllBuffers();

private:
    SoundResources();

    // List of Buffer sounds
    std::list<SoundBuffer*> mBufferList;
    std::string defaultLocation;
};

}
#endif // SOUNDRESOURCES_HPP
