#include "Sprite.h"

Sprite::Sprite()
{
	m_image = nullptr;
	m_imageCel = 0;
	m_animationVelocity = 0.5f;
	m_isAnimated = false;
	m_isAnimationLooping = false;
	m_isAnimationDead = false;


	m_dimension = { 0,0 };
	m_spriteDimension = { 0,0 };
	m_imageDimension = { 0,0 };

}
Sprite::~Sprite()
{
}
//============================================================================
void Sprite::IsAnimated(bool flag)
{
	m_isAnimated = flag;
}
//============================================================================
void Sprite::IsAnimationLooping(bool flag)
{
	m_isAnimationLooping = flag;
}
//============================================================================
void Sprite::SetImageCel(int column, int row)
{
	m_imageCel = ((row - 1) * m_imageDimension.x) + (column - 1);
}
//============================================================================
void Sprite::SetAnimationVelocity(float velocity)
{
	m_animationVelocity = velocity;
}
//============================================================================
void Sprite::SetSpriteDimension(int width, int height)
{
	m_spriteDimension.x = width;
	m_spriteDimension.y = height;

}
//============================================================================
void Sprite::SetImageDimension(int columns, int rows, int width, int height)
{
	m_imageDimension.x = columns;
	m_imageDimension.y = rows;

	m_dimension.x = width / columns;
	m_dimension.y = height / rows;

}
//============================================================================
bool Sprite::Load(const std::string& filename)
{
	SDL_Surface* rawImageData = IMG_Load(filename.c_str());

	if (!rawImageData)
	{
		//std::cout << "Error loading image file." << std::endl;
		return false;
	}
	m_image = SDL_CreateTextureFromSurface(Screen::Instance()->GetRenderer(), rawImageData);

	return true;
}
SDL_Point Sprite::GetSpriteDimension()
{
	return m_spriteDimension;
}
//============================================================================
void Sprite::Unload()
{
	//SDL_DestroyTexture(m_image);
}
//============================================================================
void Sprite::Update()
{
	if (m_isAnimated)
	{
		static float total = 0.0f;
		total += 0.1f;

		m_imageCel = static_cast<int>(total * m_animationVelocity) % (m_imageDimension.x * m_imageDimension.y);


		if (!m_isAnimationLooping && m_imageCel == (m_imageDimension.x * m_imageDimension.y - 1))
		{
			m_isAnimationDead = true;
		}
	}
}
//============================================================================
void Sprite::Render(int xPos, int yPos, double angle, Flip flip)
{
	if (!m_isAnimationDead)
	{
		SDL_Rect sourceRect;
		SDL_Rect targetRect;

		sourceRect.x = (m_imageCel % m_imageDimension.x) * m_dimension.x;
		sourceRect.y = (m_imageCel / m_imageDimension.x) * m_dimension.y;
		sourceRect.w = m_dimension.x;
		sourceRect.h = m_dimension.y;

		targetRect.x = xPos;
		targetRect.y = yPos;
		targetRect.w = m_spriteDimension.x;
		targetRect.h = m_spriteDimension.y;


		SDL_Point cente{ static_cast<int>(m_spriteDimension.x * 0.5f), static_cast<int>(m_spriteDimension.y * 0.5f) };

		SDL_RenderCopyEx(Screen::Instance()->GetRenderer(), m_image, &sourceRect,
			&targetRect, angle, &cente, static_cast<SDL_RendererFlip>(flip));
	}
}

