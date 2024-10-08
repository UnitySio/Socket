﻿#include "pch.h"
#include "CharacterBase.h"

#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/Animator/AnimatorComponent.h"
#include "Actor/Component/Controller2DComponent.h"
#include "Actor/StateMachine/StateMachine.h"
#include "rttr/registration.h"
#include "rttr/detail/registration/registration_impl.h"

CharacterBase::CharacterBase(const std::wstring& kName) :
    Actor(kName)
{
    state_machine_ = std::make_unique<StateMachine>();
    
    sprite_renderer_ = AddComponent<SpriteRendererComponent>(L"SpriteRenderer");
    animator_ = AddComponent<AnimatorComponent>(L"Animator");
    capsule_collider_ = AddComponent<CapsuleColliderComponent>(L"CapsuleCollider");
    capsule_collider_->SetSize({.5f, .5f});
    
    controller_ = AddComponent<Controller2DComponent>(L"Controller2D");
    controller_->SetCollider(capsule_collider_);
}

void CharacterBase::PhysicsTick(float delta_time)
{
    Actor::PhysicsTick(delta_time);

    state_machine_->PhysicsTick(delta_time);
}

void CharacterBase::Tick(float delta_time)
{
    Actor::Tick(delta_time);

    state_machine_->Tick(delta_time);
}

void CharacterBase::PostTick(float delta_time)
{
    Actor::PostTick(delta_time);

    state_machine_->PostTick(delta_time);
}

RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<CharacterBase>("CharacterBase")
        .constructor<const std::wstring&>()
        (
            policy::ctor::as_std_shared_ptr
        );
}
