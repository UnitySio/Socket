#include "CameraComponent.h"

#include "TransformComponent.h"
#include "Actor/Actor.h"
#include "Graphics/Graphics.h"

CameraComponent::CameraComponent(Actor* owner, const std::wstring& kName) : ActorComponent(owner, kName)
{
}

void CameraComponent::TickComponent(float delta_time)
{
    ActorComponent::TickComponent(delta_time);

    Graphics* gfx = Graphics::Get();
    Camera2D& camera = gfx->GetCamera2D();

    const Vector location = owner_->GetTransform()->GetLocation();
    camera.SetPosition(location.x, location.y, 0.f);
}
