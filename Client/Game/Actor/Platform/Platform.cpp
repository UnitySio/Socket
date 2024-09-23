#include "pch.h"
#include "Platform.h"

#include "Actor/Component/BoxColliderComponent.h"
#include "PlatformControllerComponent.h"

Platform::Platform(const std::wstring& kName) :
    Actor(kName)
{
    SetLayer(ActorLayer::kGround);
    
    collider_ = AddComponent<BoxColliderComponent>(L"BoxCollider");
    collider_->SetSize({2.f, 1.f});
    
    controller_ = AddComponent<PlatformControllerComponent>(L"PlatformController");
    controller_->SetCollider(collider_);
}

void Platform::Tick(float delta_time)
{
    Actor::Tick(delta_time);
}
