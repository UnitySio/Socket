#include "pch.h"
#include "Camera.h"

#include "Component/TransformComponent.h"
#include "Level/World.h"
#include "Windows/DX/Renderer.h"

std::weak_ptr<Camera> Camera::camera_;

Camera::Camera(const std::wstring& kName) :
    Actor(kName),
    size_(5.f),
    near_z_(.3f),
    far_z_(1000.f),
    target_(nullptr)
{
}

void Camera::BeginPlay()
{
    Actor::BeginPlay();
    
    std::shared_ptr<Camera> camera = camera_.lock();
    if (!camera) camera_ = GetSharedThis();
    else
    {
        Destroy();
        return;
    }

    UpdateProjectionMatrix();
    
}

void Camera::PhysicsTick(float delta_time)
{
    Actor::PhysicsTick(delta_time);

    // 테스트용
    if (target_)
    {
        GetTransform()->SetPosition(target_->GetTransform()->GetPosition());
    }
    
    TransformComponent* transform = GetTransform();
    Math::Vector2 position = transform->GetPosition();

    if (Viewport* viewport = Renderer::Get()->FindViewport(World::Get()->GetWindow()))
    {
        viewport->view_matrix = DirectX::XMMatrixTranslation(-position.x, -position.y, 0.f)
            * DirectX::XMMatrixRotationZ(-transform->GetAngle());
    }
}

Camera* Camera::Get()
{
    if (camera_.expired()) return nullptr;
    if (const auto kCamera = camera_.lock())
    {
        if (Camera* ptr = kCamera.get(); IsValid(ptr)) return ptr;
    }

    return nullptr;
}

void Camera::SetSize(float size)
{
    size_ = size;
    UpdateProjectionMatrix();
}

void Camera::SetNearZ(float near_z)
{
    near_z_ = near_z;
    UpdateProjectionMatrix();
}

void Camera::SetFarZ(float far_z)
{
    far_z_ = far_z;
    UpdateProjectionMatrix();
}

float Camera::GetAspect() const
{
    if (Viewport* viewport = Renderer::Get()->FindViewport(World::Get()->GetWindow()))
    {
        return viewport->d3d_viewport.Width / viewport->d3d_viewport.Height;
    }

    return 0.f;
}

Bounds Camera::GetBounds() const
{
    Math::Vector2 position = GetTransform()->GetPosition();

    const float height = size_ * 2.f;
    const float width = height * GetAspect();
    
    return {position, {width, height}};
}

void Camera::UpdateProjectionMatrix() const
{
    if (Viewport* viewport = Renderer::Get()->FindViewport(World::Get()->GetWindow()))
    {
        const float aspect = GetAspect();
        const float left = -size_ * aspect;
        const float right = size_ * aspect;
        
        viewport->projection_matrix = DirectX::XMMatrixOrthographicOffCenterLH(left, right, -size_, size_, near_z_, far_z_);
    }
}
