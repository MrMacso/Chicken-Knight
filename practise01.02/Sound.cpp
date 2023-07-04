#include "Sound.h"

Sound::Sound()
{
}

bool Sound::Load(const std::string& filename)
{
	m_sound = Mix_LoadWAV(filename.c_str());

	if (!m_sound)
	{
		std::cout << "Error loading audio system. " << std::endl;
		return false;
	}
	return true;
}
//===================================================================================
void Sound::Unload()
{
	Mix_FreeChunk(m_sound);
}
//===================================================================================
void Sound::Play(int loop)
{
	if (Mix_PlayChannel(-1, m_sound, loop) == -1)
	{
		std::cout << "error" << std::endl;
	}
}
//===================================================================================
void Sound::SetVolume(int volume)
{
	Mix_VolumeChunk(m_sound, volume);
}
