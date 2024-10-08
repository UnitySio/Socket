#include "pch.h"
#include "Player.h"

#include "Actor/Camera.h"
#include "Actor/Component/Controller2DComponent.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Actor/Component/Animator/AnimationClip.h"
#include "Actor/Component/Animator/AnimatorComponent.h"
#include "Actor/ObjectPool/Bullet.h"
#include "Actor/ObjectPool/ObjectPool.h"
#include "Data/CSVReader.h"
#include "Data/StatInfo.h"
#include "Input/Keyboard.h"
#include "Level/World.h"
#include "Math/Math.h"
#include "Resource/ResourceManager.h"
#include "rttr/registration.h"
#include "rttr/detail/registration/registration_impl.h"
#include "State/PlayerJumpingState.h"
#include "State/PlayerStandingState.h"
#include "Windows/DX/Sprite.h"

Player::Player(const std::wstring& kName) :
    CharacterBase(kName),
    gravity_(0.f),
    jump_height_(2.f),
    time_to_jump_apex_(.4f),
    jump_velocity_(0.f),
    move_speed_(0.f),
    last_pressed_jump_time_(0.f)
{
    SetLayer(ActorLayer::kPlayer);
    
    GetTransform()->SetPosition({5.f, 5.f});
    
    if (ResourceManager::Get()->Load<Sprite>(L"PlayerSheet", L".\\Game_Data\\PlayerSheet.png"))
    {
        sprite_ = ResourceManager::Get()->GetResource<Sprite>(L"PlayerSheet");
        sprite_->Split(8, 7, Sprite::kCenter);
        
        sprite_renderer_->SetSprite(sprite_);
    }
    
    {
        int idle_indices[] = {0, 1, 2, 3, 4, 5, 6, 7};
        std::shared_ptr<AnimationClip> idle_clip = animator_->AddClip(L"Idle", idle_indices, 8);
        idle_clip->SetRepeat(true);
        idle_clip->SetFrameRate(6.f);

        int walk_indices[] = {8, 9, 10, 11, 12, 13, 14, 15};
        std::shared_ptr<AnimationClip> walk_clip = animator_->AddClip(L"Walk", walk_indices, 8);
        walk_clip->SetRepeat(true);
        walk_clip->SetFrameRate(10.f);

        int run_indices[] = {24, 25, 26, 27, 28, 29};
        std::shared_ptr<AnimationClip> run_clip = animator_->AddClip(L"Run", run_indices, 6);
        run_clip->SetRepeat(true);
        run_clip->SetFrameRate(10.f);

        int jump_indices[] = {32, 33, 34};
        std::shared_ptr<AnimationClip> jump_clip = animator_->AddClip(L"Jump", jump_indices, 3);
        jump_clip->SetRepeat(false);
        jump_clip->SetFrameRate(10.f);
    }

    states_[0] = std::make_unique<PlayerStandingState>(this, state_machine_.get());
    states_[1] = std::make_unique<PlayerJumpingState>(this, state_machine_.get());

    object_pool_ = AddComponent<ObjectPool>(L"ObjectPool");
    object_pool_->SetPooledObjectClass(Bullet::StaticClass());
}

void Player::BeginPlay()
{
    CharacterBase::BeginPlay();

    Camera::Get()->SetTarget(this);

    state_machine_->ChangeState(states_[0].get());

    gravity_ = -(2 * jump_height_) / std::pow(time_to_jump_apex_, 2);
    jump_velocity_ = Math::Abs(gravity_) * time_to_jump_apex_;

    // 직렬화 테스트
    std::vector<StatInfo> stats;
    CSVReader::Get()->Load(L".\\Game_Data\\StatInfo.csv", stats);
}

void Player::Tick(float delta_time)
{
    CharacterBase::Tick(delta_time);

    HandleTime(delta_time);

    Keyboard* keyboard = Keyboard::Get();
    if (keyboard->GetKeyDown('C'))
    {
        last_pressed_jump_time_ = .1f;
    }

    if (keyboard->GetKeyDown('R'))
    {
        World::Get()->OpenLevel(LevelType::kDefault);
    }

    if (keyboard->GetKeyDown('F'))
    {
        PooledObject* poolable_object = object_pool_->SpawnPooledObject();
        if (poolable_object)
        {
            poolable_object->GetTransform()->SetPosition(GetTransform()->GetPosition());
        }
    }
}

void Player::HandleTime(float delta_time)
{
    if (last_pressed_jump_time_ > 0.f)
    {
        last_pressed_jump_time_ = Math::Max(last_pressed_jump_time_ - delta_time, 0.f);
    }
}

RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<Player>("Player")
        .constructor<const std::wstring&>()
        (
            policy::ctor::as_std_shared_ptr
        );
}
