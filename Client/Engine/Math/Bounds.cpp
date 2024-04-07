#include "Math/Bounds.h"

Bounds::Bounds(Vector center, Vector size) :
        center(center),
        size(size),
        extents(size * .5f)
{
    min = center - extents;
    max = center + extents;
}

Bounds Bounds::Intersect(Bounds a, Bounds b)
{
    Vector min = Vector::Max(a.min, b.min);
    Vector max = Vector::Min(a.max, b.max);

    return {(min + max) * .5f, max - min};
}
