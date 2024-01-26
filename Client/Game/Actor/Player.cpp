#include "Player.h"

#include "Box.h"
#include "../../Engine/Core.h"
#include "../../Engine/Actor/Camera.h"
#include "../../Engine/Actor/Component/BoxComponent.h"
#include "../../Engine/Graphics/Graphics.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Physics/HitResult.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_world.h"
#include "imgui/imgui.h"

Player::Player(b2World* world) : Actor(world)
{
    GetBody()->SetType(b2_dynamicBody);

    BoxComponent* box_component = AddComponent<BoxComponent>();
    box_component->SetBox(b2Vec2(32.f, 32.f));
    box_component->SetDensity(1.f);
    box_component->SetFriction(.3f);
}

void Player::Begin()
{
    Camera::GetInstance()->SetTarget(this);
}

void Player::Tick(float deltaTime)
{
    is_ground_ = false;
    HitResult hit_result;
    GetWorld()->RayCast(&hit_result, GetBody()->GetPosition(), GetBody()->GetPosition() + b2Vec2(0.f, 32.f));
    for (Actor* actor : hit_result.GetActors())
    {
        if (strcmp(actor->GetName(), "Box"))
        {
            is_ground_ = true;
            break;
        }
    }
    
    InputManager* input = InputManager::GetInstance();

    const int h = input->IsKeyPressed(VK_RIGHT) - input->IsKeyPressed(VK_LEFT);
    GetBody()->SetLinearVelocity(b2Vec2(h * 10.f, GetBody()->GetLinearVelocity().y));

    if (input->IsKeyDown(VK_SPACE) && is_ground_)
    {
        GetBody()->ApplyLinearImpulse(b2Vec2(0.f, -50000.f), GetBody()->GetWorldCenter(), true);
    }

    if (input->IsKeyDown(VK_DOWN))
    {
        Box* box = new Box(GetBody()->GetWorld());
        box->SetName("Box");

        SpawnActor(box);
    }

    if (input->IsKeyDown(MK_LBUTTON))
    {
        b2Vec2 mouse_position = Camera::GetInstance()->GetScreenToWorldPosition(input->GetMousePosition());
        GetBody()->SetTransform(mouse_position, GetBody()->GetAngle());
    }

    if (ImGui::Begin(u8"DEBUG"))
    {
        float angle = GetBody()->GetAngle() * 180.f / b2_pi;

        ImGui::Text(u8"Mouse Position: (%.2f, %.2f)", input->GetMousePosition().x, input->GetMousePosition().y);
        ImGui::Text(u8"Mouse World Position: (%.2f, %.2f)", Camera::GetInstance()->GetScreenToWorldPosition(input->GetMousePosition()).x, Camera::GetInstance()->GetScreenToWorldPosition(input->GetMousePosition()).y);
        ImGui::Text(u8"Position: (%.2f, %.2f)", GetBody()->GetPosition().x, GetBody()->GetPosition().y);
        ImGui::Text(u8"Angle: %.2f", angle);
        ImGui::Text(u8"Velocity: (%.2f, %.2f)", GetBody()->GetLinearVelocity().x, GetBody()->GetLinearVelocity().y);
        ImGui::Text(u8"Screen Position: (%.2f, %.2f)", Camera::GetInstance()->GetScreenPosition().x, Camera::GetInstance()->GetScreenPosition().y);
    }

    ImGui::End();
}

void Player::Render()
{
    b2Vec2 position = Camera::GetInstance()->GetRenderPosition(GetBody()->GetPosition());
    float angle = GetBody()->GetAngle();

    // Graphics::GetInstance()->DrawBox(position, b2Vec2(32.f, 32.f), angle, b2Color(1.f, 1.f, 1.f, 1.f));

    b2Vec2 vertices[4];
    vertices[0] = position + b2Mul(b2Rot(angle), b2Vec2(-16.f, -16.f));
    vertices[1] = position + b2Mul(b2Rot(angle), b2Vec2(16.f, -16.f));
    vertices[2] = position + b2Mul(b2Rot(angle), b2Vec2(16.f, 16.f));
    vertices[3] = position + b2Mul(b2Rot(angle), b2Vec2(-16.f, 16.f));

    Graphics::GetInstance()->DrawSolidPolygon(vertices, 4, b2Color(1.f, 1.f, 1.f, 1.f));
}
