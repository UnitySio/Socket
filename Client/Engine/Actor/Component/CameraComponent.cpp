#include "CameraComponent.h"

#include "TransformComponent.h"
#include "Actor/Actor.h"
#include "Level/World.h"
#include "Misc/EngineMacros.h"
#include "Windows/WindowDefinition.h"
#include "Windows/WindowsWindow.h"
#include "Windows/D3D/Renderer.h"

CameraComponent::CameraComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName),
    camera_size_(5.f),
    camera_near_z(.3f),
    camera_far_z(1000.f)
{
}

void CameraComponent::InitializeComponent()
{
    ActorComponent::InitializeComponent();

    UpdateProjectionMatrix();
}

void CameraComponent::TickComponent(float delta_time)
{
    ActorComponent::TickComponent(delta_time);

    TransformComponent* transform = GetOwner()->GetTransform();
    Math::Vector2 location = transform->GetWorldLocation();

    if (Viewport* viewport = g_renderer->FindViewport(GetWorld()->GetWindow()))
    {
        viewport->view_matrix = DirectX::XMMatrixTranslation(-location.x, -location.y, 0.f)
            * DirectX::XMMatrixRotationZ(-transform->GetWorldRotationZ());
    }
}

void CameraComponent::SetCameraSize(float size)
{
    camera_size_ = size;
    UpdateProjectionMatrix();
}

void CameraComponent::SetCameraNearZ(float near_z)
{
    camera_near_z = near_z;
    UpdateProjectionMatrix();
}

void CameraComponent::SetCameraFarZ(float far_z)
{
    camera_far_z = far_z;
    UpdateProjectionMatrix();
}

void CameraComponent::UpdateProjectionMatrix()
{
    if (Viewport* viewport = g_renderer->FindViewport(GetWorld()->GetWindow()))
    {
        const WindowDefinition* definition = GetWorld()->GetWindow()->GetDefinition();
        
        const float screen_width = definition->width;
        const float screen_height = definition->height;
        const float aspect_ratio = screen_width / screen_height;
        const float left = -camera_size_ * aspect_ratio;
        const float right = camera_size_ * aspect_ratio;
        
        viewport->projection_matrix = DirectX::XMMatrixOrthographicOffCenterLH(left, right, -camera_size_, camera_size_, camera_near_z, camera_far_z);
    }
}
