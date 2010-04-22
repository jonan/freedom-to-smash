#ifndef SOUNDLOADER_HPP
#define SOUNDLOADER_HPP

#include <AL/al.h>

namespace audio {

class SoundLoader {
public:
    static void loadWAV(const char* path, ALuint &buffer);
    static void loadOgg(const char* path, ALuint &buffer);
private:
    SoundLoader();
};

}

#endif // SOUNDLOADER_HPP
