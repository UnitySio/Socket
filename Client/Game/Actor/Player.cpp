#include "Player.h"

#include "../../Engine/Core.h"
#include "../../Engine/Graphics/Graphics.h"
#include "../../Engine/Input/InputManager.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"

Player::Player(b2World* world) : Actor(world)
{
    GetBody()->SetType(b2_dynamicBody);

    b2PolygonShape box;
    box.SetAsBox(16.f, 16.f);

    b2FixtureDef fixture_def;
    fixture_def.shape = &box;
    fixture_def.density = 1.f;
    fixture_def.friction = 0.3f;

    GetBody()->CreateFixture(&fixture_def);
}

void Player::Begin()
{
}

void Player::Tick(float deltaTime)
{
    std::shared_ptr<InputManager> input = InputManager::GetInstance();

    const int h = input->IsKeyPressed(VK_RIGHT) - input->IsKeyPressed(VK_LEFT);
    GetBody()->SetLinearVelocity(b2Vec2(h * 100.f, GetBody()->GetLinearVelocity().y));

    if (input->IsKeyDown(VK_SPACE))
    {
        GetBody()->ApplyLinearImpulse(b2Vec2(0.f, -500000.f), GetBody()->GetWorldCenter(), true);
    }
}

void Player::Render()
{
    b2Vec2 position = GetBody()->GetPosition();
    float angle = GetBody()->GetAngle();

    Graphics::GetInstance()->DrawFillRectangle(position, b2Vec2(32.f, 32.f), angle);
}
