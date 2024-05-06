#include "CameraComponent.h"

#include "TransformComponent.h"
#include "Level/World.h"
#include "Misc/EngineMacros.h"
#include "Windows/D3D/Renderer.h"

CameraComponent::CameraComponent(Actor* owner, const std::wstring& kName) : ActorComponent(owner, kName)
{
}

void CameraComponent::TickComponent(float delta_time)
{
    ActorComponent::TickComponent(delta_time);

    if (Viewport* viewport = g_renderer->FindViewport(GetWorld()->GetWindow()))
    {
        viewport->view_matrix = DirectX::XMMatrixTranslation(-0.f, -0.f, 0.f)
            * DirectX::XMMatrixRotationRollPitchYaw(-0.f, -0.f, -0.f);
    }

}
