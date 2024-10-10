#include "pch.h"
#include "TopDownCharacter.h"

#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Input/Keyboard.h"
#include "Resource/ResourceManager.h"
#include "Windows/DX/Sprite.h"

TopDownCharacter::TopDownCharacter(const std::wstring& name) :
    Actor(name),
    gravity_(9.8f),
    z_(0.f),
    z_height_(0.f),
    z_floor_(0.f),
    z_speed_(0.f)
{
    shadow_renderer_ = AddComponent<SpriteRendererComponent>(L"ShadowRenderer");
    shadow_renderer_->SetManual(true);
    
    sprite_renderer_ = AddComponent<SpriteRendererComponent>(L"SpriteRenderer");
    sprite_renderer_->SetManual(true);

    if (ResourceManager::Get()->Load<Sprite>(L"Square", L".\\Game_Data\\Default\\Square.png"))
    {
        shadow_ = ResourceManager::Get()->GetResource<Sprite>(L"Square");
        shadow_->Split(1, 1, Sprite::kCenter);
        shadow_->SetPPU(512);

        shadow_renderer_->SetSprite(shadow_);
    }
    
    if (ResourceManager::Get()->Load<Sprite>(L"PlayerSheet", L".\\Game_Data\\PlayerSheet.png"))
    {
        sprite_ = ResourceManager::Get()->GetResource<Sprite>(L"PlayerSheet");
        sprite_->Split(8, 7, Sprite::kBottom);

        sprite_renderer_->SetSprite(sprite_);
    }
    
}

void TopDownCharacter::BeginPlay()
{
    Actor::BeginPlay();

    if (sprite_) z_height_ = sprite_->GetHeight() * .5f;
    
}

void TopDownCharacter::Tick(float delta_time)
{
    Actor::Tick(delta_time);

    Keyboard* keyboard = Keyboard::Get();

    const float h = keyboard->GetKey(VK_RIGHT) - keyboard->GetKey(VK_LEFT);
    const float v = keyboard->GetKey(VK_UP) - keyboard->GetKey(VK_DOWN);

    if (keyboard->GetKeyDown(VK_SPACE))
    {
        z_speed_ = 5.f;
    }

    float h_speed = 3.f * delta_time;
    float v_speed = 2.f * delta_time;

    if (z_ != z_floor_) z_speed_ -= gravity_ * delta_time;
    // if (z_ - z_speed_ > z_floor_)
    if (z_ < z_floor_)
    {
        z_ = z_floor_;
        z_speed_ = 0.f;
    }

    GetTransform()->Translate({h * h_speed, v * v_speed});
    z_ += z_speed_ * delta_time;
}

void TopDownCharacter::PostTick(float delta_time)
{
    Actor::PostTick(delta_time);

    TransformComponent* transform = GetTransform();

    Math::Vector2 position = transform->GetPosition();
    shadow_renderer_->SetPosition({position.x, position.y + z_floor_});

    shadow_renderer_->SetScale(transform->GetScale());
    shadow_renderer_->SetAngle(transform->GetAngle());
    
    sprite_renderer_->SetPosition({position.x, position.y + z_});    
    
    sprite_renderer_->SetScale(transform->GetScale());
    sprite_renderer_->SetAngle(transform->GetAngle());
}

RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<TopDownCharacter>("TopDownCharacter")
        .constructor<const std::wstring&>()
        (
            policy::ctor::as_std_shared_ptr
        );
}
