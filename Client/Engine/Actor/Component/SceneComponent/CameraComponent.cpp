#include "CameraComponent.h"

#include "Core.h"
#include "Graphics/Graphics.h"
#include "Level/Level.h"
#include "Level/World.h"

CameraComponent::CameraComponent(Actor* owner, const std::wstring& kName) : SceneComponent(owner, kName)
{
}

void CameraComponent::TickComponent(float delta_time)
{
    SceneComponent::TickComponent(delta_time);

    Graphics* gfx = Graphics::Get();
    Camera2D& camera = gfx->GetCamera2D();

    camera.SetPosition(GetRelativeLocation().x, GetRelativeLocation().y, 0.f);
}
