#include "Player.h"

#include "../../Engine/Core.h"
#include "../../Engine/Graphics/Graphics.h"
#include "../../Engine/Input/InputManager.h"
#include "box2d/b2_body.h"
#include "box2d/b2_circle_shape.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"
#include "imgui/imgui.h"

Player::Player(b2World* world) : Actor(world)
{
    GetBody()->SetType(b2_dynamicBody);

    b2CircleShape circle;
    circle.m_radius = 16.f;

    b2FixtureDef fixture_def;
    fixture_def.shape = &circle;
    fixture_def.density = 1.f;
    fixture_def.friction = .3f;

    GetBody()->CreateFixture(&fixture_def);

    color_ = b2Color(1.f, 1.f, 1.f);
}

void Player::Begin()
{
}

void Player::Tick(float deltaTime)
{
    std::shared_ptr<InputManager> input = InputManager::GetInstance();

    if (!is_focused_)
    {
        const int h = input->IsKeyPressed(VK_RIGHT) - input->IsKeyPressed(VK_LEFT);
        GetBody()->SetLinearVelocity(b2Vec2(h * 10.f, GetBody()->GetLinearVelocity().y));

        if (input->IsKeyDown(VK_SPACE))
        {
            GetBody()->ApplyLinearImpulse(b2Vec2(0.f, -50000.f), GetBody()->GetWorldCenter(), true);
        }
    }

    if (ImGui::Begin(u8"정보"))
    {
        ImGui::Text(u8"Player 위치: (%.2f, %.2f)", GetBody()->GetPosition().x, GetBody()->GetPosition().y);
        ImGui::Text(u8"Player 각도: %.2f", GetBody()->GetAngle());
        ImGui::Text(u8"Player 속도: (%.2f, %.2f)", GetBody()->GetLinearVelocity().x, GetBody()->GetLinearVelocity().y);

        is_focused_ = ImGui::IsWindowFocused();
    }

    ImGui::End();
}

void Player::Render()
{
    b2Vec2 position = GetBody()->GetPosition();
    float angle = GetBody()->GetAngle();

    Graphics::GetInstance()->DrawBox(position, b2Vec2(32.f, 32.f), angle, color_);
}

void Player::OnCollisionBegin(Actor* other)
{
    if (strcmp(other->GetName(), "Box") == 0)
    {
        color_ = b2Color(1.f, 0.f, 0.f);
    }
}

void Player::OnCollisionEnd(Actor* other)
{
    if (strcmp(other->GetName(), "Box") == 0)
    {
        color_ = b2Color(1.f, 1.f, 1.f);
    }
}
