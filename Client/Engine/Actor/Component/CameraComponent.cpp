﻿#include "CameraComponent.h"

#include "TransformComponent.h"
#include "Actor/Actor.h"
#include "Level/World.h"
#include "Windows/DX/Renderer.h"

CameraComponent::CameraComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName),
    size_(5.f),
    near_z_(.3f),
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

    if (Viewport* viewport = Renderer::Get()->FindViewport(World::Get()->GetWindow()))
    {
        viewport->view_matrix = DirectX::XMMatrixTranslation(-location.x, -location.y, 0.f)
            * DirectX::XMMatrixRotationZ(-transform->GetWorldRotationZ());
    }

    UpdateProjectionMatrix();
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

void CameraComponent::UpdateAspect()
{
    if (Viewport* viewport = Renderer::Get()->FindViewport(World::Get()->GetWindow()))
    {
        aspect_ = size_ * viewport->d3d_viewport.Width / viewport->d3d_viewport.Height;
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
