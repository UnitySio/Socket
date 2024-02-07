#include "Pawn.h"

#include "../../Engine/Core.h"
#include "../../Engine/Actor/Component/Scenecomponent/ShapeComponent/BoxComponent.h"
#include "../../Engine/Actor/Component/Scenecomponent/SpriteComponent.h"
#include "../../Engine/Actor/Component/Scenecomponent/CameraComponent.h"
#include "../../Engine/Actor/Component/SceneComponent/ShapeComponent/CircleComponent.h"
#include "../../Engine/Graphics/Graphics.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Level/Level.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "imgui/imgui.h"

Pawn::Pawn(b2World* world, const std::wstring& kName) :
    Actor(world, kName)
{
    box_ = CreateComponent<BoxComponent>(L"Box");
    root_component_ = box_;
    
    box_->SetBoxExtent(b2Vec2(16.f, 16.f));
    box_->SetRelativeLocation(b2Vec2(0.f, -100.f));

    root_component_->GetBody()->SetType(b2_dynamicBody);
    root_component_->GetBody()->GetFixtureList()->SetDensity(1.f);
    root_component_->GetBody()->GetFixtureList()->SetFriction(0.3f);
    root_component_->GetBody()->ResetMassData();

    box2_ = CreateComponent<BoxComponent>(L"Box2");
    box2_->SetupAttachment(root_component_);
    
    box2_->SetBoxExtent(b2Vec2(16.f, 16.f));
    box2_->SetRelativeLocation(b2Vec2(0.f, -100.f));

    box3_ = CreateComponent<BoxComponent>(L"Box3");
    box3_->SetupAttachment(box2_);

    box3_->SetBoxExtent(b2Vec2(16.f, 16.f));
    box3_->SetRelativeLocation(b2Vec2(0.f, -100.f));

    BoxComponent* box4 = CreateComponent<BoxComponent>(L"Box4");
    box4->SetupAttachment(box3_);

    box4->SetBoxExtent(b2Vec2(16.f, 16.f));
    box4->SetRelativeLocation(b2Vec2(0.f, -100.f));

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

    float angle = box2_->GetRelativeRotation() * 180.f / b2_pi;
    angle += 50.f * delta_time;
    box2_->SetRelativeRotation(angle);

    float angle2 = box3_->GetRelativeRotation() * 180.f / b2_pi;
    angle2 += 100.f * delta_time;
    box3_->SetRelativeRotation(angle2);
}
