#include "FollowCamera.h"

#include <iostream>

#include "../../Engine/Actor/Component/SceneComponent/CameraComponent.h"

FollowCamera::FollowCamera(b2World* world, const std::wstring& kName) :
    Actor(world, kName)
{
    camera_ = CreateComponent<CameraComponent>(L"Camera");
    SetRootComponent(camera_);
}

void FollowCamera::Tick(float delta_time)
{
    Actor::Tick(delta_time);

    Vector new_position = Vector::Lerp(GetActorLocation(), target_->GetActorLocation(), delta_time);
    SetActorLocation({new_position.x, new_position.y});
}
