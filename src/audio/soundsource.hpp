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

#ifndef AUDIO_SOUNDSOURCE_HPP
#define AUDIO_SOUNDSOURCE_HPP

#include <AL/al.h>

namespace audio {

class SoundSource {
public:
    SoundSource(const char* name, ALuint *buffer);
    ~SoundSource();

    void play() { alSourcePlay(mSource);}
    void pause() { alSourcePause(mSource);}
    void stop() { alSourceStop(mSource);}
    void setVolume(ALfloat num) { alSourcef(mSource, AL_GAIN, num);}
    void setLoop(bool enable) { alSourcei(mSource, AL_LOOPING, enable);}

private:
    const char* name;
    ALuint *mBuffer;
    ALuint  mSource;
    ALfloat mPosition[3];
    ALfloat mVelocity[3];
};

}
#endif // SOUNDSOURCE_HPP
