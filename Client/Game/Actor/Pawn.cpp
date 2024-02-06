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
    root_component_ = box_;
    
    box_->SetBoxExtent(b2Vec2(32.f, 32.f));
    box_->SetRelativeLocation(b2Vec2(0.f, -100.f));

    root_component_->GetBody()->SetType(b2_dynamicBody);
    root_component_->GetBody()->GetFixtureList()->SetDensity(1.f);
    root_component_->GetBody()->GetFixtureList()->SetFriction(0.3f);
    root_component_->GetBody()->ResetMassData();

    box2_ = CreateComponent<BoxComponent>(L"Box2");
    box2_->SetupAttachment(root_component_);
    
    box2_->SetBoxExtent(b2Vec2(32.f, 32.f));
    box2_->SetRelativeLocation(b2Vec2(0.f, -100.f));
    box2_->SetRelativeRotation(45.f);

    BoxComponent* box3 = CreateComponent<BoxComponent>(L"Box3");
    box3->SetupAttachment(box2_);

    box3->SetBoxExtent(b2Vec2(32.f, 32.f));
    box3->SetRelativeLocation(b2Vec2(0.f, -100.f));

    camera_view_ = CreateComponent<CameraComponent>(L"Camera");
    camera_view_->SetupAttachment(root_component_);
}

void Pawn::Tick(float delta_time)
{
    Actor::Tick(delta_time);

    InputManager* input = InputManager::GetInstance();
    float h = input->IsKeyPressed(VK_RIGHT) - input->IsKeyPressed(VK_LEFT);

    root_component_->GetBody()->SetLinearVelocity(b2Vec2(h * 100.f, root_component_->GetBody()->GetLinearVelocity().y));

    if (input->IsKeyDown(VK_SPACE))
    {
        root_component_->GetBody()->ApplyLinearImpulse(b2Vec2(0.f, -500000.f), root_component_->GetBody()->GetWorldCenter(), true);
        // Destroy(this);
    }

    static float angle = 0.f;
    angle += 10.f * delta_time;
    box2_->SetRelativeRotation(angle);
}
