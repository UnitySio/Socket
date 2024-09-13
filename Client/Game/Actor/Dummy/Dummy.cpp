#include "pch.h"
#include "Dummy.h"

#include "Actor/Camera.h"
#include "Input/Keyboard.h"
#include "Math/Math.h"

Dummy::Dummy(const std::wstring& kName) :
    Controller2D(kName),
    gravity_(0.f),
    jump_height_(3.5f),
    time_to_jump_apex_(.4f),
    jump_velocity_(0.f),
    move_speed_(5.f),
    velocity_(Math::Vector2::Zero())
{
}

void Dummy::BeginPlay()
{
    Controller2D::BeginPlay();
    
    Camera::Get()->SetTarget(this);

    gravity_ = -(2 * jump_height_) / Math::Pow(time_to_jump_apex_, 2);
    jump_velocity_ = Math::Abs(gravity_) * time_to_jump_apex_;
}

void Dummy::Tick(float delta_time)
{
    Controller2D::Tick(delta_time);

    if (collisions_.above || collisions_.below)
    {
        velocity_.y = 0.f;
    }

    Keyboard* keyboard = Keyboard::Get();
    float h = keyboard->GetKey(VK_RIGHT) - keyboard->GetKey(VK_LEFT);

    if (keyboard->GetKeyDown(VK_SPACE) && collisions_.below)
    {
        velocity_.y = jump_velocity_;
    }

    velocity_.x = h * move_speed_;
    velocity_.y += gravity_ * delta_time;
    Move(velocity_ * delta_time);
}
