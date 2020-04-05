#include "Sound.h"

#include <iostream>
// sound lib
#include <bass.h>

bool Sound::audio_device = false;

Sound::Sound(const char * filename)
{
	// init 
	if(!audio_device)
	{
		if(!BASS_Init(-1, 44100, 0, NULL,NULL))
		{
			printf("erorr loading sound file \n");
		}
		audio_device = true;
	}

	channel = BASS_StreamCreateFile(false,filename, 0,0, BASS_SAMPLE_LOOP);

	if(!channel)
	{
		printf("can't play file \n");
	}
}

Sound::~Sound()
{
	BASS_Free();
}

void Sound::play()
{
	BASS_ChannelPlay(channel, false);
}

void Sound::pause()
{
	BASS_ChannelPause(channel);
}

void Sound::stop()
{
	BASS_ChannelStop(channel);
}
