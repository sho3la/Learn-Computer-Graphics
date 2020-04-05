#pragma once

class Sound
{
public:
	Sound(const char* filename);

	~Sound();

	void play();

	void pause();

	void stop();

private:
	unsigned int channel;

	static bool audio_device;
};