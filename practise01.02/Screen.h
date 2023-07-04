#pragma once

#include <string>
#include <SDL.h>

class Screen
{
public:
	static Screen* Instance();

	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();
	bool Initialize(const std::string& windowTitle = "<No name>", int width = 1280, int height = 720);
	void Clear();
	void Present();
	void Shutdown();


private:
	Screen() {}
	Screen(const Screen&);
	Screen& operator=(const Screen&);

	SDL_Renderer* renderer{ nullptr };
	SDL_Window* window{ nullptr };

};

