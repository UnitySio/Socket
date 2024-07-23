#pragma once
#include "Math/Vector2.h"

class UIBase
{
public:
    UIBase();
    virtual ~UIBase() = default;

    void SetPosition(const Math::Vector2& position);
    void SetSize(const Math::Vector2& size);

protected:
    friend class Canvas;

    virtual void Render();

    Math::Vector2 position_;
    Math::Vector2 size_;
    Math::Vector2 anchor_min_;
    Math::Vector2 anchor_max_;
    Math::Vector2 pivot_;
    
};
