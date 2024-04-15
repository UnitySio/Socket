#include "FollowCamera.h"

#include "Actor/Component/CameraComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Audio/AudioManager.h"

FollowCamera::FollowCamera(b2World* world, const std::wstring& kName) :
    Actor(world, kName)
{
    camera_ = CreateComponent<CameraComponent>(L"Camera");
}

void FollowCamera::Tick(float delta_time)
{
    Actor::Tick(delta_time);

    const Math::Vector location = GetTransform()->GetRelativeLocation();
    const Math::Vector target_location = target_->GetTransform()->GetRelativeLocation();

    const Math::Vector new_position = Math::Vector::Lerp(location, target_location, delta_time * 2.f);
    GetTransform()->SetRelativeLocation(new_position);
}
