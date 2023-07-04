#include "MainCharacter.h"

MainCharacter::~MainCharacter()
{
	m_idleImage.Unload();
	m_runImage.Unload();
	m_deathImage.Unload();
	m_slideImage.Unload();
}
//=========================================================================================================
void MainCharacter::CreateCharacter()
{
	auto createImage = [](Sprite& image, std::string location, int column, int width)
	{
		image.Load(location);
		image.SetImageDimension(column, 1, width, 40);
		image.SetSpriteDimension(240, 80);
		image.IsAnimated(true);
		image.IsAnimationLooping(true);
		image.SetAnimationVelocity(0.05f);
	};
	createImage(m_idleImage, "assets/images/Knight_Idle2.png", 10, 1200);
	createImage(m_runImage, "assets/images/Knight_Run2.png", 10, 1200);
	createImage(m_deathImage, "assets/images/KnightDeath2.png", 10, 1200);
	createImage(m_slideImage, "assets/images/Knight_Slide2.png", 4, 480);

	SetPositionAndCollider(500, 500, 240, 80);
	m_healthbar.CreateHealthBar(m_health);
	m_healthbar.SetHealthBarPosition(760, 10);
	m_slideTimer.CreateTimer(Timer::Type::Cooldown, 0.0f, 0.5f);
	m_damageTimer.CreateTimer(Timer::Type::Cooldown, 0.0f, 1.0f);
}
//=========================================================================================================
void MainCharacter::SetPositionAndCollider(float x, float y, int width, int height)
{
	SetPosition(x, y);
	m_collider.SetPosition(x + m_idleImage.GetSpriteDimension().x / 3.0f, y);
	m_collider.SetDimension(50, height);
}
//=========================================================================================================
BoxCollider MainCharacter::GetCollider()
{
	return m_collider;
}
//=========================================================================================================
void MainCharacter::SetState(State state)
{
	m_state = state;
}
//=========================================================================================================
void MainCharacter::SetFacing(Facing direction)
{
	m_facing = direction;
}
//=========================================================================================================
void MainCharacter::SetColliderPosition()
{
	float colliderPosition = static_cast<float>((m_idleImage.GetSpriteDimension().x / 3.0f) + m_position.x);
	m_collider.SetPosition(colliderPosition, m_position.y);
}
//=========================================================================================================
void MainCharacter::SetHealth(int health)
{
	m_health = health;
}
void MainCharacter::SetIsDamaged(bool damaged)
{
	m_isDamaged = damaged;
}
void MainCharacter::ReduceHealth()
{
	//deals damage to the player, there's a 1 second time between each action, 
	//so the player cannot be damaged multiple times at the same time
	if (m_isDamaged == true && m_damageTimer.GetCurrent() == m_damageTimer.GetMax())
	{

		m_damageTimer.StartTimer();
		m_health = m_health - m_damage;
		SetIsDamaged(false);
	}
}
void MainCharacter::DealDamageToPlayer(int damage)
{
	m_damage = damage;
	SetIsDamaged(true);
}
void MainCharacter::Slide()
{
	//player gets higher speed for 0.5 sec
	if (m_state == State::Slide && m_slideTimer.GetCurrent() > m_slideTimer.GetMin())
	{
		if (m_facing == Facing::Left)
		{
			m_position.x -= m_velocity.x;
		}
		if (m_facing == Facing::Right)
		{
			m_position.x += m_velocity.x;
		}
	}
	if (m_state != State::Slide && m_slideTimer.GetCurrent() != m_slideTimer.GetMax())
	{
		m_slideTimer.SetCurrent(m_slideTimer.GetMax());
	}
}
//=========================================================================================================
MainCharacter::State MainCharacter::GetState()
{
	return m_state;
}
//=========================================================================================================
MainCharacter::Facing MainCharacter::GetFacing()
{
	return m_facing;
}
//=========================================================================================================
int MainCharacter::GetHealth()
{
	return m_health;
}
bool MainCharacter::IsReady()
{
	return m_isReady;
}
//=========================================================================================================
void MainCharacter::UpdateMain()
{
	bool isMouseClicked = Input::Instance()->IsMouseClicked();
	auto getKeyDown = Input::Instance()->IsKeyPressed();
	SDL_Point mousePos = Input::Instance()->GetMousePosition();

	if (Input::Instance()->IsKeyPressed(HM_KEY_A))
	{
		SetFacing(Facing::Left);
		SetState(State::Run);
		m_position.x -= m_velocity.x;
		SetColliderPosition();
	}
	if (Input::Instance()->IsKeyPressed(HM_KEY_D))
	{
		SetFacing(Facing::Right);
		SetState(State::Run);
		m_position.x += m_velocity.x;
		SetColliderPosition();
	}
	if (Input::Instance()->IsKeyPressed(HM_KEY_S))
	{
		SetState(State::Run);
		m_position.y += m_velocity.y;
		SetColliderPosition();
	}
	if (Input::Instance()->IsKeyPressed(HM_KEY_W))
	{
		SetState(State::Run);
		m_position.y -= m_velocity.y;
		SetColliderPosition();
	}
	if (Input::Instance()->IsKeyPressed(HM_KEY_E))
	{
		m_health--;
	}
	if (Input::Instance()->IsKeyPressed(HM_KEY_Q))
	{
		m_health++;
	}
	if (Input::Instance()->IsKeyPressed(HM_KEY_TAB))
	{
		SetState(State::Slide);
		m_slideTimer.StartTimer();
		m_velocity.x = 7;
	}
	if (m_health <= 0)
	{
		SetState(State::Death);
	}
	if (Input::Instance()->IsKeyPressed() == false && m_state != State::Death && m_state != State::Slide)
	{
		SetState(State::Idle);
		m_velocity = { 3,3 };
	}
	m_collider.Update();
	m_idleImage.Update();
	m_runImage.Update();
	m_deathImage.Update();
	m_slideImage.Update();
	m_healthbar.Update(m_health);
	m_slideTimer.Update();
	m_damageTimer.Update();
	Slide();
	ReduceHealth();
}

