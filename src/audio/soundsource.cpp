#include "soundsource.hpp"

#include <string.h>

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
