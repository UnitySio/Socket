#include "pch.h"
#include "CharacterBase.h"

#include "DebugDrawHelper.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/Animator/AnimatorComponent.h"
#include "Actor/Component/CapsuleColliderComponent.h"
#include "Actor/Component/RigidBody2DComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Math/Math.h"
#include "Physics/Physics2D.h"

CharacterBase::CharacterBase(const std::wstring& kName) :
    StateMachine(kName),
    is_jumping_(false),
    is_jump_falling_(false),
    is_falling_(false),
    move_axis_(Math::Vector2::Zero()),
    ground_check_size_({.4f, .1f}),
    last_grounded_time_(0.f),
    coyote_time_(.15f),
    jump_force_(5.f),
    gravity_scale_(1.f),
    fall_gravity_multiplier_(2.f),
    max_fall_speed_(10.f),
    jump_hang_time_threshold_(.1f),
    jump_hang_gravity_multiplier_(.5f)
{
    sprite_renderer_ = AddComponent<SpriteRendererComponent>(L"SpriteRenderer");
    animator_ = AddComponent<AnimatorComponent>(L"Animator");

    PhysicsMaterial2D material = {0.f, 0.f};
    
    capsule_collider_ = AddComponent<CapsuleColliderComponent>(L"CapsuleCollider");
    capsule_collider_->SetMaterial(material);
    capsule_collider_->SetSize({1.f, 1.f});
    capsule_collider_->SetPreSolve(true);

    rigid_body_ = AddComponent<RigidBody2DComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kDynamic);
    rigid_body_->SetFreezeRotation(true);
    rigid_body_->UseAutoMass(false);
    
}

void CharacterBase::Tick(float delta_time)
{
    StateMachine::Tick(delta_time);

    Math::Vector2 position = GetTransform()->GetPosition();

    last_grounded_time_ -= delta_time;
    
    if (is_jumping_ && rigid_body_->GetLinearVelocityY() < 0.f)
    {
        is_jumping_ = false;
        is_jump_falling_ = true;
    }

    if (last_grounded_time_ > 0.f && is_jump_falling_)
    {
        is_jump_falling_ = false;
    }
    
    Math::Vector2 center = position + Math::Vector2::Down() * .5f;

    Actor* ground = nullptr;
    if (Physics2D::OverlapBox(center, ground_check_size_, &ground, ActorLayer::kGround) && !is_jumping_)
    {
        last_grounded_time_ = coyote_time_;
        DebugDrawHelper::Get()->DrawBox(center, ground_check_size_, Math::Color::Green);
    }
    else
    {
        DebugDrawHelper::Get()->DrawBox(center, ground_check_size_, Math::Color::Red);
    }

    if ((is_jumping_ || is_jump_falling_) && Math::Abs(rigid_body_->GetLinearVelocityY()) < jump_hang_time_threshold_)
    {
        rigid_body_->SetGravityScale(gravity_scale_ * jump_hang_gravity_multiplier_);
    }
    else if (rigid_body_->GetLinearVelocityY() < 0.f)
    {
        rigid_body_->SetGravityScale(gravity_scale_ * fall_gravity_multiplier_);
        rigid_body_->SetLinearVelocityY(Math::Max(rigid_body_->GetLinearVelocityY(), -max_fall_speed_));
        
        is_falling_ = true;
    }
    else
    {
        rigid_body_->SetGravityScale(gravity_scale_);
        is_falling_ = false;
    }
}

void CharacterBase::Jump()
{
    is_jumping_ = true;
    is_jump_falling_ = false;
    
    float force = jump_force_;
    if (rigid_body_->GetLinearVelocityY() < 0.f) force -= rigid_body_->GetLinearVelocityY();

    rigid_body_->AddForceY(force, ForceMode::kImpulse);
}

bool CharacterBase::CanJump() const
{
    return last_grounded_time_ > 0.f && !is_jumping_;
}
