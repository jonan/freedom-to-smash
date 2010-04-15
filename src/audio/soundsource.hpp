#ifndef SOUNDSOURCE_HPP
#define SOUNDSOURCE_HPP

#include <AL/al.h>

class SoundSource {
public:
    SoundSource(const char* name, ALuint *buffer);
    ~SoundSource();

    void play() { alSourcePlay(mSource);}
    void pause() { alSourcePause(mSource);}
    void stop() { alSourceStop(mSource);}

private:
    // Background Values
    ALfloat mPosition[3];
    ALfloat mVelocity[3];
    ALuint  mSource;
    ALuint *mBuffer;
};

#endif // SOUNDSOURCE_HPP
