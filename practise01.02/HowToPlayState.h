#pragma once

#include "GameState.h"
#include "Sprite.h"
#include "Button.h"
#include "MenuState.h"
#include "SDLText.h"

class HowToPlayState : public GameState
{
public:
	~HowToPlayState() override {};

	bool OnEnter() override;
	GameState* Update() override;
	bool Render() override;
	void OnExit() override;
private:
	Sprite m_howToBackground;
	Button m_exitButton;
	SDLText m_text;
	SDLText m_textTwo;
};

