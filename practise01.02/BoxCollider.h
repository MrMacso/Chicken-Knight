#pragma once

#include "Vector2D.h"
#include "Sprite.h"

class BoxCollider
{

public:

	void SetPosition(float x, float y);
	void SetDimension(int width, int height);
	Vector2D GetPosition();
	Vector2D GetDimension();
	void Update();
	bool IsColliding(const BoxCollider& secondBox) const;
	void SetIsBorderActive(bool isActive);


private:
	Vector2D m_min;
	Vector2D m_max;
	Vector2D m_position;
	Vector2D m_dimension;
	Sprite m_border;
	bool m_isBorderActive = true;

};

