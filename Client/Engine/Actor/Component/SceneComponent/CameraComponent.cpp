#include "CameraComponent.h"

#include "../../Actor.h"
#include "../../../Core.h"
#include "../../../Level/Level.h"
#include "../../../Level/LevelManager.h"
#include "box2d/b2_body.h"

CameraComponent::CameraComponent(Actor* owner, const std::wstring& kName) : SceneComponent(owner, kName)
{
}

void CameraComponent::TickComponent(float delta_time)
{
    SceneComponent::TickComponent(delta_time);
    
    Core* core = Core::GetInstance();
    Level* level = LevelManager::GetInstance()->GetLevel();

    POINT resolution = core->GetResolution();
    b2Vec2 half_screen = b2Vec2(resolution.x / 2.f, resolution.y / 2.f);
    
    level->SetScreenPosition(GetWorldLocation() - half_screen);
}
