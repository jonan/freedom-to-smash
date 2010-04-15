
#include "soundmanager.hpp"
using namespace audio;

#include <stdio.h>
#include <stdlib.h>


SoundManager* SoundManager::getInstance()
{
    static SoundManager instance;
    return &instance;
}

SoundManager::~SoundManager()
{
    // Stop all sources before exiting
    alSourceStop( mBackgrondSrc );
    // Exit OpenAL
    alcMakeContextCurrent(NULL); // Deatach Context
    //mContext = alcGetCurrentContext();
    //mDevice = alcGetContextsDevice (mContext);
    if (mContext) alcDestroyContext(mContext);
    if (mDevice)  alcCloseDevice(mDevice);
}


void SoundManager::createSource(const char* name, const char* songName, const char* extension)
{
    mResourceManager->loadSound(songName, extension);
}


SoundManager::SoundManager()
{
    // Initialize OpenAL
    if (init() == EXIT_FAILURE)
        exit(-1);
    // Init Resource Manager
    mResourceManager = SoundResources::getInstance();
    foo();
}

bool SoundManager::init()
{
    // INITIALIZE OPENAL

    // Open Default Device
    mDevice = alcOpenDevice (NULL);
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


void SoundManager::foo()
{
    // SOURCE
    alGenSources (1, &mBackgrondSrc);
    alSourcei (mBackgrondSrc, AL_BUFFER, *(mResourceManager->loadSound("HE")->buffer()));
    alSourcePlay (mBackgrondSrc);
}
