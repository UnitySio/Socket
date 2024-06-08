#include "SpriteRendererComponent.h"
#include "../../Windows/DX/Sprite.h"
#include "TransformComponent.h"

SpriteRendererComponent::SpriteRendererComponent(Actor* owner, const std::wstring& kName):ActorComponent(owner, kName),
    sprite_(nullptr), flipX(false), flipY(false)
{
    
}

void SpriteRendererComponent::SetRenderTarget(std::shared_ptr<Sprite> sprite)
{
    sprite_ = sprite;
}

void SpriteRendererComponent::SetFlipX(bool value) { flipX = value; }
bool SpriteRendererComponent::GetFlipX() { return flipX; }