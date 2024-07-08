#include "PlayerController.h"

#include "GameInstance.h"
#include "Windows.h"
#include "Actor/Box.h"

#include "Actor/Component/BoxColliderComponent.h"
#include "Actor/Component/RigidBodyComponent.h"
#include "Actor/Component/InputComponent.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Actor/Component/Animator/AnimationClip.h"
#include "Actor/Component/Animator/AnimatorComponent.h"
#include "box2d/b2_mouse_joint.h"
#include "Level/World.h"
#include "Misc/Debug.h"
#include "Physics/HitResult.h"
#include "Physics/Physics.h"
#include "Windows/DX/Shape.h"
#include "Windows/DX/Sprite.h"

PlayerController::PlayerController(const std::wstring& kName) : CharacterBase(kName)
{
    input_ = CreateComponent<InputComponent>(L"Input");
    input_->RegisterKey(VK_RIGHT);
    input_->RegisterKey(VK_LEFT);
    input_->RegisterKey('C');
    input_->RegisterKey('Z');
    input_->RegisterKey(MK_LBUTTON);
    
    sprite_ = MAKE_SHARED<Sprite>();
    CHECK_IF(sprite_->Load(L".\\Game_Data\\spritesheet.png"), L"Failed to load texture");

    sprite_->Split(15, 3, {.5f, .45f});

    sprite_renderer_->SetSprite(sprite_);

    int temp[] = {0, 1, 2, 3, 4, 5};
    animator_->MakeAnimationClip(L"Idle", temp, 6);
    animator_->clips_[L"Idle"]->SetRepeat(true);
    animator_->clips_[L"Idle"]->SetPlayBackSpeed(6.f);
    animator_->current_clip_ = animator_->clips_[L"Idle"];
    
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
    
    if (input_->IsKeyDown('Z'))
    {
        Box* box = new Box(L"Box");
        box->GetTransform()->SetRelativePosition(GetTransform()->GetWorldPosition());
        SpawnActor(box);
    }
}
