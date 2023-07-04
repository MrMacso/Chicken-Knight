#include "Monster.h"

Monster::~Monster()
{
	m_idleImage.Unload();
	m_runImage.Unload();
}
//=========================================================================================================
void Monster::CreateCharacter(std::string idleLocation, std::string runLocation,
	int idleRow, int runRow, int idleWidth, int runWidth)
{
	auto createImage = [](Sprite& image, std::string location, int column, int width)
	{
		image.Load(location);
		image.SetImageDimension(column, 1, width, 55);
		image.SetSpriteDimension(150, 55);
		image.IsAnimated(true);
		image.IsAnimationLooping(true);
		image.SetAnimationVelocity(0.03f);
	};
	createImage(m_idleImage, idleLocation, idleRow, idleWidth);
	createImage(m_runImage, runLocation, runRow, runWidth);

	SetPositionAndCollider(700, 500, 120, 55);
	m_collider.SetIsBorderActive(false);
	m_timer.CreateTimer(Timer::Type::Counter);
	m_timer.StartTimer();
	m_respawn.CreateTimer(Timer::Type::Cooldown, 0.0f, 10.0f);
	m_respawn.StartTimer();
	//m_collider.SetIsBorderActive(false);
}
//=========================================================================================================

//=========================================================================================================
void Monster::SetPositionAndCollider(float x, float y, int width, int height)
{
	SetPosition(x, y);
	m_collider.SetPosition(x + m_CollPos, y);
	m_collider.SetDimension(width / 4, height);
}
//=========================================================================================================
void Monster::SetState(State state)
{
	m_state = state;
}
//=========================================================================================================
void Monster::SetFacing(Facing direction)
{
	m_facing = direction;
}
//=========================================================================================================
void Monster::MonsterBehavior(Vector2D vector)
{
	//different type of behaviors
	if (m_behavior == Behavior::Basic)
	{
		if (m_position.x >= 1800) SetFacing(Facing::Left);
		if (m_position.x <= 50) SetFacing(Facing::Right);
		if (m_facing == Facing::Right)
		{
			m_position.x++;
			m_collider.SetPosition(m_position.x + m_CollPos, m_position.y);
		}
		if (m_facing == Facing::Left)
		{
			m_position.x--;
			m_collider.SetPosition(m_position.x + m_CollPos, m_position.y);
		}
	}
	if (m_behavior == Behavior::Follow)
	{
		m_velocity = { 1.0f,1.0f };
		Vector2D direction = vector.Subtract(m_position);
		if (m_position.x < vector.x)
		{
			direction.x = vector.x - m_position.x;
			m_facing = Facing::Right;
		}
		else if (m_position.x > vector.x)
		{
			direction.x = m_position.x - vector.x;
			m_facing = Facing::Left;
		}
		else if (m_position.y < vector.y)
		{
			direction.y = vector.y - m_position.y;
		}
		else if (m_position.y > vector.y)
		{
			direction.y = m_position.y - vector.y;
		}
		else {}

		if (m_position.x < vector.x)
		{
			m_position.x += m_velocity.x;
		}
		else {
			m_position.x -= m_velocity.x;
		}
		if (m_position.y < vector.y)
		{
			m_position.y += m_velocity.y;
		}
		else
		{
			m_position.y -= m_velocity.y;
		}
		if (m_respawn.GetCurrent() >= m_respawn.GetMax())
		{
			int randomX = rand() % 1500;
			int randomY = rand() % 800;
			SetPosition(static_cast<float>(randomX), static_cast<float>(randomY));
			m_respawn.StartTimer();
		}
		m_collider.SetPosition(m_position.x + m_CollPos, m_position.y);
	}
	if (m_behavior == Behavior::Crazy)
	{
		m_velocity = { 6,6 };
		if (m_position.y >= 1500) SetFacing(Facing::Left);
		if (m_position.y <= 50) SetFacing(Facing::Right);
		if (m_facing == Facing::Right)
		{
			m_position.y += m_velocity.y;
			m_collider.SetPosition(m_position.x + m_CollPos, m_position.y);
		}
		if (m_facing == Facing::Left)
		{
			m_position.y -= m_velocity.y;
			m_collider.SetPosition(m_position.x + m_CollPos, m_position.y);
		}
	}
}
//=========================================================================================================
void Monster::RandomBehavior()
{
	//picks a random behavior
	int random = rand() % 4;
	if (random == 1)
	{
		m_behavior = Monster::Behavior::Follow;
	}
	if (random == 2)
	{
		m_behavior = Monster::Behavior::Basic;
	}
	if (random == 3)
	{
		m_behavior = Monster::Behavior::Crazy;
	}
}
//=========================================================================================================
BoxCollider Monster::GetCollider()
{
	return m_collider;
}
//=========================================================================================================
Monster::State Monster::GetState()
{
	return m_state;
}
//=========================================================================================================
Monster::Facing Monster::GetFacing()
{
	return m_facing;
}
//=========================================================================================================
Vector2D Monster::GetDirection()
{
	return m_direction;
}
//=========================================================================================================
void Monster::Update(Vector2D vector)
{
	MonsterBehavior(vector);
	if (m_state == State::Idle)
	{
		m_idleImage.Update();
	}
	if (m_state == State::Run)
	{
		m_runImage.Update();
	}
	m_collider.Update();
	m_timer.Update();
	m_respawn.Update();
}
//=========================================================================================================
void Monster::Render()
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
}