#include "InGame.h"

InGame::~InGame()
{
}

void InGame::OnEnter()
{
	m_background.Load("assets/images/HollowBG.png");
	m_background.SetImageDimension(1, 1, 1600, 1040);
	m_background.SetSpriteDimension(1920, 1121);

	m_score.Initialize();
	m_score.Load("assets/text/fontbold.ttf", 40);
	m_score.SetColor(56, 255, 0, static_cast<Uint8>(0.8f));
	m_score.SetDimension(100, 40);

	m_timer.CreateTimer(Timer::Type::Counter);
	m_timer.StartTimer();
	m_skeletonTimer.CreateTimer(Timer::Type::Cooldown, 0.0f, 2.0f);
	m_skeletonTimer.StartTimer();


	m_playerMain.CreateCharacter();

	//load monsters
	for (int i = 0; i < m_maxSkeletons; i++)
	{
		m_skeletons.push_back(new Monster());
		m_skeletons[i]->CreateCharacter("assets/images/Skeleton_Idle.png", "assets/images/Skeleton_Walk.png", 4, 4, 600, 600);
		m_skeletons[i]->SetPositionAndCollider(static_cast<float>(rand() % 1800), static_cast<float>(rand() % 1600), 120, 55);
		m_skeletons[i]->RandomBehavior();
	}
	for (int i = 0; i < m_maxGoblins; i++)
	{
		m_goblins.push_back(new Monster());
		m_goblins[i]->CreateCharacter("assets/images/Goblin_Idle.png", "assets/images/Goblin_Run2.png", 4, 8, 600, 1200);
		m_goblins[i]->SetPositionAndCollider(static_cast<float>(rand() % 1800), static_cast<float>(rand() % 1600), 150, 42);
		m_goblins[i]->RandomBehavior();
	}
	m_backgroundMusic.Initialize();
	m_backgroundMusic.Load("assets/music/background.mp3");
	m_backgroundMusic.SetVolume(10);
	m_backgroundMusic.Play(Music::PlayLoop::PLAY_ENDLESS);
}
//=========================================================================================================
int InGame::GetRandomValue(int random)
{
	m_random = rand() % random;
	return m_random;
}
//=========================================================================================================
void InGame::SummonSkeletons()
{
	//depending on time, a certain amount of skeletons are summoned
	for (int i = 0; i < m_stageOne; i++)
	{
		m_skeletons[i]->Update(m_playerMain.GetPosition());
	}
	if (m_timer.GetCurrent() >= 10.0f)
	{
		for (int i = m_stageOne; i < m_stageTwo; i++)
		{
			m_skeletons[i]->Update(m_playerMain.GetPosition());
		}
	}
	if (m_timer.GetCurrent() >= 20.0f)
	{
		for (int i = m_stageTwo; i < m_stageThree; i++)
		{
			m_skeletons[i]->Update(m_playerMain.GetPosition());
		}
	}
}
//=========================================================================================================
void InGame::SummonGoblins()
{
	//at 30 sec goblins are summoned
	if (m_timer.GetCurrent() >= 30.0f)
	{
		for (int i = 0; i < m_maxGoblins; i++)
		{
			m_goblins[i]->Update(m_playerMain.GetPosition());
		}
	}
}
//=========================================================================================================
void InGame::DealDamageToPlayer(BoxCollider collider)
{
	//if monsters collide with the knight they deal damage to it
	for (int i = 0; i < m_maxSkeletons; i++)
	{
		if (m_skeletons[i]->GetCollider().IsColliding(collider) == true)
		{
			m_playerMain.DealDamageToPlayer(20);
		}
	}

	for (int i = 0; i < m_maxGoblins; i++)
	{
		if (m_goblins[i]->GetCollider().IsColliding(collider) == true)
		{
			m_playerMain.DealDamageToPlayer(10);
		}
	}
}
//=========================================================================================================
bool InGame::PlayerIsDead()
{
	//if players health drops below 0 the game is over
	if (m_playerMain.GetHealth() <= 0)
	{
		m_isDead = true;
	}
	return m_isDead;
}
//=========================================================================================================
bool InGame::GetIsDead()
{
	return m_isDead;
}
//=========================================================================================================
void InGame::SetIsDead(bool isDead)
{
	m_isDead = isDead;
}
//=========================================================================================================
void InGame::MiniMenu()
{
	SDL_Point mousePos = Input::Instance()->GetMousePosition();
	bool isMouseClicked = Input::Instance()->IsMouseClicked();
}
//=========================================================================================================
void InGame::CreateNewPlayer()
{
	m_playerOther.CreateCharacter();
}
//=========================================================================================================
void InGame::Reset()
{
	m_playerMain.SetHealth(100);
	m_playerMain.SetPositionAndCollider(500, 500, 240, 80);
	m_timer.SetCurrent(0);
}
//=========================================================================================================
void InGame::Update()
{
	m_timer.Update();
	m_playerMain.UpdateMain();

	m_score.SetText("Timer: " + std::to_string(static_cast<int>(m_timer.GetCurrent())));

	SummonSkeletons();
	SummonGoblins();
	DealDamageToPlayer(m_playerMain.GetCollider());

	if(PlayerIsDead())
			Reset();
}
//=========================================================================================================
void InGame::Render()
{
	m_background.Render(0, 0, 0);
	m_playerMain.Render();
	m_score.Render(600, 10);

	//depending on time, a certain amount of skeletons are summoned
	for (int i = 0; i < m_stageOne; i++)
	{
		m_skeletons[i]->Render();
	}
	if (m_timer.GetCurrent() >= 10.0f)
	{
		for (int i = m_stageOne; i < m_stageTwo; i++)
		{
			m_skeletons[i]->Render();
		}
	}
	if (m_timer.GetCurrent() >= 20.0f)
	{
		for (int i = m_stageTwo; i < m_stageThree; i++)
		{
			m_skeletons[i]->Render();
		}
	}
	if (m_timer.GetCurrent() >= 30.0f)
	{
		for (int i = 0; i < m_maxGoblins; i++)
		{
			m_goblins[i]->Render();
		}
	}
}
//=========================================================================================================
void InGame::OnExit()
{
	m_background.Unload();
	m_backgroundMusic.Unload();
	m_goblins.clear();
	m_skeletons.clear();
}