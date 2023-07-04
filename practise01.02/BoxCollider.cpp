#include "BoxCollider.h"

void BoxCollider::SetPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;

	m_border.Load("assets/images/Colliderborder.png");
	m_border.SetImageDimension(1, 1, 500, 656);

}
void BoxCollider::SetDimension(int width, int height)
{
	m_dimension.x = width;
	m_dimension.y = height;
	m_border.SetSpriteDimension(width, height);
}
Vector2D BoxCollider::GetPosition()
{
	return m_position;
}
Vector2D BoxCollider::GetDimension()
{
	return m_dimension;
}
void BoxCollider::Update()
{
	m_min.x = m_position.x;
	m_min.y = m_position.y;
	m_max.x = m_position.x + m_dimension.x;
	m_max.y = m_position.y + m_dimension.y;
	if (m_isBorderActive)
	{
		m_border.Render(static_cast<int>(m_position.x), static_cast<int>(m_position.y), 0);
	}
}

bool BoxCollider::IsColliding(const BoxCollider& secondBox) const
{
	return (m_max.x > secondBox.m_min.x && secondBox.m_max.x > m_min.x &&
		m_max.y > secondBox.m_min.y && secondBox.m_max.y > m_min.y);

}

void BoxCollider::SetIsBorderActive(bool isActive)
{
	m_isBorderActive = isActive;
}
