#include "GameObject.h"

GameObject::GameObject()
{
	m_angle = 0.0f;
}
float GameObject::GetAngle() const
{
	return m_angle;
}
const std::string& GameObject::GetTag() const
{
	return m_tag;
}
const Vector2D& GameObject::GetSize() const
{
	return m_size;
}
Vector2D GameObject::GetPosition()
{
	return m_position;
}
void GameObject::SetTag(const std::string& tag)
{
	m_tag = tag;
}
void GameObject::SetAngle(float angle)
{
	m_angle = angle;
}
void GameObject::SetSize(float width, float height)
{
	m_size = { width, height };
}
void GameObject::SetSize(const Vector2D& size)
{
	m_size = size;
}
void GameObject::SetPosition(float x, float y)
{
	m_position = { x, y };
}
void GameObject::SetPosition(const Vector2D& position)
{
	m_position = position;
}



