#pragma once
class Timer
{
public:
	enum class Type
	{
		Counter,
		Cooldown
	};
	enum class State
	{
		Idle,
		Run
	};
	void CreateTimer(Type type, float min = 0.0f, float max = 0.0f);
	void SetTimer(float time);
	float GetMin();
	float GetCurrent();
	float GetMax();
	void SetMin(float min);
	void SetCurrent(float current);
	void SetMax(float max);
	void StartTimer();
	void StopTimer();
	void Update();


private:
	float m_min = 0.0f;
	float m_current = 0.0f;
	float m_max = 0.0f;
	float m_velocity = 0.013f;
	Type m_type = Type::Counter;
	State m_state = State::Idle;
};

