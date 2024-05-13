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
    size_(5.f),
    near_z(.3f),
    far_z_(1000.f),
    aspect_(0.f)
{
    UpdateAspect();
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

void CameraComponent::SetSize(float size)
{
    size_ = size;

    UpdateAspect();
    UpdateProjectionMatrix();
}

void CameraComponent::SetNearZ(float near_z)
{
    near_z = near_z;
    UpdateProjectionMatrix();
}

void CameraComponent::SetFarZ(float far_z)
{
    far_z_ = far_z;
    UpdateProjectionMatrix();
}

void CameraComponent::UpdateAspect()
{
    const WindowDefinition* definition = GetWorld()->GetWindow()->GetDefinition();
    aspect_ = size_ * definition->width / definition->height;
}

void CameraComponent::UpdateProjectionMatrix()
{
    if (Viewport* viewport = g_renderer->FindViewport(GetWorld()->GetWindow()))
    {
        const WindowDefinition* definition = GetWorld()->GetWindow()->GetDefinition();
        
        const float screen_width = definition->width;
        const float screen_height = definition->height;
        const float aspect_ratio = screen_width / screen_height;
        const float left = -size_ * aspect_ratio;
        const float right = size_ * aspect_ratio;
        
        viewport->projection_matrix = DirectX::XMMatrixOrthographicOffCenterLH(left, right, -size_, size_, near_z, far_z_);
    }
}
