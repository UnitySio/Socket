#include "PlayerController.h"
#include "Windows.h"
#include "Actor/Box.h"

#include "Actor/Component/BoxColliderComponent.h"
#include "Actor/Component/RigidBodyComponent.h"
#include "Actor/Component/InputComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Level/World.h"
#include "Misc/Debug.h"
#include "Windows/DX/Shape.h"
#include "Windows/DX/Sprite.h"

PlayerController::PlayerController(const std::wstring& kName) : CharacterBase(kName)
{
    input_ = CreateComponent<InputComponent>(L"Input");
    input_->RegisterKey(VK_RIGHT);
    input_->RegisterKey(VK_LEFT);
    input_->RegisterKey('C');
    input_->RegisterKey('Z');
    
    sprite_ = MAKE_SHARED<Sprite>();
    CHECK_IF(sprite_->Load(L".\\Game_Data\\spritesheet.png"), L"Failed to load texture");

    sprite_->Split(15, 3, {.5f, .45f});
    
}

void PlayerController::PhysicsTick(float delta_time)
{
    CharacterBase::PhysicsTick(delta_time);
    
    float h = input_->IsKeyPressed(VK_RIGHT) - input_->IsKeyPressed(VK_LEFT);
    
    rigid_body_->SetVelocity({h * 6.f, rigid_body_->GetVelocity().y});
}

void PlayerController::Tick(float delta_time)
{
    CharacterBase::Tick(delta_time);
    
    if (input_->IsKeyDown('C'))
    {
        rigid_body_->SetVelocity(Math::Vector2::Zero());
        rigid_body_->AddForce(Math::Vector2::Up() * 5.f, ForceMode::kImpulse);
    }

    if (input_->IsKeyPressed('Z'))
    {
        Box* box = new Box(L"Box");
        box->GetTransform()->SetRelativePosition(GetTransform()->GetWorldPosition());
        SpawnActor(box);
    }
}

void PlayerController::Render(float alpha)
{
    CharacterBase::Render(alpha);
    
    const std::vector<SpriteFrame>& frames = sprite_->GetFrames();

    const float width = sprite_->GetWidth() * frames[0].uv_scale.x / sprite_->GetPPU();
    const float height = sprite_->GetHeight() * frames[0].uv_scale.y / sprite_->GetPPU();
    const float pivot_x = width * frames[0].pivot.x;
    const float pivot_y = height * frames[0].pivot.y;

    SHARED_PTR<Shape> shape = MAKE_SHARED<Shape>();
    shape->SetVertices(sprite_->GetVertices());
    shape->SetIndices(sprite_->GetIndices());
    shape->SetTexture(sprite_);
    shape->SetPosition(GetTransform()->GetWorldPosition());
    shape->SetRotation(GetTransform()->GetWorldRotationZ());
    shape->SetScale({width, height});
    shape->SetUVOffset(frames[0].uv_offset);
    shape->SetUVScale(frames[0].uv_scale);
    shape->SetPivot({pivot_x, pivot_y});
    shape->SetZOrder(1);

    World::Get()->AddShape(shape);
}
