#include "Player.h"

#include "Box.h"
#include "../../Engine/Core.h"
#include "../../Engine/Actor/Camera.h"
#include "../../Engine/Actor/Component/BoxComponent.h"
#include "../../Engine/Graphics/Graphics.h"
#include "../../Engine/Input/InputManager.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "imgui/imgui.h"

Player::Player(b2World* world) : Actor(world), is_ground_(false)
{
    GetBody()->SetType(b2_dynamicBody);
    // GetBody()->SetFixedRotation(true);
    GetBody()->SetTransform(b2Vec2(320.f, 0.f), 0.f);

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
    InputManager* input = InputManager::GetInstance();

    const int h = input->IsKeyPressed(VK_RIGHT) - input->IsKeyPressed(VK_LEFT);
    GetBody()->SetLinearVelocity(b2Vec2(h * 250.f, GetBody()->GetLinearVelocity().y));

    if (input->IsKeyDown(VK_SPACE))
    {
        GetBody()->ApplyLinearImpulse(b2Vec2(0.f, -500000.f), GetBody()->GetWorldCenter(), true);
    }

    if (input->IsKeyDown(VK_DOWN))
    {
        Box* box = new Box(GetBody()->GetWorld());
        box->SetName(L"Box");

        SpawnActor(box);
    }
}

void Player::Render()
{
    b2Vec2 position = Camera::GetInstance()->GetRenderPosition(GetBody()->GetPosition());
    float angle = GetBody()->GetAngle();

    Graphics::GetInstance()->DrawSolidBox(position, b2Vec2(32.f, 32.f), angle, b2Color(1.f, 1.f, 1.f, 1.f));
}
