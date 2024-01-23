#include "Box.h"

#include "../../Engine/Graphics/Graphics.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"

Box::Box(b2World* world) : Actor(world)
{
    GetBody()->SetType(b2_dynamicBody);

    b2PolygonShape box;
    box.SetAsBox(32.f, 32.f);

    b2FixtureDef fixture_def;
    fixture_def.shape = &box;
    fixture_def.density = 1.f;
    fixture_def.friction = 0.3f;

    GetBody()->CreateFixture(&fixture_def);
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

    Graphics::GetInstance()->DrawFillRectangle(position, b2Vec2(64.f, 64.f), angle);
}
