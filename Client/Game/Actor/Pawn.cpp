#include "Pawn.h"

#include "../../Engine/Core.h"
#include "../../Engine/Actor/Component/Scenecomponent/ShapeComponent/BoxComponent.h"
#include "../../Engine/Actor/Component/Scenecomponent/ShapeComponent/CircleComponent.h"
#include "../../Engine/Actor/Component/Scenecomponent/SpriteComponent.h"
#include "../../Engine/Actor/Component/Scenecomponent/CameraComponent.h"
#include "../../Engine/Graphics/Graphics.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Level/Level.h"
#include "../../Engine/Level/LevelManager.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"

Pawn::Pawn(b2World* world, const std::wstring& kName) :
    Actor(world, kName),
    bitmap_(nullptr)
{
    box_ = CreateComponent<BoxComponent>(L"Box");
    box_->SetBoxExtent(b2Vec2(32.f, 32.f));
    box_->SetRelativeLocation(b2Vec2(0.f, -96.f));

    box_->GetBody()->SetType(b2_dynamicBody);
    box_->GetBody()->GetFixtureList()->SetDensity(1.f);
    box_->GetBody()->GetFixtureList()->SetFriction(0.3f);
    box_->GetBody()->ResetMassData();

    root_component_ = box_;

    circle_ = CreateComponent<CircleComponent>(L"Circle");
    circle_->SetCircleRadius(32.f);
    circle_->SetRelativeLocation(b2Vec2(0.f, -96.f));

    circle_->GetBody()->SetType(b2_dynamicBody);
    circle_->GetBody()->GetFixtureList()->SetDensity(1.f);
    circle_->GetBody()->GetFixtureList()->SetFriction(0.3f);
    circle_->GetBody()->ResetMassData();
    
    circle_->SetupAttachment(root_component_);

    sprite_ = CreateComponent<SpriteComponent>(L"Sprite");
    sprite_->SetupAttachment(root_component_);

    camera_view_ = CreateComponent<CameraComponent>(L"Camera");
    camera_view_->SetupAttachment(root_component_);

    bitmap_ = Graphics::GetInstance()->LoadTexture(L"box.png");
    assert(bitmap_);
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

void Pawn::Render()
{
    Actor::Render();

    Level* level = LevelManager::GetInstance()->GetLevel();
    b2Vec2 render_position = level->GetRenderPosition(box_->GetWorldLocation());
    Graphics::GetInstance()->DrawTexture(bitmap_, render_position, b2Vec2(.125f, .125f), box_->GetWorldRotation());
}
