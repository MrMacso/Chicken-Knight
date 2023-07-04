#pragma once
#include <string>

#include "Input.h"
#include "GameObject.h"
#include "Sprite.h"
class Button :
	public GameObject
{
public:
	~Button();

	void CreateButton(std::string file, std::string hoverfile, int height, int width);
	void SetButtonDimension(int width, int height);
	void SetButtonPosition(float width, float height);
	SDL_Rect GetCollider();
	void Update();
	void Render();

private:
	SDL_Rect m_collider = { 0,0,0,0 };
	Sprite m_image;
	Sprite m_hoverImage;

};