#pragma once
#include "BoxCollider.h"
#include "GameObject.h"
#include "Sprite.h"
#include "SDLText.h"
#include "Vector2D.h"
#include "Timer.h"

class Monster : public GameObject
{
public:
    enum class State
    {
        Idle,
        Run,
        Up,
        Down,
        Attack,
        Slide
    };
    enum class Facing
    {
        Left,
        Right
    };
    enum class Behavior
    {
        Basic,
        Follow,
        Crazy,
    };
    ~Monster();

    void CreateCharacter(std::string fileLocation, std::string runLocation,
        int idleRow, int runRow, int idleWidth, int runWidth);
    void SetPositionAndCollider(float x, float y, int width, int height);
    void SetState(State state);
    void SetFacing(Facing direction);

    void MonsterBehavior(Vector2D vector);

    void RandomBehavior();
    BoxCollider GetCollider();
    Monster::State GetState();
    Monster::Facing GetFacing();
    Vector2D GetDirection();

    void Update(Vector2D vector);
    void Render();

private:
    Sprite m_idleImage;
    Sprite m_runImage;

    Vector2D m_direction;
    Vector2D m_distance;

    BoxCollider m_collider;

    int m_CollPos = 55;

    State m_state = State::Run;
    Facing m_facing = Facing::Right;
    Behavior m_behavior = Behavior::Basic;
    Timer m_timer;
    Timer m_respawn;
};

