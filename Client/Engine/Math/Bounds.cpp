#include "Math/Bounds.h"

Bounds::Bounds(Math::Vector center, Math::Vector size) :
        center(center),
        size(size),
        extents(size * .5f)
{
    min = center - extents;
    max = center + extents;
}

Bounds Bounds::Intersect(Bounds a, Bounds b)
{
    Math::Vector min = Math::Vector::Max(a.min, b.min);
    Math::Vector max = Math::Vector::Min(a.max, b.max);

    return {(min + max) * .5f, max - min};
}
