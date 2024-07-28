#pragma once
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
    void AttachToUI(Widget* parent);
    void DetachFromUI();
    
    Math::Vector2 GetPivotPosition() const;
    
    inline float GetAngle() const { return angle_; }
    
    inline Widget* GetParent() const { return parent_; }
    inline const std::vector<Widget*>& GetChildren() const { return children_; }

protected:
    friend class Canvas;

    virtual inline void OnMousePressed() {}
    virtual inline void OnMouseReleased() {}
    virtual void Render() = 0;
    
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

    bool is_hovered_;
    
};
