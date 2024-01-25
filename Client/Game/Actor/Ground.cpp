#include "Ground.h"

#include "../../Engine/Actor/Camera.h"
#include "../../Engine/Graphics/Graphics.h"
#include "box2d/b2_body.h"
#include "box2d/b2_polygon_shape.h"

Ground::Ground(b2World* world) : Actor(world)
{
    GetBody()->SetTransform(b2Vec2(320.f, 464.f), 0.f);

    b2PolygonShape box;
    box.SetAsBox(320.f, 16.f);

    GetBody()->CreateFixture(&box, 0.f);
}

void Ground::Render()
{
    b2Vec2 position = Camera::GetInstance()->GetRenderPosition(GetBody()->GetPosition());
    float angle = GetBody()->GetAngle();

    Graphics::GetInstance()->DrawBox(position, b2Vec2(640.f, 32.f), angle);
}
