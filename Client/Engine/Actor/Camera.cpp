#include "Camera.h"

#include "../Core.h"
#include "box2d/b2_body.h"

Camera* Camera::instance_ = nullptr;

Camera::Camera(b2World* world) : Actor(world)
{
    instance_ = this;
}

void Camera::Tick(float deltaTime)
{
    std::shared_ptr<Core> core = Core::GetInstance();
    screen_position_ = GetBody()->GetPosition() - b2Vec2(core->GetResolution().x / 2.f, core->GetResolution().y / 2.f);
}

b2Vec2 Camera::GetRenderPosition(b2Vec2 position)
{
    return position - screen_position_;
}
