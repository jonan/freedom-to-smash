#include "soundbuffer.hpp"

#include <string.h>
#include "soundloader.hpp"

SoundBuffer::SoundBuffer(const char* name, const char* path, const char* extension)
{
    this->mName = strdup(name);
    // Generate Buffer
    alGenBuffers(1, &mBuffer);
    //if (strcmp(extension,".wav"))
        SoundLoader::loadWAV(path, mBuffer);
    //else
    //if (strcmp(extension,".ogg"))
        //SoundLoader::loadOgg(path, mBuffer);
    //else;
        // Unknown Filetype
}

SoundBuffer::~SoundBuffer()
{
    alDeleteBuffers(1, &mBuffer);
}
