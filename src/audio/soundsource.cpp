#include "soundsource.hpp"

SoundSource::SoundSource()
{
    alGenSources(1, &mSource);
    alSourcei(mSource, AL_BUFFER, *buffer);
}

SoundSource::~SoundSource()
{
    alDeleteSources(1, &mSource);
}
