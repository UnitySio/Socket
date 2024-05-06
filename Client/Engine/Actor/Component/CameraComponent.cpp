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

    Viewport* viewport = g_renderer->FindViewport(GetWorld()->GetWindow());

}
