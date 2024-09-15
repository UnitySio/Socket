#include "pch.h"
#include "Player.h"

#include "Actor/Camera.h"
#include "Actor/Component/Controller2DComponent.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Input/Keyboard.h"
#include "Resource/ResourceManager.h"
#include "Windows/DX/Sprite.h"

Player::Player(const std::wstring& kName) :
    CharacterBase(kName)
{
    GetTransform()->SetScale({2.f, 2.f});
    
    if (ResourceManager::Get()->Load<Sprite>(L"Soldier", L".\\Game_Data\\Soldier.png"))
    {
        sprite_ = ResourceManager::Get()->GetResource<Sprite>(L"Soldier");
        sprite_->Split(9, 7, Sprite::kCenter);
        
        sprite_renderer_->SetSprite(sprite_);
    }

    standing_state_ = std::make_unique<PlayerStandingState>(this, state_machine_.get());
    state_machine_->ChangeState(standing_state_.get());
}

void Player::BeginPlay()
{
    CharacterBase::BeginPlay();

    Camera::Get()->SetTarget(this);
}
