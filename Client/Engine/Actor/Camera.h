#pragma once
#include "Actor.h"

class Camera : public Actor
{
    SHADER_CLASS_HELPER(Camera)
    
public:
    Camera(const std::wstring& kName);
    virtual ~Camera() override = default;

    virtual void BeginPlay() override;

    static Camera* Get();

private:
    static std::weak_ptr<Camera> camera_;
    
    float size_;
    float near_z_;
    float far_z_;
    float aspect_;
    
};
