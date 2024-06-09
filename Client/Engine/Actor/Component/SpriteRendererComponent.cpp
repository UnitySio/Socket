#include "SpriteRendererComponent.h"
#include "../../Windows/DX/Sprite.h"
#include "TransformComponent.h"

SpriteRendererComponent::SpriteRendererComponent(Actor* owner, const std::wstring& kName):ActorComponent(owner, kName),
    sprite_(nullptr), flipX(false), flipY(false), frame_index_(0)
{
    
}

void SpriteRendererComponent::SetRenderTarget(std::shared_ptr<Sprite> sprite)
{
    sprite_ = sprite;
}

int SpriteRendererComponent::GetFrameIndex()
{
    return frame_index_;
}

void SpriteRendererComponent::SetFlipX(bool value) { flipX = value; }
bool SpriteRendererComponent::GetFlipX() { return flipX; }