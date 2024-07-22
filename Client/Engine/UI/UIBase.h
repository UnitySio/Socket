#pragma once
#include "Math/Vector2.h"

class UIBase
{
public:
    UIBase();
    virtual ~UIBase() = default;

protected:
    friend class Canvas;

    virtual void Render() = 0;

    Math::Vector2 relative_position_;

    Math::Vector2 anchor_min_;
    Math::Vector2 anchor_max_;
    
};
