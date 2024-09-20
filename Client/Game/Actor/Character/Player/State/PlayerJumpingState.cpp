#include "pch.h"
#include "PlayerJumpingState.h"

#include "Actor/Character/Player/Player.h"
#include "Actor/Component/Controller2DComponent.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/Animator/AnimatorComponent.h"
#include "Input/Keyboard.h"
#include "Math/Math.h"

PlayerJumpingState::PlayerJumpingState(Actor* actor, StateMachine* state_machine) :
    State(actor, state_machine),
    player_(nullptr),
    sprite_renderer_(nullptr),
    animator_(nullptr),
    controller_(nullptr),
    input_x_(0),
    jump_count_(0)
{
}

void PlayerJumpingState::Enter()
{
    player_ = dynamic_cast<Player*>(owner_);
    if (player_)
    {
        sprite_renderer_ = player_->GetSpriteRenderer();
        animator_ = player_->GetAnimator();
        controller_ = player_->GetController();

        animator_->PlayClip(L"Jump");

        Math::Vector2 velocity = player_->GetVelocity();
        
        const CollisionInfo& collisions = controller_->GetCollisions();
        if (collisions.sliding_down_max_slope)
        {
            velocity.y = player_->GetJumpVelocity() * collisions.slope_normal.y;
            velocity.x = player_->GetJumpVelocity() * collisions.slope_normal.x;
        }
        else velocity.y = player_->GetJumpVelocity();
        
        player_->SetVelocity(velocity);

        jump_count_++;
    }
}

void PlayerJumpingState::Exit()
{
    Math::Vector2 velocity = player_->GetVelocity();
    velocity.x = 0.f;
    player_->SetVelocity(velocity);

    input_x_ = 0;
    jump_count_ = 0;
}

void PlayerJumpingState::PhysicsTick(float delta_time)
{
    Math::Vector2 velocity = player_->GetVelocity();
    if (player_->GetLastPressedJumpTime() > 0.f && jump_count_ < 2)
    {
        player_->ResetLastPressedJumpTime();
        
        velocity.x *= input_x_;
        velocity.y = player_->GetJumpVelocity();
        
        jump_count_++;
    }
    
    velocity.y += player_->GetGravity() * delta_time;
    player_->SetVelocity(velocity);
    
    controller_->Move(velocity * delta_time);
    
    const CollisionInfo& collisions = controller_->GetCollisions();
    if (collisions.below)
    {
        state_machine_->ChangeState(player_->GetState(0));
        return;
    }
}

void PlayerJumpingState::Tick(float delta_time)
{
    Keyboard* keyboard = Keyboard::Get();
    input_x_ = keyboard->GetKey(VK_RIGHT) - keyboard->GetKey(VK_LEFT);
    if (Math::Abs(input_x_) > 0)
    {
        if (sprite_renderer_) sprite_renderer_->SetFlipX(input_x_ < 0);
    }
}

void PlayerJumpingState::PostTick(float delta_time)
{
}
