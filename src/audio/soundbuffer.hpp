#ifndef SOUNDBUFFER_HPP
#define SOUNDBUFFER_HPP

#include <AL/al.h>

namespace audio {

class SoundBuffer {
public:
    SoundBuffer(const char* name, const char* path, const char* extension);
    ~SoundBuffer();

    const char* getName() { return mName;}
    ALuint* buffer() { return &mBuffer;}

private:
    const char* mName;
    ALuint mBuffer;
};

}
#endif // SOUNDBUFFER_HPP
