#include "FollowCamera.h"

#include "Actor/Component/CameraComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Audio/AudioManager.h"

FollowCamera::FollowCamera(World* world, const std::wstring& kName) :
    Actor(world, kName),
    follow_(nullptr)
{
    camera_ = CreateComponent<CameraComponent>(L"Camera");
}

void FollowCamera::Tick(float delta_time)
{
    Actor::Tick(delta_time);

    if (follow_)
    {
        const Math::Vector2 location = GetTransform()->GetRelativeLocation();
        const Math::Vector2 target_location = follow_->GetTransform()->GetRelativeLocation();

        const Math::Vector2 new_position = Math::Vector2::Lerp(location, target_location, delta_time * 2.f);
        GetTransform()->SetRelativeLocation(new_position);
    }
}
