#include "Box.h"

#include "Player.h"
#include "../../Engine/Input/InputManager.h"
#include "box2d/b2_body.h"
#include "../../Engine/Actor/Component/BoxComponent.h"
#include "../../Engine/Graphics/Graphics.h"
#include "../../Engine/Scene/Scene.h"
#include "../../Engine/Scene/SceneManager.h"

Box::Box(b2World* world, const std::wstring& name) : Actor(world, name)
{
    GetBody()->SetType(b2_dynamicBody);
    // GetBody()->SetFixedRotation(true);
    GetBody()->SetTransform(b2Vec2(320.f, 0.f), 0.f);
    
    BoxComponent* box_component = CreateComponent<BoxComponent>(L"BoxComponent");
    box_component->SetBox(b2Vec2(64.f, 64.f));
    box_component->SetDensity(1.f);
    box_component->SetFriction(.3f);

    texture_ = Graphics::GetInstance()->LoadTexture(L".\\Box.png");
}

void Box::Render()
{
    Actor::Render();

    b2Vec2 position = SceneManager::GetInstance()->GetCurrentScene()->GetRenderPosition(GetBody()->GetPosition());
    float angle = GetBody()->GetAngle();

    Graphics::GetInstance()->DrawTexture(texture_, position, b2Vec2(.25f, .25f), angle);
}
