#include "Screen.h"
#include <SDL.h>
#include <iostream>



bool Screen::Initialize(const std::string& windowTitle, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "error initalizing SDL." << std::endl;
		return false;
	}
	window = SDL_CreateWindow(windowTitle.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_RESIZABLE);
	if (!window)
	{
		std::cout << "error initalizing SDL." << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!renderer)
	{
		std::cout << "Error creating renderer." << std::endl;
		return false;
	}
	return true;
}
//========================================================================================================
void Screen::Clear()
{
	SDL_RenderClear(renderer);
}
//========================================================================================================
void Screen::Present()
{
	SDL_RenderPresent(renderer);
}
//========================================================================================================
void Screen::Shutdown()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
//========================================================================================================
Screen* Screen::Instance()
{
	static Screen* screenObject = new Screen();
	return screenObject;
}
//========================================================================================================
SDL_Window* Screen::GetWindow()
{
	return window;
}
//========================================================================================================
SDL_Renderer* Screen::GetRenderer()
{
	return renderer;
}
