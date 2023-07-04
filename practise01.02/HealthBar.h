#pragma once
#include "GameObject.h"
#include "Sprite.h"
class HealthBar : public GameObject
{
public:
	~HealthBar();
	void CreateHealthBar(int health);
	void SetHealthBarPosition(float x, float y);
	void SetCurrentHealth(int health);
	void ConnectHealthToBar(int& health);
	void Update(int health);
	void Render();
private:
	Sprite m_back;
	Sprite m_bar;
	Sprite m_border;

	int m_currentHealth = 0;
};

