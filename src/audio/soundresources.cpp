#include "soundresources.hpp"

#include <string>
using namespace audio;


SoundResources* SoundResources::getInstance()
{
    static SoundResources instance;
    return &instance;
}

SoundResources::~SoundResources()
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

SoundBuffer* SoundResources::loadSound(const char* name, const char* extension, const char* location)
{
    std::string path = location; path += name; path += extension;
    SoundBuffer* buffer = new SoundBuffer(name, path.c_str(), extension);
    mBufferList.push_back(buffer);
    return buffer;
}

SoundBuffer* SoundResources::getSound(const char* name)
{
    std::string temp = name;
    std::list<SoundBuffer*>::iterator it;
    // Find name ocurrences in buffer list
    for( it = mBufferList.begin(); it != mBufferList.end(); it++ )
    {
        if (temp == (*it)->getName())
            return *it;
    }
    return loadSound(name);
}

SoundResources::SoundResources()
{
}
