#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Screen.h"

class SDLText
{
public:
	static bool Initialize();
	static void Shutdown();

	SDLText();
	~SDLText();

	void SetText(const std::string text);
	void SetColor(const SDL_Color& color);
	void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void SetDimension(int width, int height);

	bool Load(const char* filename, int fontsize);
	void Render(int xPos, int yPos);
	void Unload();


private:

	bool m_isDirty;
	std::string m_text;

	TTF_Font* m_font;
	SDL_Color m_color;
	SDL_Point m_dimension;
	SDL_Texture* m_texture;
};

