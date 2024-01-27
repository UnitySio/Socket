#include "Box.h"

#include "../../Engine/Graphics/Graphics.h"
#include "../../Engine/Input/InputManager.h"
#include "box2d/b2_body.h"
#include "../../Engine/Actor/Component/BoxComponent.h"
#include "../../Engine/Actor/Component/SpriteComponent.h"

Box::Box(b2World* world, const std::wstring& name) : Actor(world, name)
{
    GetBody()->SetType(b2_dynamicBody);
    // GetBody()->SetFixedRotation(true);
    GetBody()->SetTransform(b2Vec2(320.f, 0.f), 0.f);
    
    BoxComponent* box_component = CreateComponent<BoxComponent>(L"BoxComponent");
    box_component->SetBox(b2Vec2(64.f, 64.f));
    box_component->SetDensity(1.f);
    box_component->SetFriction(.3f);

    SpriteComponent* sprite_component = CreateComponent<SpriteComponent>(L"SpriteComponent");

    texture_ = Graphics::GetInstance()->LoadTexture(L".\\Box.png");
}
