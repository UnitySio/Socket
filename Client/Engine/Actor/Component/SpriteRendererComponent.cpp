#include "Graphics/Graphics.h"
#include "Graphics/SpriteBatch.h"
#include "SpriteRendererComponent.h"
#include "Graphics/Sprite.h"
#include "TransformComponent.h"

SpriteRendererComponent::SpriteRendererComponent(Actor* owner, const std::wstring& kName)
	:ActorComponent(owner, kName),sprite_(nullptr),flipX(false),flipY(false)
{
    SetRenderTarget();
}

void SpriteRendererComponent::SetRenderTarget(/*파라미터 추가*/)
{
    //리소스 매니저 구현 필요?
    Graphics* gfx = Graphics::Get();
    sprite_ = std::make_unique<Sprite>();
    assert(sprite_->Load(gfx->GetD3DDevice(), L"spritesheet.png"));

    sprite_->Split(3, 15, { .5f, 0.f });
}

void SpriteRendererComponent::RenderSprite()
{
    Graphics* gfx = Graphics::Get();
    SpriteBatch* batch = gfx->GetSpriteBatch();

    Actor* owner = GetOwner();
    TransformComponent* transform = owner->GetTransform();

    const Math::Vector2 location = transform->GetRelativeLocation();
    const float angle = transform->GetRelativeRotationZ();

    Math::Vector2 dir = { flipX ? 1.f : -1.f,flipY ? -1.f : 1.f};
    batch->Draw(sprite_.get(), L"spritesheet_" + std::to_wstring(0), location, {dir.x * 1.f, dir.y * 1.f}, angle);
}