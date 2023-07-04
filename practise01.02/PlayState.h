#pragma once

#include "GameState.h"
#include "GameOverState.h"
#include "Sprite.h"
#include "MainCharacter.h"
#include "InGame.h"
#include "Button.h"

class PlayState : public GameState
{
public:
	~PlayState() override {}

	bool OnEnter() override;
	GameState* Update() override;
	bool Render() override;
	void OnExit() override;
private:

	InGame m_inGame;
	Button m_exitButton;
};

