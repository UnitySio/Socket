#include "Vector.h"

#include <algorithm>

Vector::Vector() :
    x(),
    y()
{
}

Vector::Vector(float x, float y) :
    x(x),
    y(y)
{
}

Vector& Vector::operator+=(const Vector& kVector)
{
    x += kVector.x;
    y += kVector.y;

    return *this;
}

Vector& Vector::operator-=(const Vector& kVector)
{
    x -= kVector.x;
    y -= kVector.y;

    return *this;
}

Vector& Vector::operator*=(const Vector& kVector)
{
    x *= kVector.x;
    y *= kVector.y;

    return *this;
}

Vector& Vector::operator/=(const Vector& kVector)
{
    x /= kVector.x;
    y /= kVector.y;

    return *this;
}

Vector& Vector::operator=(const Vector& kVector)
{
    x = kVector.x;
    y = kVector.y;

    return *this;
}

Vector Vector::operator+(const Vector& kVector)
{
    return {x + kVector.x, y + kVector.y};
}

Vector Vector::operator-(const Vector& kVector)
{
    return {x - kVector.x, y - kVector.y};
}

Vector Vector::operator*(const Vector& kVector)
{
    return {x * kVector.x, y * kVector.y};
}

Vector Vector::operator/(const Vector& kVector)
{
    return {x / kVector.x, y / kVector.y};
}

Vector Vector::operator+(float val)
{
    return {x + val, y + val};
}

Vector Vector::operator-(float val)
{
    return {x - val, y - val};
}

Vector Vector::operator*(float val)
{
    return {x * val, y * val};
}

Vector Vector::operator/(float val)
{
    return {x / val, y / val};
}

bool Vector::operator==(const Vector& kVector) const
{
    if (fabsf(x - kVector.x) <= FLT_EPSILON &&
        fabsf(y - kVector.y) <= FLT_EPSILON)
    {
        return true;
    }

    return false;
}

bool Vector::operator!=(const Vector& kVector) const
{
    if (fabsf(x - kVector.x) > FLT_EPSILON ||
        fabsf(y - kVector.y) > FLT_EPSILON)
    {
        return true;
    }

    return false;
}

bool Vector::operator==(float val) const
{
    if (fabsf(x - val) <= FLT_EPSILON &&
        fabsf(y - val) <= FLT_EPSILON)
    {
        return true;
    }

    return false;
}

bool Vector::operator!=(float val) const
{
    if (fabsf(x - val) > FLT_EPSILON ||
        fabsf(y - val) > FLT_EPSILON)
    {
        return true;
    }

    return false;
}

Vector Vector::Zero()
{
    return {0.f, 0.f};
}

Vector Vector::One()
{
    return {1.f, 1.f};
}

Vector Vector::Left()
{
    return {-1.f, 0.f};
}

Vector Vector::Up()
{
    return {0.f, -1.f};
}

Vector Vector::Right()
{
    return {1.f, 0.f};
}

Vector Vector::Down()
{
    return {0.f, 1.f};
}

Vector Vector::Lerp(Vector a, Vector b, float t)
{
    t = std::clamp(t, 0.f, 1.f);
    return a + (b - a) * t;
}

float Vector::Distance(Vector a, Vector b)
{
    Vector diff = a - b;
    return diff.Magnitude();
}

float Vector::Dot(Vector a, Vector b)
{
    const float theta = (a.x * b.x) + (a.y * b.y);
    return theta;
}

Vector Vector::Max(Vector a, Vector b)
{
    const float max_x = std::max(a.x, b.x);
    const float max_y = std::max(a.y, b.y);

    return {max_x, max_y};
}

Vector Vector::Min(Vector a, Vector b)
{
    const float min_x = std::min(a.x, b.x);
    const float min_y = std::min(a.y, b.y);

    return {min_x, min_y};
}

Vector Vector::Normalized()
{
    float m = Magnitude();

    if (m > 0)
    {
        return {x / m, y / m};
    }

    return Zero();
}

float Vector::Magnitude()
{
    const auto temp_x = static_cast<double>(x);
    const auto temp_y = static_cast<double>(y);

    return static_cast<float>(sqrt(pow(temp_x, 2) + pow(temp_y, 2)));
}

void Vector::Normalize()
{
    float m = Magnitude();

    if (m > 0)
    {
        x /= m;
        y /= m;
    }
    else
    {
        x = 0.f;
        y = 0.f;
    }
}
