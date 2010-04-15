#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include <AL/al.h>
#include <AL/alc.h>
#include "soundresources.hpp"
#include "soundsource.hpp"

class SoundManager {
public:
    static SoundManager* getInstance();
    ~SoundManager();

    void setSourceFolder(const char* path);
    SoundSource* createSource(const char* sourceName, const char* songName, const char* extension=".wav");
    void setVolume(ALfloat vol);

protected:
    SoundManager();
    bool init();

    // OpenAL vars
    ALCdevice *mDevice;
    ALCcontext *mContext;
    ALfloat volume;
    // Listener Values
    ALfloat mListenerPos[3];
    ALfloat mListenerVel[3];
    ALfloat mListenerOri[6];
    // ResourceManager
    SoundResources *mResourceManager;
    std::list<SoundSource*> mSourceList;
};

#endif // SOUNDMANAGER_HPP
