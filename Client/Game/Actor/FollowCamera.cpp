#include "FollowCamera.h"

#include "Actor/Component/CameraComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Actor/Component/AudioListenerComponent.h"
#include "Audio/AudioManager.h"

FollowCamera::FollowCamera(b2World* world, const std::wstring& kName) :
    Actor(world, kName)
{
    camera_ = CreateComponent<CameraComponent>(L"Camera");
    audio_listener_ = CreateComponent<AudioListenerComponent>(L"AudioListener");
}

void FollowCamera::Tick(float delta_time)
{
    Actor::Tick(delta_time);

    const Vector location = GetTransform()->GetLocation();
    const Vector target_location = target_->GetTransform()->GetLocation();

    const Vector new_position = Vector::Lerp(location, target_location, delta_time * 2.f);
    GetTransform()->SetLocation(new_position);
}
