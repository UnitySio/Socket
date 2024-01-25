#include "Box.h"

#include "../../Engine/Actor/Camera.h"
#include "../../Engine/Graphics/Graphics.h"
#include "../../Engine/Input/InputManager.h"
#include "box2d/b2_body.h"
#include "../../Engine/Actor/Component/BoxComponent.h"
#include "../../Engine/Actor/Component/SpriteComponent.h"

class BoxComponent;

Box::Box(b2World* world) : Actor(world)
{
    GetBody()->SetType(b2_dynamicBody);
    GetBody()->SetTransform(b2Vec2(320.f, 0.f), 0.f);
    
    BoxComponent* box_component = AddComponent<BoxComponent>();
    box_component->SetBox(b2Vec2(64.f, 64.f));
    box_component->SetDensity(1.f);
    box_component->SetFriction(.3f);

    SpriteComponent* sprite_component = AddComponent<SpriteComponent>();

    texture_ = Graphics::GetInstance()->LoadTexture(L".\\box.png");
}

void Box::Render()
{
    b2Vec2 position = Camera::GetInstance()->GetRenderPosition(GetBody()->GetPosition());
    float angle = GetBody()->GetAngle();

    Graphics::GetInstance()->DrawTexture(texture_, position, b2Vec2(.25f, .25f), angle);
}
