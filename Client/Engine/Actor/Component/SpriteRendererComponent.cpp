#include "SpriteRendererComponent.h"

#include "TransformComponent.h"
#include "Actor/Actor.h"
#include "Level/World.h"
#include "Windows/DX/Shape.h"
#include "Windows/DX/Sprite.h"

SpriteRendererComponent::SpriteRendererComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName),
    shape_(nullptr),
    sprite_(nullptr),
    frame_index_(0),
    flip_x_(false),
    flip_y_(false)
{
}

void SpriteRendererComponent::InitializeComponent()
{
    ActorComponent::InitializeComponent();
    if (!sprite_) return;

    shape_ = std::make_shared<Shape>();
    shape_->SetVertices(sprite_->GetVertices());
    shape_->SetIndices(sprite_->GetIndices());
    shape_->SetTexture(sprite_);
}

void SpriteRendererComponent::Render(float alpha)
{
    ActorComponent::Render(alpha);
    if (!sprite_) return;

    const TransformComponent* transform = GetOwner()->GetTransform();
    if (!transform) return;

    const std::vector<SpriteFrame>& frames = sprite_->GetFrames();
    if (frames.empty() || frame_index_ >= frames.size()) return;

    const SpriteFrame& current_frame = frames[frame_index_];

    const float width = (sprite_->GetWidth() * current_frame.uv_scale.x / sprite_->GetPPU()) * transform->GetWorldScale().x;
    const float height = (sprite_->GetHeight() * current_frame.uv_scale.y / sprite_->GetPPU()) * transform->GetWorldScale().y;

    const float pivot_x = current_frame.pivot.x * width;
    const float pivot_y = current_frame.pivot.y * height;

    const int flip_x = flip_x_ ? -1 : 1;
    const int flip_y = flip_y_ ? -1 : 1;

    shape_->SetPosition(transform->GetWorldPosition());
    shape_->SetRotation(transform->GetWorldRotationZ());
    shape_->SetScale({width * flip_x, height * flip_y});
    shape_->SetUVOffset(current_frame.uv_offset);
    shape_->SetUVScale(current_frame.uv_scale);
    shape_->SetPivot({pivot_x, pivot_y});

    World::Get()->AddShape(shape_);
}
