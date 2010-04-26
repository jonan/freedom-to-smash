#include "soundbuffer.hpp"

#include <string.h>
#include "soundloader.hpp"

#include <stdio.h>

using namespace audio;

SoundBuffer::SoundBuffer(const char* name, const char* path, const char* extension)
{
    this->mName = strdup(name);
    printf("%s\n",path);
    printf("extension: %s\n",extension);

    // Generate Buffer
    alGenBuffers(1, &mBuffer);
    // Load & decode
    if (strcmp(extension,".wav")==0)
        SoundLoader::loadWAV(path, mBuffer);
    else
    if (strcmp(extension,".ogg")==0)
        SoundLoader::loadOgg(path, mBuffer);
}

SoundBuffer::~SoundBuffer()
{
    alDeleteBuffers(1, &mBuffer);
}
