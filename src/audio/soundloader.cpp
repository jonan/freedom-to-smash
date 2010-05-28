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

#include "soundloader.hpp"

//#include <SDL/SDL_audio.h>
#include <vorbis/vorbisfile.h>
#include <stdlib.h>
#include <vector>

#define BUFFER_SIZE     32768       // 32 KB buffers

using namespace audio;
using namespace std;


/*void SoundLoader::loadWAV(const char* path, ALuint &buffer)
{
    // Load WAV song
    Uint32 size;
    Uint8 *data;
    SDL_AudioSpec wav_spec;
    SDL_LoadWAV( path, &wav_spec, &data, &size);
    // Load buffer here
    alBufferData(buffer, AL_FORMAT_STEREO16, data, size, wav_spec.freq);
    // Free WAV
    SDL_FreeWAV(data);
}*/

void SoundLoader::loadOgg(const char *path, ALuint &buffer)
{
    FILE *f;
    f = fopen(path, "rb");

    OggVorbis_File oggFile;
    if (ov_open(f, &oggFile, NULL, 0) == 0)
    {
        vorbis_info *pInfo;
        pInfo = ov_info(&oggFile, -1);
        // Chanels & Format        ( always use 16-bit samples )
        ALenum format;
        (pInfo->channels == 1)? format = AL_FORMAT_MONO16 : format = AL_FORMAT_STEREO16;
        // Frequency
        ALsizei freq = pInfo->rate;

        int endian = 0;                         // 0 for Little-Endian, 1 for Big-Endian
        int bitStream;
        long bytes;
        char array[BUFFER_SIZE];                // Local fixed size array
        vector<char> bufferData;

        do
        {
            // Read up to a buffer's worth of decoded sound data
            bytes = ov_read(&oggFile, array, BUFFER_SIZE, endian, 2, 1, &bitStream);
            if (bytes < 0)
            {
                ov_clear(&oggFile);
                exit(-1);
            }
            // Append to end of buffer
            bufferData.insert(bufferData.end(), array, array + bytes);
        }
        while (bytes > 0);

        // Turn into al buffer
        alBufferData(buffer, format, &bufferData[0], static_cast<ALsizei>(bufferData.size()), freq);

        // Clean up!
        ov_clear(&oggFile);
    }
}

//@} load Song
/*ALsizei size,freq;
ALenum 	format;
ALvoid 	*data;
alutLoadWAVFile("../a.wav",&format,&data,&size,&freq);
alBufferData(buffer[0],format,data,size,freq);
alutUnloadWAV(format,data,size,freq);*/
