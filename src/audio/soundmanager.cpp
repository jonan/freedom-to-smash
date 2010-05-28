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

#include "soundmanager.hpp"

#include <stdio.h>
#include <stdlib.h>
using namespace audio;

SoundManager* SoundManager::getInstance()
{
    static SoundManager instance;
    return &instance;
}

SoundManager::SoundManager() : volume(1.0f)
{
    // Initialize OpenAL
    if (init() == EXIT_FAILURE)
        exit(-1);
    // Init Resource Manager
    mResourceManager = SoundResources::getInstance();
}

SoundManager::~SoundManager()
{
    // Stop & delete all sources before exiting
    std::list<SoundSource*>::iterator it;
    for( it = mSourceList.begin(); it != mSourceList.end(); it++ )
    {
        delete (*it); // stop playing && delete source
    }
    mSourceList.clear();

    // Delete all buffers created
    mResourceManager->unloadAllBuffers();

    // Exit OpenAL
    alcMakeContextCurrent(NULL); // Deatach Context
    if (mContext) alcDestroyContext(mContext);
    if (mDevice)  alcCloseDevice(mDevice);
}

void SoundManager::setSourceFolder(const char* path)
{
    mResourceManager->setResourceFolder(path);
}

SoundSource* SoundManager::createSource(const char* sourceName, const char* songFile)
{
    ALuint *buffer = mResourceManager->getSound(songFile)->buffer();
    SoundSource *source = new SoundSource(sourceName, buffer);
    source->setVolume(volume);
    mSourceList.push_back(source);
    return source;
}

void SoundManager::setVolume(ALfloat vol)
{
    volume = vol;
    // Set all sources volume
    std::list<SoundSource*>::iterator it;
    for( it = mSourceList.begin(); it != mSourceList.end(); it++ )
    {
        (*it)->setVolume(volume);
    }
}

bool SoundManager::init()
{
    // INITIALIZE OPENAL

    // Open Default Device
    mDevice = alcOpenDevice(NULL);
    if (mDevice == NULL)
        return EXIT_FAILURE;

    // Create Context
    mContext = alcCreateContext (mDevice, NULL);
    if (mContext == NULL)
    {
        alcCloseDevice (mDevice);
        return EXIT_FAILURE;
    }
    if (!alcMakeContextCurrent (mContext))
    {
        alcDestroyContext (mContext);
        alcCloseDevice (mDevice);
        return EXIT_FAILURE;
    }

    // Check if any error
    if (alGetError() != AL_NO_ERROR)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
