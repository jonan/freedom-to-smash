#include "soundloader.hpp"

#include <SDL/SDL_audio.h> // Temporal Testing Solution

SoundLoader::SoundLoader()
{
}

void SoundLoader::loadWAV(const char* path, ALuint &buffer)
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
}


void SoundLoader::loadOgg(const char* path, ALuint &buffer)
{
    // Not implemented yet
}

//@} load Song
/*ALsizei size,freq;
ALenum 	format;
ALvoid 	*data;
alutLoadWAVFile("../a.wav",&format,&data,&size,&freq);
alBufferData(buffer[0],format,data,size,freq);
alutUnloadWAV(format,data,size,freq);*/
