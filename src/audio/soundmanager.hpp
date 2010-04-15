#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include <AL/al.h>
#include <AL/alc.h>
#include "soundresources.hpp"
#include "soundsource.hpp"

namespace audio {

class SoundManager {
public:
    static SoundManager* getInstance();
    ~SoundManager();

    void createSource(const char* name, const char* songName, const char* extension=".wav");


protected:
    SoundManager();
    bool init();
    void foo();

    // OpenAL vars
    ALCdevice *mDevice;
    ALCcontext *mContext;
    // Listener Values
    ALfloat mListenerPos[3];
    ALfloat mListenerVel[3];
    ALfloat mListenerOri[6];
    // Background Values
    ALfloat mBackgroundPos[3];
    ALfloat mBackgroundVel[3];
    ALuint  mBackgrondSrc;

    // ResourceManager
    SoundResources *mResourceManager;
    // SoundSourcesList
};

}

#endif // SOUNDMANAGER_HPP
