/*
 *  This file is part of Freedom to Smash.
 *  Copyright (c) 2009-2010 David G. Miguel <noxwings@gmail.com>
 *
 *  Freedom to Smash is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Freedom to Smash is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Freedom to Smash.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef AUDIO_SOUNDMANAGER_HPP
#define AUDIO_SOUNDMANAGER_HPP

#include <AL/al.h>
#include <AL/alc.h>
#include "soundresources.hpp"
#include "soundsource.hpp"


namespace audio {

class SoundManager {
public:
    static SoundManager* getInstance();
    ~SoundManager();

    void setSourceFolder(const char* path);
    SoundSource* createSource(const char* sourceName, const char* songFile);
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

}

#endif // SOUNDMANAGER_HPP
