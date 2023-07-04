#pragma once
#include <iostream>
#include <string>
#include "GameState.h"
#include "Screen.h"
#include "Sprite.h"
#include "Input.h"
#include "Button.h"
class Game
{
public:
	Game(GameState* initialState);
	//======================================================================
	bool Initialize()
	{
		Screen::Instance()->Initialize("Test", 1920, 1040);
		return true;
	}
	bool Run();
	void Shutdown();

private:
	std::unique_ptr<GameState>m_gamestate;
};

