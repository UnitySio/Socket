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
    
    sprite_ = MAKE_SHARED<Sprite>();
    CHECK_IF(sprite_->Load(L".\\Game_Data\\spritesheet.png"), L"Failed to load texture");

    sprite_->Split(15, 3, {.5f, .45f});
    
    const std::vector<SpriteFrame>& frames = sprite_->GetFrames();

    const float width = sprite_->GetWidth() * frames[0].uv_scale.x / sprite_->GetPPU();
    const float height = sprite_->GetHeight() * frames[0].uv_scale.y / sprite_->GetPPU();
    const float pivot_x = width * frames[0].pivot.x;
    const float pivot_y = height * frames[0].pivot.y;

    shape_ = MAKE_SHARED<Shape>();
    shape_->SetVertices(sprite_->GetVertices());
    shape_->SetIndices(sprite_->GetIndices());
    shape_->SetTexture(sprite_);
    shape_->SetPosition(GetTransform()->GetWorldPosition());
    shape_->SetRotation(GetTransform()->GetWorldRotationZ());
    shape_->SetScale({width, height});
    shape_->SetUVOffset(frames[0].uv_offset);
    shape_->SetUVScale(frames[0].uv_scale);
    shape_->SetPivot({pivot_x, pivot_y});
    shape_->SetZOrder(1);
    
}

void PlayerController::BeginPlay()
{
    CharacterBase::BeginPlay();

    TimerManager::Get()->SetTimer(this, &PlayerController::OnFire, 1.f, true);
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

    Math::Vector2 screen_position = Renderer::Get()->WorldToScreen(GetTransform()->GetWorldPosition());
}

void PlayerController::Render(float alpha)
{
    CharacterBase::Render(alpha);
    
    shape_->SetPosition(GetTransform()->GetWorldPosition());
    shape_->SetRotation(GetTransform()->GetWorldRotationZ());

    World::Get()->AddShape(shape_);
}

void PlayerController::OnFire()
{
    Math::Vector2 world_position = Renderer::Get()->ScreenToWorld({320.f, 10.f});
    
    Box* box = new Box(L"Box");
    box->GetTransform()->SetRelativePosition(world_position);
    SpawnActor(box);
}
