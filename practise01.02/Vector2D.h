#pragma once
#include "math.h"
class Vector2D
{

public:
	Vector2D(float x = 0, float y = 0);

	Vector2D GetVector2D();
	void SetVector2D(float x, float y);

	Vector2D Add(const Vector2D& second);
	Vector2D Subtract(const Vector2D& second);
	Vector2D Scale(float scaler);
	int Distance(const Vector2D& vector);
	double Magnitude();
	void Normalize();
	Vector2D Negation();

public:

	float x;
	float y;
};

