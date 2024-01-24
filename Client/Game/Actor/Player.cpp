#include "Player.h"

#include "Box.h"
#include "../../Engine/Core.h"
#include "../../Engine/Graphics/Graphics.h"
#include "../../Engine/Input/InputManager.h"
#include "box2d/b2_body.h"
#include "box2d/b2_circle_shape.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_world.h"
#include "imgui/imgui.h"

Player::Player(b2World* world) : Actor(world)
{
    GetBody()->SetType(b2_dynamicBody);

    b2PolygonShape box;
    box.SetAsBox(16.f, 16.f);

    b2FixtureDef fixture_def;
    fixture_def.shape = &box;
    fixture_def.density = 1.f;
    fixture_def.friction = .3f;

    GetBody()->CreateFixture(&fixture_def);

    color_ = b2Color(1.f, 1.f, 1.f);
}

float Player::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
{
    b2Body* body = fixture->GetBody();
    Actor* actor = reinterpret_cast<Actor*>(body->GetUserData().pointer);
    if (actor)
    {
        is_ground_ = true;
        return fraction;
    }
    
    return 1;
}

void Player::Begin()
{
}

void Player::Tick(float deltaTime)
{
    is_ground_ = false;
    GetBody()->GetWorld()->RayCast(this, GetBody()->GetPosition(), GetBody()->GetPosition() + b2Vec2(0.f, 32.f));
    
    std::shared_ptr<InputManager> input = InputManager::GetInstance();

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
