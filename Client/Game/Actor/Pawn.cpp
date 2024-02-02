#include "Pawn.h"

#include "../../Engine/Core.h"
#include "../../Engine/Actor/Component/Scenecomponent/ShapeComponent/BoxComponent.h"
#include "../../Engine/Actor/Component/Scenecomponent/CameraComponent.h"
#include "../../Engine/Input/InputManager.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"

Pawn::Pawn(b2World* world, const std::wstring& kName) :
    Actor(world, kName)
{
    box_ = CreateComponent<BoxComponent>(L"Box");
    box_->SetBoxExtent(b2Vec2(32.f, 32.f));

    box_->GetBody()->SetType(b2_dynamicBody);
    box_->GetBody()->GetFixtureList()->SetDensity(1.f);
    box_->GetBody()->GetFixtureList()->SetFriction(0.3f);
    box_->GetBody()->ResetMassData();

    root_component_ = box_;

    camera_view_ = CreateComponent<CameraComponent>(L"Camera");
    camera_view_->SetupAttachment(root_component_);

    temp_box_ = CreateComponent<BoxComponent>(L"TempBox");
    temp_box_->SetBoxExtent(b2Vec2(32.f, 32.f));
    temp_box_->SetLocation(b2Vec2(0.f, -64.f));

    temp_box_->GetBody()->SetType(b2_dynamicBody);
    temp_box_->GetBody()->GetFixtureList()->SetDensity(1.f);
    temp_box_->GetBody()->GetFixtureList()->SetFriction(0.3f);
    temp_box_->GetBody()->ResetMassData();

    temp_box_->SetupAttachment(root_component_);

    temp_box2_ = CreateComponent<BoxComponent>(L"TempBox2");
    temp_box2_->SetBoxExtent(b2Vec2(32.f, 32.f));
    temp_box2_->SetLocation(b2Vec2(0.f, -64.f));

    temp_box2_->SetupAttachment(temp_box_);

    temp_ = CreateComponent<SceneComponent>(L"Temp");
    temp_->SetLocation(b2Vec2(0.f, -128.f));

    temp_->SetupAttachment(temp_box_);
}

void Pawn::Tick(float delta_time)
{
    Actor::Tick(delta_time);

    InputManager* input = InputManager::GetInstance();
    float h = input->IsKeyPressed(VK_RIGHT) - input->IsKeyPressed(VK_LEFT);

    box_->GetBody()->SetLinearVelocity(b2Vec2(h * 100.f, box_->GetBody()->GetLinearVelocity().y));

    if (input->IsKeyDown(VK_SPACE))
    {
        box_->GetBody()->ApplyLinearImpulse(b2Vec2(0.f, -500000.f), box_->GetBody()->GetWorldCenter(), true);
    }
}
