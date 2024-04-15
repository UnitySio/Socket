#include "Math/Vector.h"

#include <algorithm>

Math::Vector::Vector() :
    x(),
    y()
{
}

Math::Vector::Vector(float x, float y) :
    x(x),
    y(y)
{
}

Math::Vector& Math::Vector::operator+=(const Vector& kVector)
{
    x += kVector.x;
    y += kVector.y;

    return *this;
}

Math::Vector& Math::Vector::operator-=(const Vector& kVector)
{
    x -= kVector.x;
    y -= kVector.y;

    return *this;
}

Math::Vector& Math::Vector::operator*=(const Vector& kVector)
{
    x *= kVector.x;
    y *= kVector.y;

    return *this;
}

Math::Vector& Math::Vector::operator/=(const Vector& kVector)
{
    x /= kVector.x;
    y /= kVector.y;

    return *this;
}

Math::Vector& Math::Vector::operator=(const Vector& kVector)
{
    x = kVector.x;
    y = kVector.y;

    return *this;
}

Math::Vector Math::Vector::operator+(const Vector& kVector)
{
    return {x + kVector.x, y + kVector.y};
}

Math::Vector Math::Vector::operator-(const Vector& kVector)
{
    return {x - kVector.x, y - kVector.y};
}

Math::Vector Math::Vector::operator*(const Vector& kVector)
{
    return {x * kVector.x, y * kVector.y};
}

Math::Vector Math::Vector::operator/(const Vector& kVector)
{
    return {x / kVector.x, y / kVector.y};
}

Math::Vector Math::Vector::operator+(float val)
{
    return {x + val, y + val};
}

Math::Vector Math::Vector::operator-(float val)
{
    return {x - val, y - val};
}

Math::Vector Math::Vector::operator*(float val)
{
    return {x * val, y * val};
}

Math::Vector Math::Vector::operator/(float val)
{
    return {x / val, y / val};
}

bool Math::Vector::operator==(const Vector& kVector) const
{
    if (fabsf(x - kVector.x) <= FLT_EPSILON &&
        fabsf(y - kVector.y) <= FLT_EPSILON)
    {
        return true;
    }

    return false;
}

bool Math::Vector::operator!=(const Vector& kVector) const
{
    if (fabsf(x - kVector.x) > FLT_EPSILON ||
        fabsf(y - kVector.y) > FLT_EPSILON)
    {
        return true;
    }

    return false;
}

bool Math::Vector::operator==(float val) const
{
    if (fabsf(x - val) <= FLT_EPSILON &&
        fabsf(y - val) <= FLT_EPSILON)
    {
        return true;
    }

    return false;
}

bool Math::Vector::operator!=(float val) const
{
    if (fabsf(x - val) > FLT_EPSILON ||
        fabsf(y - val) > FLT_EPSILON)
    {
        return true;
    }

    return false;
}

Math::Vector Math::Vector::Zero()
{
    return {0.f, 0.f};
}

Math::Vector Math::Vector::One()
{
    return {1.f, 1.f};
}

Math::Vector Math::Vector::Left()
{
    return {-1.f, 0.f};
}

Math::Vector Math::Vector::Up()
{
    return {0.f, 1.f};
}

Math::Vector Math::Vector::Right()
{
    return {1.f, 0.f};
}

Math::Vector Math::Vector::Down()
{
    return {0.f, -1.f};
}

Math::Vector Math::Vector::Lerp(Vector a, Vector b, float t)
{
    t = std::clamp(t, 0.f, 1.f);
    return a + (b - a) * t;
}

float Math::Vector::Distance(Vector a, Vector b)
{
    Math::Vector diff = a - b;
    return diff.Magnitude();
}

float Math::Vector::Dot(Vector a, Vector b)
{
    const float theta = (a.x * b.x) + (a.y * b.y);
    return theta;
}

Math::Vector Math::Vector::Max(Vector a, Vector b)
{
    const float max_x = std::max(a.x, b.x);
    const float max_y = std::max(a.y, b.y);

    return {max_x, max_y};
}

Math::Vector Math::Vector::Min(Vector a, Vector b)
{
    const float min_x = std::min(a.x, b.x);
    const float min_y = std::min(a.y, b.y);

    return {min_x, min_y};
}

Math::Vector Math::Vector::Normalized()
{
    float m = Magnitude();

    if (m > 0)
    {
        return {x / m, y / m};
    }

    return Zero();
}

float Math::Vector::Magnitude()
{
    const auto temp_x = static_cast<double>(x);
    const auto temp_y = static_cast<double>(y);

    return static_cast<float>(sqrt(pow(temp_x, 2) + pow(temp_y, 2)));
}

void Math::Vector::Normalize()
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
