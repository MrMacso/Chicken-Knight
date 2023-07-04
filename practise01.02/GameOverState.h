#pragma once
#include "GameState.h"
#include "Sprite.h"
#include "MenuState.h"
#include "Button.h"
#include "SDLText.h"

class GameOverState : public GameState
{
public:
	~GameOverState() override {}

	bool OnEnter() override;
	GameState* Update() override;
	bool Render() override;
	void OnExit() override;
private:

	Sprite m_exitBackground;
	Button m_restartButton;
	Button m_exitButton;
	SDLText m_gameOvertext;

};


