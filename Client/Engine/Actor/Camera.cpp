#include "pch.h"
#include "Camera.h"

std::weak_ptr<Camera> Camera::camera_;

Camera::Camera(const std::wstring& kName) :
    Actor(kName),
    size_(5.f),
    near_z_(.3f),
    far_z_(1000.f),
    aspect_(0.f)
{
}

void Camera::BeginPlay()
{
    Actor::BeginPlay();
    
    std::shared_ptr<Camera> camera = camera_.lock();
    if (!camera) camera_ = GetSharedThis();
    else Destroy();
    
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
