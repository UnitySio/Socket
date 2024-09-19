#include "pch.h"
#include "PlayerStandingState.h"

#include "Actor/Character/Player/Player.h"
#include "Actor/Component/Controller2DComponent.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/Animator/AnimatorComponent.h"
#include "imgui/imgui_internal.h"
#include "Input/Keyboard.h"
#include "Math/Math.h"

PlayerStandingState::PlayerStandingState(Actor* actor, StateMachine* state_machine) :
    State(actor, state_machine),
    player_(nullptr),
    sprite_renderer_(nullptr),
    controller_(nullptr),
    velocity_(Math::Vector2::Zero()),
    last_grounded_time_(0.f),
    coyote_time_(.15f),
    last_double_tap_time_(0.f),
    is_running_(false)
{
}

void PlayerStandingState::Enter()
{
    player_ = dynamic_cast<Player*>(owner_);
    if (player_)
    {
        sprite_renderer_ = player_->GetSpriteRenderer();
        animator_ = player_->GetAnimator();
        controller_ = player_->GetController();

        animator_->PlayClip(L"Idle");
    }
}

void PlayerStandingState::Exit()
{
    velocity_ = Math::Vector2::Zero();
    last_grounded_time_ = 0.f;
}

void PlayerStandingState::PhysicsTick(float delta_time)
{
    float move_speed = is_running_ ? player_->GetRunSpeed() : player_->GetWalkSpeed();
    velocity_.x = player_->GetInputX() * move_speed;
    velocity_.y += player_->GetGravity() * delta_time;
    
    if (controller_)
    {
        controller_->Move(velocity_ * delta_time);

        if (controller_->IsWall())
        {
            velocity_.x = 0.f;
        }

        const CollisionInfo& collisions = controller_->GetCollisions();

        if (controller_->IsGrounded())
        {
            if (collisions.sliding_down_max_slope)
                velocity_.y += collisions.slope_normal.y * -player_->GetGravity() * delta_time;
            else velocity_.y = 0.f;
        }
    }
}

void PlayerStandingState::Tick(float delta_time)
{
    HandleTime(delta_time);

    Keyboard* keyboard = Keyboard::Get();
    if (keyboard->GetKeyDown(VK_LEFT) || keyboard->GetKeyDown(VK_RIGHT))
    {
        if (last_double_tap_time_ > 0.f)
        {
            is_running_ = true;
            last_double_tap_time_ = 0.f;
        }
        else
        {
            last_double_tap_time_ = .2f;
        }
    }

    if (is_running_ && !keyboard->GetKey(VK_LEFT) && !keyboard->GetKey(VK_RIGHT))
    {
        is_running_ = false;
    }

    if (ImGui::Begin("Property"))
    {
        ImGui::Text("Last Double Tap Time: %.2f", last_double_tap_time_);
        ImGui::Text("Is Running: %s", is_running_ ? "True" : "False");
    }

    ImGui::End();
}

void PlayerStandingState::PostTick(float delta_time)
{
}

void PlayerStandingState::HandleTime(float delta_time)
{
#pragma region Coyote Time
    if (controller_->IsGrounded())
    {
        last_grounded_time_ = coyote_time_;
    }
    else if (last_grounded_time_ > 0.f)
    {
        last_grounded_time_ = Math::Max(last_grounded_time_ - delta_time, 0.f);
    }
#pragma endregion

#pragma region Double Tap Time
    if (last_double_tap_time_ > 0.f)
    {
        last_double_tap_time_ = Math::Max(last_double_tap_time_ - delta_time, 0.f);
    }
#pragma endregion
}
