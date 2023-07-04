#pragma once
#include "GameState.h"
#include "Sprite.h"
#include "Button.h"
#include "PlayState.h"
#include "HowToPlayState.h"
#include "SDLText.h"

class MenuState : public GameState
{
public:
	~MenuState() override {};

	bool OnEnter() override;
	GameState* Update() override;
	bool Render() override;
	void OnExit() override;
private:
	Sprite m_background;
	Button m_startButton;
	Button m_howToButton;
	Button m_exitButton;
	SDLText m_text;

};