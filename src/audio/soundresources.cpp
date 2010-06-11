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

#include "soundresources.hpp"
using namespace audio;

SoundResources* SoundResources::getInstance()
{
    static SoundResources instance;
    return &instance;
}

SoundResources::~SoundResources()
{
    unloadAllBuffers();
}

SoundBuffer* SoundResources::loadSound(const char* fileName)
{
    std::string path = defaultLocation; path += fileName;
    SoundBuffer* buffer = new SoundBuffer(fileName, path.c_str());
    mBufferList.push_back(buffer);
    return buffer;
}

SoundBuffer* SoundResources::getSound(const char* fileName)
{
    std::string temp = fileName;

    std::list<SoundBuffer*>::iterator it;
    // Find name ocurrences in buffer list
    for( it = mBufferList.begin(); it != mBufferList.end(); it++ )
    {
        if (temp == (*it)->getName())
            return *it;
    }
    return loadSound(fileName);
}

void SoundResources::unloadAllBuffers()
{
    // Delete buffers
    std::list<SoundBuffer*>::iterator it;
    for( it = mBufferList.begin(); it != mBufferList.end(); it++ )
    {
        delete (*it);
    }
    // Clear List
    mBufferList.clear();
}

SoundResources::SoundResources()
{
    defaultLocation = "./media/sound/";
}
