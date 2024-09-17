#include "pch.h"
#include "Player.h"

#include "Actor/Camera.h"
#include "Actor/Component/Controller2DComponent.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Input/Keyboard.h"
#include "Math/Math.h"
#include "Resource/ResourceManager.h"
#include "State/PlayerJumpingState.h"
#include "State/PlayerStandingState.h"
#include "Windows/DX/Sprite.h"

Player::Player(const std::wstring& kName) :
    CharacterBase(kName),
    gravity_(0.f),
    jump_height_(2.f),
    time_to_jump_apex_(.4f),
    jump_velocity_(0.f),
    move_speed_(3.f),
    last_pressed_jump_time_(0.f)
{
    GetTransform()->SetPosition({10.f, 0.f});
    GetTransform()->SetScale({2.f, 2.f});
    
    if (ResourceManager::Get()->Load<Sprite>(L"Soldier", L".\\Game_Data\\Soldier.png"))
    {
        sprite_ = ResourceManager::Get()->GetResource<Sprite>(L"Soldier");
        sprite_->Split(9, 7, Sprite::kCenter);
        
        sprite_renderer_->SetSprite(sprite_);
    }

    states_[0] = std::make_unique<PlayerStandingState>(this, state_machine_.get());
    states_[1] = std::make_unique<PlayerJumpingState>(this, state_machine_.get());
}

void Player::BeginPlay()
{
    CharacterBase::BeginPlay();

    Camera::Get()->SetTarget(this);

    state_machine_->ChangeState(states_[0].get());

    gravity_ = -(2 * jump_height_) / std::pow(time_to_jump_apex_, 2);
    jump_velocity_ = Math::Abs(gravity_) * time_to_jump_apex_;
}

void Player::Tick(float delta_time)
{
    CharacterBase::Tick(delta_time);

    last_pressed_jump_time_ -= delta_time;

    Keyboard* keyboard = Keyboard::Get();
    if (keyboard->GetKeyDown('C'))
    {
        last_pressed_jump_time_ = .1f;
    }
}