//=========================================================================================================
void MainCharacter::Render()
{
	int posX = static_cast<int>(m_position.x);
	int posY = static_cast<int>(m_position.y);

	//IDLE STATE
	if (m_state == State::Idle && m_facing == Facing::Right)
	{
		m_idleImage.Render(posX, posY, m_angle);
	}
	if (m_state == State::Idle && m_facing == Facing::Left)
	{
		m_idleImage.Render(posX, posY, m_angle, Sprite::Flip::HORZ_FLIP);
	}
	//RUN STATE
	if (m_state == State::Run && m_facing == Facing::Right)
	{
		m_runImage.Render(posX, posY, m_angle);
	}
	if (m_state == State::Run && m_facing == Facing::Left)
	{
		m_runImage.Render(posX, posY, m_angle, Sprite::Flip::HORZ_FLIP);
	}
	//DEATH STATE
	if (m_state == State::Death && m_facing == Facing::Right)
	{
		m_deathImage.Render(posX, posY, m_angle);
		m_deathImage.IsAnimationLooping(false);

	}
	if (m_state == State::Death && m_facing == Facing::Left)
	{
		m_deathImage.Render(posX, posY, m_angle, Sprite::Flip::HORZ_FLIP);
		m_deathImage.IsAnimationLooping(false);
	}
	//SLIDE STATE
	if (m_state == State::Slide && m_facing == Facing::Right)
	{
		m_slideImage.Render(posX, posY, m_angle);
	}
	if (m_state == State::Slide && m_facing == Facing::Left)
	{
		m_slideImage.Render(posX, posY, m_angle, Sprite::Flip::HORZ_FLIP);
	}
	m_healthbar.Render();
}
