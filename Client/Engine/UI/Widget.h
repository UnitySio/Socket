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

class Widget
{
public:
    Widget(const std::wstring& kName);
    virtual ~Widget() = default;

    void SetPosition(const Math::Vector2& kPosition);
    void SetPositionScreen(const Math::Vector2& kPosition);
    void SetSize(const Math::Vector2& kSize);
    void SetAnchorMin(const Math::Vector2& kAnchorMin);
    void SetAnchorMax(const Math::Vector2& kAnchorMax);
    void SetPivot(const Math::Vector2& kPivot);
    void SetAnchors(const Math::Vector2& kAnchorMin, const Math::Vector2& kAnchorMax);
    void SetAnchorPreset(MathTypes::uint16 anchor, bool match_pivot = false);
    void AttachToWidget(Widget* parent);
    void DetachFromUI();
    
    Math::Vector2 GetPivotPosition() const;
    
    inline float GetAngle() const { return angle_; }
    
    inline Widget* GetParent() const { return parent_; }
    inline const std::vector<Widget*>& GetChildren() const { return children_; }
    
    inline bool IsFocused() const { return is_focused_; }

protected:
    friend class Canvas;

    inline virtual void OnMousePressed() {}
    inline virtual void OnMouseReleased() {}
    inline virtual void OnMouseHover() {}
    inline virtual void OnMouseLeave() {}
    inline virtual void OnKeyEvent(MathTypes::uint16 key_code, bool is_pressed) {}
    inline virtual void OnCharEvent(wchar_t character) {}
    inline virtual void BeginPlay() {}
    inline virtual void Tick(float delta_time) {}
    inline virtual void Render() {}
    
    virtual void OnFocus();
    virtual void OnBlur();
    
    virtual void UpdateRect();
    
    static MathTypes::uint32 next_z_index_;

    std::wstring name_;

    Math::Rect rect_;
    
    Math::Vector2 position_;
    Math::Vector2 size_;
    Math::Vector2 anchor_min_;
    Math::Vector2 anchor_max_;
    Math::Vector2 pivot_;

    float angle_;

    Widget* parent_;
    std::vector<Widget*> children_;

    MathTypes::uint32 z_index_;

    bool is_focused_;
    
};
