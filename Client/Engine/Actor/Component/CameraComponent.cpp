#include "CameraComponent.h"

#include "../Actor.h"
#include "../../Core.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneManager.h"
#include "box2d/b2_body.h"

CameraComponent::CameraComponent(Actor* owner, const std::wstring& name) : ActorComponent(owner, name)
{
}

void CameraComponent::TickComponent(float delta_time)
{
    Core* core = Core::GetInstance();
    Scene* scene = SceneManager::GetInstance()->GetCurrentScene();

    POINT resolution = core->GetResolution();
    b2Vec2 half_screen = b2Vec2(resolution.x / 2.f, resolution.y / 2.f);
    
    b2Vec2 position = owner_->GetBody()->GetPosition();
    scene->SetScreenPosition(position - half_screen);
}
