#pragma once
#include "Math/Rect.h"
#include "Math/Vector2.h"

class UIBase
{
public:
    UIBase();
    virtual ~UIBase() = default;

    void SetPosition(const Math::Vector2& kPosition);
    void SetSize(const Math::Vector2& kSize);
    void SetAnchorMin(const Math::Vector2& kAnchorMin);
    void SetAnchorMax(const Math::Vector2& kAnchorMax);
    void SetPivot(const Math::Vector2& kPivot);

protected:
    friend class Canvas;

    virtual void Render();
    virtual void UpdateRect();

    Math::Rect rect_;
    
    Math::Vector2 position_;
    Math::Vector2 size_;
    Math::Vector2 anchor_min_;
    Math::Vector2 anchor_max_;
    Math::Vector2 pivot_;
    
};
