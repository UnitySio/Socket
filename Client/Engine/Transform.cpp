#include "Transform.h"

Transform::Transform(Vector position, Vector scale, float angle) :
    position(position),
    scale(scale),
    angle(angle)
{
}

bool Transform::operator==(const Transform& kTransform) const
{
    if (position == kTransform.position &&
        scale == kTransform.scale &&
        angle == kTransform.angle)
        return true;
    
    return false;
}

bool Transform::operator!=(const Transform& kTransform) const
{
    if (position != kTransform.position ||
        scale != kTransform.scale ||
        angle != kTransform.angle)
        return true;
    
    return false;
}
