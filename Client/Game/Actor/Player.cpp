#include "Player.h"

#include "Box.h"
#include "../../Engine/Core.h"
#include "../../Engine/Actor/Component/BoxComponent.h"
#include "../../Engine/Actor/Component/CameraComponent.h"
#include "../../Engine/Actor/Component/SceneComponent.h"
#include "../../Engine/Graphics/Graphics.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Time/Time.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_world.h"
#include "imgui/imgui.h"

Player::Player(b2World* world, const std::wstring& name) : Actor(world, name), is_ground_(false)
{
    // GetBody()->SetType(b2_dynamicBody);
    // // GetBody()->SetFixedRotation(true);
    // GetBody()->SetTransform(b2Vec2(0.f, 0.f), 0.f);

    // BoxComponent* box_component = CreateComponent<BoxComponent>(L"BoxComponent");
    // box_component->SetBox(b2Vec2(32.f, 32.f));
    // box_component->SetDensity(1.f);
    // box_component->SetFriction(.3f);

    // CameraComponent* camera_component = CreateComponent<CameraComponent>(L"CameraComponent");
    
    GetWorld()->DestroyBody(GetBody());

    root_component_ = CreateComponent<SceneComponent>(L"RootComponent");

    root_component_->GetBody()->SetType(b2_dynamicBody);

    b2PolygonShape box;
    box.SetAsBox(16.f, 16.f);

    b2FixtureDef fixture_def;
    fixture_def.shape = &box;
    fixture_def.density = 1.f;
    fixture_def.friction = .3f;

    root_component_->GetBody()->CreateFixture(&fixture_def);
    
    temp_1 = CreateComponent<SceneComponent>(L"Temp1");
    temp_1->SetupAttachment(root_component_);
    temp_1->SetLocation(b2Vec2(0.f, 50.f));
    
    temp_2 = CreateComponent<SceneComponent>(L"Temp2");
    temp_2->SetupAttachment(temp_1);
    temp_2->SetLocation(b2Vec2(0.f, 50.f));

    temp_3 = CreateComponent<SceneComponent>(L"Temp3");
    temp_3->SetupAttachment(temp_2);
    temp_3->SetLocation(b2Vec2(0.f, 50.f));
}

void Player::Tick(float delta_time)
{
    Actor::Tick(delta_time);
    
    InputManager* input = InputManager::GetInstance();

    const int h = input->IsKeyPressed(VK_RIGHT) - input->IsKeyPressed(VK_LEFT);
    root_component_->GetBody()->SetLinearVelocity(b2Vec2(h * 250.f, root_component_->GetBody()->GetLinearVelocity().y));

    if (input->IsKeyDown(VK_SPACE))
    {
        root_component_->GetBody()->ApplyLinearImpulse(b2Vec2(0.f, -500000.f), GetBody()->GetWorldCenter(), true);
    }

    if (input->IsKeyDown(VK_DOWN))
    {
        Box* box = new Box(GetWorld(), L"Box");
        SpawnActor(box);

        // b2Vec2 location = temp_2->GetLocation();
        // location.y -= 100.f * delta_time;
        // temp_2->SetLocation(location);
    }

    if (input->IsKeyPressed(VK_UP))
    {
        b2Vec2 location = root_component_->GetLocation();
        location.y += 100.f * delta_time;
        root_component_->SetLocation(location);
    }

    float angle = root_component_->GetRotation();
    root_component_->SetRotation(angle + .5f * delta_time);
    
    float angle2 = temp_1->GetRotation();
    temp_1->SetRotation(angle2 + 1.f * delta_time);
    
    float angle3 = temp_2->GetRotation();
    temp_2->SetRotation(angle3 + 1.5f * delta_time);

    // body 개수
    ImGui::Text("Body Count: %d", GetWorld()->GetBodyCount());
}
