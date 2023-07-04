#pragma once

#include "Sprite.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include "Vector2D.h"
#include "window.h"

class TileMap : public GameObject
{

public:
	enum State
	{	
		A,
		B,
		C,
		D,
		TOTAL_STATES,
		N
	};

	TileMap(Window& window);
	~TileMap();
	void SetState(State state);
	void SetPosition(int x, int y);
	const BoxCollider& GetCollider() const;
	void Array();
	void Update();
	void Render(Window& window);

private:
	float m_angle;
	BoxCollider m_collider;
	State m_state;
	Sprite m_image[N];
	Vector2D m_position;


};

