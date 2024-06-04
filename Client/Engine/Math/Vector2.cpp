#include "Math/Vector2.h"

#include <algorithm>

Math::Vector2::Vector2() :
    x(),
    y()
{
}

Math::Vector2::Vector2(float x, float y) :
    x(x),
    y(y)
{
}

Math::Vector2& Math::Vector2::operator+=(const Vector2& kVector)
{
    x += kVector.x;
    y += kVector.y;

    return *this;
}

Math::Vector2& Math::Vector2::operator-=(const Vector2& kVector)
{
    x -= kVector.x;
    y -= kVector.y;

    return *this;
}

Math::Vector2& Math::Vector2::operator*=(const Vector2& kVector)
{
    x *= kVector.x;
    y *= kVector.y;

    return *this;
}

Math::Vector2& Math::Vector2::operator/=(const Vector2& kVector)
{
    x /= kVector.x;
    y /= kVector.y;

    return *this;
}

Math::Vector2& Math::Vector2::operator=(const Vector2& kVector)
{
    x = kVector.x;
    y = kVector.y;

    return *this;
}

Math::Vector2 Math::Vector2::operator+(const Vector2& kVector)
{
    return {x + kVector.x, y + kVector.y};
}

Math::Vector2 Math::Vector2::operator-(const Vector2& kVector)
{
    return {x - kVector.x, y - kVector.y};
}

Math::Vector2 Math::Vector2::operator*(const Vector2& kVector)
{
    return {x * kVector.x, y * kVector.y};
}

Math::Vector2 Math::Vector2::operator/(const Vector2& kVector)
{
    return {x / kVector.x, y / kVector.y};
}

Math::Vector2 Math::Vector2::operator+(float val)
{
    return {x + val, y + val};
}

Math::Vector2 Math::Vector2::operator-(float val)
{
    return {x - val, y - val};
}

Math::Vector2 Math::Vector2::operator*(float val)
{
    return {x * val, y * val};
}

Math::Vector2 Math::Vector2::operator/(float val)
{
    return {x / val, y / val};
}

bool Math::Vector2::operator==(const Vector2& kVector) const
{
    if (fabsf(x - kVector.x) <= FLT_EPSILON &&
        fabsf(y - kVector.y) <= FLT_EPSILON)
    {
        return true;
    }

    return false;
}

bool Math::Vector2::operator!=(const Vector2& kVector) const
{
    if (fabsf(x - kVector.x) > FLT_EPSILON ||
        fabsf(y - kVector.y) > FLT_EPSILON)
    {
        return true;
    }

    return false;
}

bool Math::Vector2::operator==(float val) const
{
    if (fabsf(x - val) <= FLT_EPSILON &&
        fabsf(y - val) <= FLT_EPSILON)
    {
        return true;
    }

    return false;
}

bool Math::Vector2::operator!=(float val) const
{
    if (fabsf(x - val) > FLT_EPSILON ||
        fabsf(y - val) > FLT_EPSILON)
    {
        return true;
    }

    return false;
}

Math::Vector2 Math::Vector2::Zero()
{
    return {0.f, 0.f};
}

Math::Vector2 Math::Vector2::One()
{
    return {1.f, 1.f};
}

Math::Vector2 Math::Vector2::Left()
{
    return {-1.f, 0.f};
}

Math::Vector2 Math::Vector2::Up()
{
    return {0.f, 1.f};
}

Math::Vector2 Math::Vector2::Right()
{
    return {1.f, 0.f};
}

Math::Vector2 Math::Vector2::Down()
{
    return {0.f, -1.f};
}

Math::Vector2 Math::Vector2::Lerp(Vector2 a, Vector2 b, float t)
{
    t = std::clamp(t, 0.f, 1.f);
    return a + (b - a) * t;
}

float Math::Vector2::Distance(Vector2 a, Vector2 b)
{
    Math::Vector2 diff = a - b;
    return diff.Magnitude();
}

float Math::Vector2::Dot(Vector2 a, Vector2 b)
{
    const float theta = (a.x * b.x) + (a.y * b.y);
    return theta;
}

Math::Vector2 Math::Vector2::Max(Vector2 a, Vector2 b)
{
    const float max_x = std::max(a.x, b.x);
    const float max_y = std::max(a.y, b.y);

    return {max_x, max_y};
}

Math::Vector2 Math::Vector2::Min(Vector2 a, Vector2 b)
{
    const float min_x = std::min(a.x, b.x);
    const float min_y = std::min(a.y, b.y);

    return {min_x, min_y};
}

Math::Vector2 Math::Vector2::Normalized()
{
    float m = Magnitude();

    if (m > 0)
    {
        return {x / m, y / m};
    }

    return Zero();
}

float Math::Vector2::Magnitude()
{
    const auto temp_x = static_cast<double>(x);
    const auto temp_y = static_cast<double>(y);

    return static_cast<float>(sqrt(pow(temp_x, 2) + pow(temp_y, 2)));
}

void Math::Vector2::Normalize()
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
