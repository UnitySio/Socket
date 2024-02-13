#include "Pawn.h"

#include "../../Engine/Core.h"
#include "../../Engine/Actor/Component/Scenecomponent/ShapeComponent/BoxComponent.h"
#include "../../Engine/Actor/Component/Scenecomponent/SpriteComponent.h"
#include "../../Engine/Actor/Component/Scenecomponent/CameraComponent.h"
#include "../../Engine/Graphics/Graphics.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Level/Level.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"

Pawn::Pawn(b2World* world, const std::wstring& kName) :
    Actor(world, kName)
{
    box_ = CreateComponent<BoxComponent>(L"Box");
    SetRootComponent(box_);
    
    box_->SetBoxExtent(b2Vec2(16.f, 16.f));

    GetBody()->SetType(b2_dynamicBody);
    GetBody()->GetFixtureList()->SetDensity(1.f);
    GetBody()->GetFixtureList()->SetFriction(0.3f);
    GetBody()->ResetMassData();
    
    SetActorLocation(b2Vec2(0.f, -100.f));

    camera_view_ = CreateComponent<CameraComponent>(L"Camera");
    camera_view_->SetupAttachment(GetRootComponent());
}

void Pawn::Tick(float delta_time)
{
    Actor::Tick(delta_time);

    InputManager* input = InputManager::GetInstance();
    float h = input->IsKeyPressed(VK_RIGHT) - input->IsKeyPressed(VK_LEFT);

    GetBody()->SetLinearVelocity(b2Vec2(h * 100.f, GetBody()->GetLinearVelocity().y));

    if (input->IsKeyDown(VK_SPACE))
    {
        GetBody()->ApplyLinearImpulse(b2Vec2(0.f, -500000.f), GetBody()->GetWorldCenter(), true);
        // Destroy(this);
    }
}
