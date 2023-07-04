#pragma once
#include <iostream>
#include <SDL_mixer.h>
#include <string>
class Sound
{

public:
	Sound();

	bool Load(const std::string& filename);
	void Unload();
	void Play(int loop);
	void SetVolume(int volume);

private:

	Mix_Chunk* m_sound;
};

