
#include "soundmanager.hpp"

#include <stdio.h>
#include <stdlib.h>


SoundManager* SoundManager::getInstance()
{
    static SoundManager instance;
    return &instance;
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

    // Exit OpenAL
    alcMakeContextCurrent(NULL); // Deatach Context
    if (mContext) alcDestroyContext(mContext);
    if (mDevice)  alcCloseDevice(mDevice);
}

void SoundManager::setSourceFolder(const char* path)
{
    mResourceManager->setResourceFolder(path);
}

SoundSource* SoundManager::createSource(const char* sourceName, const char* songName, const char* extension)
{
    ALuint *buffer = mResourceManager->loadSound(songName, extension)->buffer();
    SoundSource *source = new SoundSource("HE", buffer);
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

SoundManager::SoundManager() : volume(1.0f)
{
    // Initialize OpenAL
    if (init() == EXIT_FAILURE)
        exit(-1);
    // Init Resource Manager
    mResourceManager = SoundResources::getInstance();
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
