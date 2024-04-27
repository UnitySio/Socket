#include "AnimatorComponent.h"
#include "Graphics/Graphics.h"
#include "Graphics/SpriteBatch.h"
#include "Graphics/Sprite.h"
#include "TransformComponent.h"
#include "Time/time.h"

AnimationClip::AnimationClip(/*int firstIndex, int lastIndex*/)
{
    Image = std::make_unique<Sprite>();
    isRepeat = false;
    playbackSpeed = .25f;
    //firstIndex_ = firstIndex;
    //lastIndex_ = lastIndex;
}

AnimatorComponent::AnimatorComponent(Actor* owner, const std::wstring& kName) 
	:ActorComponent(owner, kName),clip_(nullptr), frameNumber_(0), playTime(0)
{
    SetAnimationClip();
}

void AnimatorComponent::SetAnimationClip(/*파라미터 추가*/)
{
	clip_ = std::make_unique<AnimationClip>();

    //리소스 매니저 구현 필요?
    Graphics* gfx = Graphics::Get();

    clip_->Image = std::make_unique<Sprite>();
    assert(clip_->Image->Load(gfx->GetD3DDevice(), L"spritesheet.png"));

    clip_->Image->Split(3, 15, { .5f, 0.f });
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

    Time time;
    playTime += time.DeltaTime();
    if(playTime >= clip_->playbackSpeed)
    {
        playTime = 0;
        frameNumber_ > 4 ? frameNumber_ = 0 : frameNumber_++;
    }

    batch->Draw(clip_->Image.get(), L"spritesheet_" + std::to_wstring(frameNumber_), location, { 1.f, 1.f }, angle);
}