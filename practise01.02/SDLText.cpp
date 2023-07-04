#include "SDLText.h"
#include <iostream>

bool SDLText::Initialize()
{
    if (TTF_Init() == 1)
    {
        std::cout << "Error initializing font system." << std::endl;
        return false;
    }
    return true;
}
//==============================================================================
void SDLText::Shutdown()
{
    TTF_Quit();
}
//==============================================================================
SDLText::SDLText()
{
    m_font = nullptr;
    m_isDirty = true;
    m_color = { 255, 255, 255, 255 };
    m_dimension = { 10, 10 };
    //assets/text/fontbold.ttf

}
//==============================================================================
SDLText::~SDLText()
{

}
//==============================================================================
void SDLText::SetText(const std::string text)
{
    m_text = text;
    m_isDirty = true;
}
//==============================================================================
void SDLText::SetColor(const SDL_Color& color)
{
    m_color = color;
    m_isDirty = true;
}
//==============================================================================
void SDLText::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    m_color.r = r;
    m_color.g = g;
    m_color.b = b;
    m_color.a = a;
    m_isDirty = true;
}
//==============================================================================
void SDLText::SetDimension(int width, int height)
{
    m_dimension = { width, height };
}
//==============================================================================
bool SDLText::Load(const char* filename, int fontsize)
{
    m_font = TTF_OpenFont(filename, fontsize);
    //.c_str()
    //const std::string&
    if (!m_font)
    {
        std::cout << "Error loading file." << std::endl;
        return false;
    }

    return true;
}
//==============================================================================
void SDLText::Render(int xPos, int yPos)
{
    SDL_Rect targetRect;

    targetRect.x = xPos;
    targetRect.y = yPos;
    targetRect.w = m_dimension.x;
    targetRect.h = m_dimension.y;

    if (m_isDirty)
    {
        SDL_DestroyTexture(m_texture);
        SDL_Surface* textData = TTF_RenderText_Blended(m_font, m_text.c_str(), m_color);
        m_texture = SDL_CreateTextureFromSurface(Screen::Instance()->GetRenderer(), textData);
        SDL_FreeSurface(textData);
        m_isDirty = false;

    }
    SDL_RenderCopy(Screen::Instance()->GetRenderer(), m_texture, nullptr, &targetRect);
}
//==============================================================================
void SDLText::Unload()
{
    TTF_CloseFont(m_font);
}

