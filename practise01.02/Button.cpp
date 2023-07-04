#include "Button.h"


Button::~Button()
{
	m_image.Unload();
}

void Button::CreateButton(std::string file, std::string hoverfile, int width, int height)
{
	m_image.Load(file);
	m_hoverImage.Load(hoverfile);
	m_image.SetImageDimension(1, 1, width, height);
	m_hoverImage.SetImageDimension(1, 1, width, height);
}

void Button::SetButtonDimension(int width, int height)
{
	m_image.SetSpriteDimension(width, height);
	m_hoverImage.SetSpriteDimension(width, height);
	m_collider.w = width;
	m_collider.h = height;
}

void Button::SetButtonPosition(float width, float height)
{
	SetPosition(width, height);
	m_collider.x = static_cast<int>(width);
	m_collider.y = static_cast<int>(height);
}

SDL_Rect Button::GetCollider()
{
	return m_collider;
}

void Button::Update()
{

}
void Button::Render()
{
	SDL_Point point = Input::Instance()->GetMousePosition();

	if (SDL_PointInRect(&point, &m_collider))
	{
		m_hoverImage.Render(static_cast<int>(m_position.x), static_cast<int>(m_position.y), m_angle);
	}
	else
	{
		m_image.Render(static_cast<int>(m_position.x), static_cast<int>(m_position.y), m_angle);
	}
}
