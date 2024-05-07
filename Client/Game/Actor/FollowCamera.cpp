#include "FollowCamera.h"

#include "Actor/Component/CameraComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Audio/AudioManager.h"

FollowCamera::FollowCamera(World* world, const std::wstring& kName) :
    Actor(world, kName)
{
    camera_ = CreateComponent<CameraComponent>(L"Camera");
}

void FollowCamera::Tick(float delta_time)
{
    Actor::Tick(delta_time);
    
}
