#include "soundresources.hpp"


SoundResources* SoundResources::getInstance()
{
    static SoundResources instance;
    return &instance;
}

SoundResources::~SoundResources()
{
    unloadAllBuffers();
}

SoundBuffer* SoundResources::loadSound(const char* name, const char* extension)
{
    Ogre::String path = defaultLocation;
    path += name; path += extension;
    SoundBuffer* buffer = new SoundBuffer(name, path.c_str(), extension);
    mBufferList.push_back(buffer);
    return buffer;
}

SoundBuffer* SoundResources::getSound(const char* name, const char* extension)
{
    Ogre::String temp = name;

    std::list<SoundBuffer*>::iterator it;
    // Find name ocurrences in buffer list
    for( it = mBufferList.begin(); it != mBufferList.end(); it++ )
    {
        if (temp == (*it)->getName())
            return *it;
    }
    return loadSound(name, extension);
}

void SoundResources::unloadAllBuffers()
{
    // Delete buffers
    std::list<SoundBuffer*>::iterator it;
    for( it = mBufferList.begin(); it != mBufferList.end(); it++ )
    {
        delete (*it);
    }
    // Clear List
    mBufferList.clear();
}

SoundResources::SoundResources()
{
    defaultLocation = "media/sound/";
}
