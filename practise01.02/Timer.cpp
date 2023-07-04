#include "Timer.h"

void Timer::CreateTimer(Type type, float min, float max)
{
    m_type = type;
    m_min = min;
    m_max = max;
    if (type == Type::Counter) { m_current = m_min; };
    if (type == Type::Cooldown) { m_current = m_max; };
}

void Timer::SetTimer(float time)
{
    m_current = time;
}

float Timer::GetMin()
{
    return m_min;
}

float Timer::GetCurrent()
{
    return m_current;
}

float Timer::GetMax()
{
    return m_max;
}

void Timer::SetMin(float min)
{
    m_min = min;
}

void Timer::SetCurrent(float current)
{
    m_current = current;
}

void Timer::SetMax(float max)
{
    m_max = max;
}

void Timer::StartTimer()
{
    m_state = State::Run;
}

void Timer::StopTimer()
{
    m_state = State::Idle;
}

void Timer::Update()
{
    if (m_type == Type::Counter && m_state == State::Run)
    {
        m_current += m_velocity;
    }
    if (m_type == Type::Cooldown && m_state == State::Run)
    {
        m_current -= m_velocity;
        if (m_current <= m_min)
        {
            SetCurrent(m_max);
            m_state = State::Idle;
        }
    }
}
