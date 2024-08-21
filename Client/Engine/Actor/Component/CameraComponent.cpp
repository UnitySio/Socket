#include "pch.h"
#include "CameraComponent.h"

#include "TransformComponent.h"
#include "Actor/Actor.h"
#include "Level/World.h"
#include "Windows/DX/Renderer.h"

CameraComponent::CameraComponent(Actor* owner, const std::wstring& kName) :
    Super(owner, kName),
    size_(5.f),
    near_z_(.3f),
    far_z_(1000.f),
    aspect_(0.f)
{
    UpdateAspect();
}

void CameraComponent::InitializeComponent()
{
    Super::InitializeComponent();

    World::Get()->SetCamera(GetOwner()->GetSharedThis());

    UpdateProjectionMatrix();
}

void CameraComponent::TickComponent(float delta_time)
{
    Super::TickComponent(delta_time);

    TransformComponent* transform = GetOwner()->GetTransform();
    Math::Vector2 position = transform->GetWorldPosition();

    if (Viewport* viewport = Renderer::Get()->FindViewport(World::Get()->GetWindow()))
    {
        viewport->view_matrix = DirectX::XMMatrixTranslation(-position.x, -position.y, 0.f)
            * DirectX::XMMatrixRotationZ(-transform->GetWorldRotationZ());
    }

    UpdateProjectionMatrix();
    UpdateAspect();
}

void CameraComponent::SetSize(float size)
{
    size_ = size;

    UpdateAspect();
    UpdateProjectionMatrix();
}

void CameraComponent::SetNearZ(float near_z)
{
    near_z_ = near_z;
    UpdateProjectionMatrix();
}

void CameraComponent::SetFarZ(float far_z)
{
    far_z_ = far_z;
    UpdateProjectionMatrix();
}

Bounds CameraComponent::GetBounds() const
{
    Math::Vector2 position = GetOwner()->GetTransform()->GetWorldPosition();

    const float height = size_ * 2.f;
    const float width = height * aspect_;
    
    return {position, {width, height}};
}

void CameraComponent::UpdateAspect()
{
    if (Viewport* viewport = Renderer::Get()->FindViewport(World::Get()->GetWindow()))
    {
        aspect_ = viewport->d3d_viewport.Width / viewport->d3d_viewport.Height;
    }
}

void CameraComponent::UpdateProjectionMatrix()
{
    if (Viewport* viewport = Renderer::Get()->FindViewport(World::Get()->GetWindow()))
    {
        const float screen_width = viewport->d3d_viewport.Width;
        const float screen_height = viewport->d3d_viewport.Height;
        const float aspect_ratio = screen_width / screen_height;
        const float left = -size_ * aspect_ratio;
        const float right = size_ * aspect_ratio;
        
        viewport->projection_matrix = DirectX::XMMatrixOrthographicOffCenterLH(left, right, -size_, size_, near_z_, far_z_);
    }
}
