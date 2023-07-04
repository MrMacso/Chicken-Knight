#pragma once
#include "BoxCollider.h"
#include "Input.h"
#include "HealthBar.h"
#include "GameObject.h"
#include "SDLText.h"
#include "Sprite.h"
#include "Vector2D.h"
#include "Timer.h"

class MainCharacter : public GameObject
{
public:
    enum class State
    {
        Idle,
        Run,
        Death,
        Slide
    };
    enum class Facing
    {
        Left,
        Right
    };

    ~MainCharacter();

    void CreateCharacter();

    void SetPositionAndCollider(float x, float y, int width, int height);
    void SetState(State state);
    void SetFacing(Facing direction);
    void SetHealth(int health);
    void SetIsDamaged(bool damaged);

    void DealDamageToPlayer(int damage);
    void SetColliderPosition();
    void ReduceHealth();
    void Slide();

    BoxCollider GetCollider();
    MainCharacter::State GetState();
    MainCharacter::Facing GetFacing();
    int GetHealth();

    bool IsReady();

    void UpdateMain();
    void Render();

private:

    Sprite m_idleImage;
    Sprite m_runImage;
    Sprite m_deathImage;
    Sprite m_slideImage;

    Timer m_slideTimer;
    Timer m_damageTimer;

    BoxCollider m_collider;
    HealthBar m_healthbar;

    State m_state = State::Idle;
    Facing m_facing = Facing::Right;

    int m_health = 100;
    int m_damage = 1;
    bool m_isDamaged = false;

    bool m_isReady;
};

