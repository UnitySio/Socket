﻿#pragma once
#include <vector>

#include "Math/Rect.h"
#include "Math/Vector2.h"

enum AnchorPresets
{
    kLeft = (0x01<<0),
    kRight = (0x01<<1),
    kTop = (0x01<<2),
    kBottom = (0x01<<3),
    kCenter = (0x01<<4),
    kMiddle = (0x01<<5),
    kStretch = (0x01<<6)
};

class UIBase
{
public:
    UIBase(const std::wstring& kName);
    virtual ~UIBase() = default;

    void SetPosition(const Math::Vector2& kPosition);
    void SetPositionScreen(const Math::Vector2& kPosition);
    void SetSize(const Math::Vector2& kSize);
    void SetAnchorMin(const Math::Vector2& kAnchorMin);
    void SetAnchorMax(const Math::Vector2& kAnchorMax);
    void SetPivot(const Math::Vector2& kPivot);
    void SetAnchors(const Math::Vector2& kAnchorMin, const Math::Vector2& kAnchorMax);
    void SetAnchorPreset(MathTypes::uint16 anchor, bool match_pivot = false);
    void AttachToUI(UIBase* parent);
    void DetachFromUI();
    void Translate(const Math::Vector2& kTranslation);

protected:
    friend class Canvas;
    
    virtual void Tick(float deltaTime);
    virtual void Render();
    virtual void UpdateRect();

    std::wstring name_;

    Math::Rect rect_;
    
    Math::Vector2 position_;
    Math::Vector2 size_;
    Math::Vector2 anchor_min_;
    Math::Vector2 anchor_max_;
    Math::Vector2 pivot_;

    UIBase* parent_;
    std::vector<UIBase*> children_;

    bool is_focused_;
    bool is_clicked_;
    
};
