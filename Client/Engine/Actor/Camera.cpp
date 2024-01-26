#include "Camera.h"

#include "../Core.h"
#include "box2d/b2_body.h"

Camera* Camera::instance_ = nullptr;

Camera::Camera(b2World* world) : Actor(world)
{
    instance_ = this;
    target_ = nullptr;
}

void Camera::Tick(float deltaTime)
{
    Core* core = Core::GetInstance();

    if (target_)
    {
        b2Vec2 target_position = target_->GetBody()->GetPosition();
        b2Vec2 lerp_position = Lerp(GetBody()->GetPosition(), target_position, deltaTime * .25f);
        GetBody()->SetTransform(lerp_position, 0.f);
    
        screen_position_ = lerp_position - b2Vec2(core->GetResolution().x / 2.f, core->GetResolution().y / 2.f);
    }
}

b2Vec2 Camera::GetRenderPosition(b2Vec2 position)
{
    if (!target_) return position;
    return position - screen_position_;
}

b2Vec2 Camera::GetScreenToWorldPosition(b2Vec2 position)
{
    if (!target_) return position;
    return position + screen_position_;
}

b2Vec2 Camera::Lerp(b2Vec2 a, b2Vec2 b, float t)
{
    b2Vec2 result;
    result.x = a.x + (b.x - a.x) * t;
    result.y = a.y + (b.y - a.y) * t;
    
    return result;
}
