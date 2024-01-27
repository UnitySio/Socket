#include "Ground.h"

#include "../../Engine/Actor/Component/BoxComponent.h"
#include "../../Engine/Graphics/Graphics.h"
#include "box2d/b2_body.h"

Ground::Ground(b2World* world, const std::wstring& name) : Actor(world, name)
{
    GetBody()->SetTransform(b2Vec2(320.f, 464.f), 0.f);

    BoxComponent* box_component = CreateComponent<BoxComponent>(L"BoxComponent");
    box_component->SetBox(b2Vec2(640.f, 32.f));
}
