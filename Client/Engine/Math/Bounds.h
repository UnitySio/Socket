#pragma once
#include "Math/Vector.h"

struct Bounds
{
    Bounds() = default;
    Bounds(Math::Vector center, Math::Vector size);
    
    /**
     * \brief 두 바운드의 교차점을 반환합니다.
     * \param a 첫번째 바운드
     * \param b 두번째 바운드
     * \return Bounds
     */
    static Bounds Intersect(Bounds a, Bounds b);
    
    Math::Vector center;
    Math::Vector size;
    Math::Vector extents;
    Math::Vector min;
    Math::Vector max;
};
