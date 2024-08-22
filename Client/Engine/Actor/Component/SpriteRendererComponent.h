#pragma once
#include <vector>

#include "ActorComponent.h"
#include "Math/Color.h"
#include "Math/Math.h"
#include "Math/MathTypes.h"
#include "Misc/EngineMacros.h"

class Sprite;

class SpriteRendererComponent : public ActorComponent
{
    DECLARE_SHARED_CLASS(SpriteRendererComponent, ActorComponent)
    
public:
    SpriteRendererComponent(class Actor* owner, const std::wstring& kName);
    virtual ~SpriteRendererComponent() override = default;

    virtual void InitializeComponent() override;
    virtual void Render(float alpha) override;

    inline void SetSprite(const std::shared_ptr<Sprite>& sprite) { sprite_ = sprite; }
    inline std::shared_ptr<Sprite> GetSprite() const { return sprite_; }

    inline void SetFrameIndex(MathTypes::uint32 frame_index) { frame_index_ = frame_index; }
    inline MathTypes::uint32 GetFrameIndex() const { return frame_index_; }

    inline void SetFlipX(bool flip_x) { flip_x_ = flip_x; }
    inline bool GetFlipX() const { return flip_x_; }

    inline void IsFlipX(bool flip_y) { flip_y_ = flip_y; }
    inline bool IsFlipY() const { return flip_y_; }

    inline void SetColor(const Math::Color& color) { color_ = color; }
    inline Math::Color GetColor() const { return color_; }

private:
    friend class AnimatorComponent;
    
    std::shared_ptr<class Shape> shape_;
    std::shared_ptr<Sprite> sprite_;

    MathTypes::uint32 frame_index_;

    bool flip_x_;
    bool flip_y_;

    Math::Color color_;
    
};
