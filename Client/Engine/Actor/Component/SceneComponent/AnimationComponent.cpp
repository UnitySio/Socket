
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

    //�Ǻ��ڵ� �߰�. ������Ʈ ���� �������� ������ �����Ͽ� �����.
    Vector ownerScale = { 1.0f, 1.0f };
    Vector scaleOffset = ownerScale * ImageScale_;

    //Vector position = AnimationComponent::GetRelativeTLocation();

    // ������Ʈ ���߽ÿ� ������Ʈ ��ġ��
    Vector position = Object->GetActorLocation();
    Level* level = World::Get()->GetLevel();

    //�Ǻ� ����
    b2Vec2 level_RenderPosition = level->GetRenderPosition({ position.x, position.y });
    Vector render_position = Vector(level_RenderPosition.x, level_RenderPosition.y) + (scaleOffset / 2.0f) * align_;
    float angle = Object->GetRootComponent()->GetRelativeRotation();
    graphics->DrawTexture(frameImage_->bitmap_, b2Vec2(render_position.x, render_position.y), { .1f * scaleOffset.x, .1f * scaleOffset.y }, angle);


    //TickComponent�� ���� �� �� ���� ���� if��
    deltaTime += 0.1f;
    if (deltaTime >= 1 / FramePerSec)
    {
        //������ʹ� Tick���� �ű� �ڵ�
            //�����Ӹ��� �̹����� �ٲ۴�. �����Ϸ��� Tick() �޼��带 �̿��� ��.
            if (frameImage_->nextClip != nullptr)
            {
                frameImage_ = frameImage_->nextClip;
                frameNumber_++;
            }
            //�ִϸ��̼��� ���� ������ Linked List�� ���� ���ư�
            else if (frameImage_->nextClip == nullptr && repeat == true)
            {
                frameImage_ = beginingImage_;
                frameNumber_ = 0;
            }
        //�������

        deltaTime = 0;
    }
}