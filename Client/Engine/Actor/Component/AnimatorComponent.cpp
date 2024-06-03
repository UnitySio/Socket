#include "AnimatorComponent.h"
#include "Graphics/Graphics.h"
#include "Graphics/SpriteBatch.h"
#include "Graphics/Sprite.h"
#include "TransformComponent.h"
#include "Time/time.h"
#include "Graphics/AnimationClip.h"

AnimatorComponent::AnimatorComponent(Actor* owner, const std::wstring& kName) 
	:ActorComponent(owner, kName),targetClip_(nullptr), frameNumber_(0), playTime(0)
{
    MakeAnimationClip(L"Idle", L"spritesheet.png");
    int frames[] = { 0, 1, 2, 3, 4, 5 };
    clips_[L"Idle"]->SetIncludeFrames(frames, 6);
    clips_[L"Idle"]->SetRepeat();
    clips_[L"Idle"]->SetPlaySpeed(5.0f);

    MakeAnimationClip(L"Attack", L"spritesheet.png");
    clips_[L"Attack"]->SetIncludeFrames(15, 42);
    clips_[L"Attack"]->SetPlaySpeed(10.0f);

    SetAnimationClip(L"Idle");

    std::vector<std::wstring> trigger;
    trigger.push_back(L"Attack");
    //triggers_.insert(L"Idle", trigger);// L"Attack"
}

void AnimatorComponent::MakeAnimationClip(std::wstring clipName, std::wstring path)
{
    clips_.insert(std::make_pair(clipName, std::make_shared<AnimationClip>(path)));
}

void AnimatorComponent::SetAnimationClip(std::wstring clipName)
{
    targetClip_ = clips_[clipName];
}

void AnimatorComponent::PlayAnimation()
{
    Graphics* gfx = Graphics::Get();
    SpriteBatch* batch = gfx->GetSpriteBatch();

    Actor* owner = GetOwner();
    TransformComponent* transform = owner->GetTransform();

    const Math::Vector2 location = transform->GetRelativeLocation();
    const float angle = transform->GetRelativeRotationZ();

    Math::Vector2 dir = { -1.f ,1.f };

    if (targetClip_ != nullptr)
    {
        Time time;
        playTime += time.DeltaTime();

        //1초에 playbackSpeed번 실행
        if (playTime >= 1.0f / targetClip_->GetPlaySpeed())
        {
            playTime = 0;

            //애니메이션이 끝나지 않음
            if (frameNumber_ < targetClip_->GetAnimationLength() - 1)
            {
                frameNumber_++;
            }
            //애니메이션을 모두 재생함
            else
            {
                //반복 옵션
                if (targetClip_->GetRepeat())
                {
                    frameNumber_ = 0;
                }
            }
        }

        batch->Draw(targetClip_->originSheet_.get(), L"spritesheet_" + std::to_wstring(targetClip_->GetAnimationIndex(frameNumber_)), location, { 1.f, 1.f }, angle);
    }
}