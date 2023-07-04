#pragma once
#include "Button.h"
#include <ctime>
#include "MainCharacter.h"
#include "Monster.h"
#include "SDLText.h"
#include <string>
#include "Timer.h"
#include <vector>
#include "Music.h"



class InGame
{

public:
	~InGame();
	void OnEnter();

	int GetRandomValue(int random);

	void SummonSkeletons();
	void SummonGoblins();
	void DealDamageToPlayer(BoxCollider collider);
	bool PlayerIsDead();
	bool GetIsDead();
	void SetIsDead(bool isdead);

	void MiniMenu();
	void CreateNewPlayer();


	void Reset();

	void Update();
	void Render();
	void OnExit();

private:
	Sprite m_background;
	MainCharacter m_playerMain;
	MainCharacter m_playerOther;
	Monster m_skeleton;
	Monster m_goblin;

	std::vector <Monster*> m_skeletons;
	std::vector <Monster*> m_goblins;

	SDLText m_score;
	Timer m_timer;
	Timer m_skeletonTimer;
	bool m_isStarted = false;

	Music m_backgroundMusic;

	int m_stageOne = 5;
	int m_stageTwo = 5;
	int m_stageThree = 5;

	bool m_isDead = false;

	int m_maxSkeletons = 5;
	int m_maxGoblins = 5;

	int m_random = 0;
	int m_pick = 0;
	int m_input = 0;


};

