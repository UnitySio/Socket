#include "CameraComponent.h"

#include "../../Actor.h"
#include "../../../Core.h"
#include "../../../Level/Level.h"
#include "../../../Level/World.h"
#include "box2d/b2_body.h"

CameraComponent::CameraComponent(Actor* owner, const std::wstring& kName) : SceneComponent(owner, kName)
{
}

void CameraComponent::TickComponent(float delta_time)
{
    SceneComponent::TickComponent(delta_time);
    
    Core* core = Core::Get();
    Level* level = World::Get()->GetLevel();

    POINT resolution = core->GetResolution();
    Vector half_screen = {resolution.x / 2.f, resolution.y / 2.f};
    
    level->SetScreenPosition(GetWorldLocation() - half_screen);
}
