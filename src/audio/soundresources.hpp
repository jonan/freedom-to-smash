#ifndef AUDIO_SOUNDRESOURCES_HPP
#define AUDIO_SOUNDRESOURCES_HPP

#include "soundbuffer.hpp"
#include "../util.hpp"
#include <list>

namespace audio {

class SoundResources {
public:
    static SoundResources* getInstance();
    ~SoundResources();

    /// Set the resource folder where load files
    void setResourceFolder(const char* path) { defaultLocation = path;}

    /// Load and especific sound & return its buffer
    /// @return Loaded SoundBuffer
    SoundBuffer* loadSound(const char* name,
                           const char* extension = ".wav");

    /// Look if sound its loaded & return its buffer,
    /// in case the sound its not loaded this funcion will load it
    /// @return Loaded SoundBuffer
    SoundBuffer* getSound(const char* name,
                           const char* extension = ".wav");

    void unloadAllBuffers();

private:
    SoundResources();

    // List of Buffer sounds
    std::list<SoundBuffer*> mBufferList;
    Ogre::String defaultLocation;
};

}
#endif // SOUNDRESOURCES_HPP
