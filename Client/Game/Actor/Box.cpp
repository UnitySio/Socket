﻿#include "Box.h"

#include "../../Engine/Graphics/Graphics.h"
#include "../../Engine/Input/InputManager.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"

Box::Box(b2World* world) : Actor(world)
{
    GetBody()->SetType(b2_dynamicBody);
    GetBody()->SetTransform(b2Vec2(320.f, 0.f), 0.f);

    b2PolygonShape box;
    box.SetAsBox(32.f, 32.f);

    b2FixtureDef fixture_def;
    fixture_def.shape = &box;
    fixture_def.density = 1.f;
    fixture_def.friction = .3f;

    GetBody()->CreateFixture(&fixture_def);

    texture_ = Graphics::GetInstance()->LoadTexture(L".\\box.png");
}

void Box::Begin()
{
}

void Box::Tick(float deltaTime)
{
}

void Box::Render()
{
    b2Vec2 position = GetBody()->GetPosition();
    float angle = GetBody()->GetAngle();

    Graphics::GetInstance()->DrawTexture(texture_, position, b2Vec2(.25f, .25f), angle);
}

void Box::OnCollisionBegin(Actor* other)
{
    if (strcmp(other->GetName(), "Player") == 0)
    {
        // Destroy();
    }
}