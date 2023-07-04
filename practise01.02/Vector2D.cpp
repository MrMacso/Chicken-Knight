#include "Vector2D.h"


Vector2D::Vector2D(float x, float y)
{
    this->x = x;
    this->y = y;
}
//======================================================================
Vector2D Vector2D::GetVector2D()
{
    return { x,y };
}
//======================================================================
void Vector2D::SetVector2D(float x, float y)
{
    this->x = x;
    this->y = y;
}
//======================================================================
Vector2D Vector2D::Add(const Vector2D& second)
{
    Vector2D result;

    result.x = x + second.x;
    result.y = y + second.y;

    return  result;
}
//======================================================================
Vector2D Vector2D::Subtract(const Vector2D& second)
{
    Vector2D result;

    result.x = x - second.x;
    result.y = y - second.y;

    return result;
}
//======================================================================
Vector2D Vector2D::Scale(float scaler)
{
    Vector2D result;

    result.x = x * scaler;
    result.y = y * scaler;

    return result;
}
//======================================================================
int Vector2D::Distance(const Vector2D& second)
{
    Vector2D temp = Subtract(second);

    return static_cast<float>(temp.Magnitude());
}
//======================================================================
double Vector2D::Magnitude()
{
    double x = static_cast<double>(this->x);
    double y = static_cast<double>(this->y);

    return sqrt((x * x) + (y * y));
}
void Vector2D::Normalize()
{
    Vector2D normalized;
    if (x > y)
    {
        normalized.x = (this->x / x);
        normalized.y = (this->y / x);
    }
    else
    {
        normalized.x = (this->x / y);
        normalized.y = (this->y / y);
    }
}
//======================================================================
Vector2D Vector2D::Negation()
{
    Vector2D result;

    result.x = -x;
    result.y = -y;

    return result;
}
