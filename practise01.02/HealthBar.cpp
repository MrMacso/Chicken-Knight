#include "HealthBar.h"

HealthBar::~HealthBar()
{
}

void HealthBar::CreateHealthBar(int health)
{
	int image = 1;

	auto createImage = [&image](Sprite& image, std::string location)
	{
		image.Load(location);
		image.SetImageDimension(1, 1, 400, 50);
		image.SetSpriteDimension(400, 50);
		image.IsAnimated(true);
		image.IsAnimationLooping(true);
	};
	createImage(m_back, "assets/images/Back.png");
	createImage(m_bar, "assets/images/Bar.png");
	createImage(m_border, "assets/images/Boarder.png");
	SetCurrentHealth(health);
}

void HealthBar::SetHealthBarPosition(float x, float y)
{
	SetPosition(x, y);
}


void HealthBar::SetCurrentHealth(int health)
{
	m_currentHealth = health;
}

void HealthBar::ConnectHealthToBar(int& health)
{
	SetCurrentHealth(health);
	//float normalizedHealth = m_currentHealth / m_maxHealth;
	m_bar.SetSpriteDimension(health * 4, m_bar.GetSpriteDimension().y);
}

void HealthBar::Update(int health)
{
	ConnectHealthToBar(health);
}

void HealthBar::Render()
{
	int posX = static_cast<int>(m_position.x);
	int posY = static_cast<int>(m_position.y);
	m_back.Render(posX, posY, m_angle);
	m_bar.Render(posX, posY, m_angle);
	m_border.Render(posX, posY, m_angle);
}
