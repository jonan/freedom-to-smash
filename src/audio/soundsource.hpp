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
    void setVolume(ALfloat num) { alSourcef(mSource, AL_GAIN, num);}


private:
    const char* name;
    ALuint *mBuffer;
    ALuint  mSource;
    ALfloat mPosition[3];
    ALfloat mVelocity[3];
};

#endif // SOUNDSOURCE_HPP
