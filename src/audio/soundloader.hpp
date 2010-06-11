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

#ifndef AUDIO_SOUNDLOADER_HPP
#define AUDIO_SOUNDLOADER_HPP

#include <AL/al.h>

namespace audio {

class SoundLoader {
public:
    /** Loads a wav sound file from the path.
        @return the buffer with the wav sound loaded */
    //static void loadWAV(const char* path, ALuint &buffer);
    /** Loads a ogg sound file from the path.
        @return the buffer with the ogg sound loaded */
    static void loadOgg(const char* path, ALuint &buffer);
private:
    SoundLoader() {}
};

}

#endif // SOUNDLOADER_HPP
