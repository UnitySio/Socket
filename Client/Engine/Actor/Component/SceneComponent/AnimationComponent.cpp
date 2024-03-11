
#include "AnimationComponent.h"
#include "../../Client/Engine/Actor/Actor.h"
#include "../../Client/Engine/Level/Level.h"
#include "../Engine/Level/World.h"
#include "../../Client/Game/Resource/ResourceManager.h"

AnimationComponent::AnimationComponent(Actor* owner, const std::wstring& kName) : SceneComponent(owner, kName)
{
    ResourceManager* resourceManager = ResourceManager::Get();
    ChangeTargetAnimation(resourceManager->testAni);
}

void AnimationComponent::Render()
{
    PlayAnimation();
}

void AnimationComponent::TickComponent(float delta_time)
{

}

void AnimationComponent::ChangeTargetAnimation(AnimationClip* targetClip)
{
    assert(targetClip);
    beginingImage_ = targetClip;

    assert(beginingImage_);
    frameImage_ = beginingImage_;
}

void AnimationComponent::PlayAnimation()
{
    Graphics* graphics = Graphics::Get();

    Actor* Object = AnimationComponent::GetOwner();

    //피봇코드 추가. 컴포넌트 로컬 스케일은 오너의 스케일에 비례함.
    Vector ownerScale = { 1.0f, 1.0f };
    Vector scaleOffset = ownerScale * ImageScale_;

    //Vector position = AnimationComponent::GetRelativeTLocation();

    // 컴포넌트 개발시엔 컴포넌트 위치로
    Vector position = Object->GetActorLocation();
    Level* level = World::Get()->GetLevel();

    //피봇 변경
    b2Vec2 level_RenderPosition = level->GetRenderPosition({ position.x, position.y });
    Vector render_position = Vector(level_RenderPosition.x, level_RenderPosition.y) + (scaleOffset / 2.0f) * align_;
    float angle = Object->GetRootComponent()->GetRelativeRotation();
    graphics->DrawTexture(frameImage_->bitmap_, b2Vec2(render_position.x, render_position.y), { .1f * scaleOffset.x, .1f * scaleOffset.y }, angle);


    //TickComponent를 아직 쓸 줄 몰라서 만든 if문
    deltaTime += 0.1f;
    if (deltaTime >= 1 / FramePerSec)
    {
        //여기부터는 Tick으로 옮길 코드
            //프레임마다 이미지를 바꾼다. 변경하려면 Tick() 메서드를 이용할 것.
            if (frameImage_->nextClip != nullptr)
            {
                frameImage_ = frameImage_->nextClip;
                frameNumber_++;
            }
            //애니메이션의 끝에 도달해 Linked List의 헤드로 돌아감
            else if (frameImage_->nextClip == nullptr && repeat == true)
            {
                frameImage_ = beginingImage_;
                frameNumber_ = 0;
            }
        //여기까지

        deltaTime = 0;
    }
}