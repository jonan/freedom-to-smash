#ifndef SOUNDRESOURCES_HPP
#define SOUNDRESOURCES_HPP

#include "soundbuffer.hpp"
#include <list>

namespace audio {

class SoundResources {
public:
    static SoundResources* getInstance();
    ~SoundResources();

    SoundBuffer* loadSound(const char* name,
                           const char* extension = ".wav",
                           const char* location = "../sound/");
    SoundBuffer* getSound(const char* name);

private:
    SoundResources();


    std::list<SoundBuffer*> mBufferList;
};

}

#endif // SOUNDRESOURCES_HPP
