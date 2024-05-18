#include "AnimatorComponent.h"
#include "Graphics/Graphics.h"
#include "Graphics/SpriteBatch.h"
#include "Graphics/Sprite.h"
#include "TransformComponent.h"
#include "Time/time.h"

AnimationClip::AnimationClip(std::wstring clipName, int firstIndex, int lastIndex)
{
    clipName_ = clipName;//�̸�
    isRepeat = false;//�ݺ�
    playbackSpeed = 1.0f/2.0f;//����ӵ�
    firstIndex_ = firstIndex;//��Ʈ�� �� ��° ĭ����
    lastIndex_ = lastIndex;//��Ʈ�� �� ��° ĭ����
    frameNumber_ = 0;//���� ������
    maxFrame_ = lastIndex - firstIndex;//������ ��
    connected_OtherClip_ = ' ';//��ȯ�� ���� Ŭ��
}

void AnimationClip::ConnectToOther(std::wstring clipName)
{
    connected_OtherClip_ = clipName;
}

bool AnimationClip::TransToOther(std::wstring clipName)
{
    //���� �ִϸ��̼� ��ȯ�� ��ȯ ���ǿ� ���� ������ �Լ�
    return true;
}

AnimatorComponent::AnimatorComponent(Actor* owner, const std::wstring& kName) 
	:ActorComponent(owner, kName),targetClip_(nullptr), frameNumber_(0), playTime(0)
{
    originSheet_ = std::make_unique<Sprite>();

    Graphics* gfx = Graphics::Get();
    assert(originSheet_->Load(gfx->GetD3DDevice(), L"spritesheet.png"));

    originSheet_->Split(3, 15, { .5f, 0.f });

    MakeAnimationClip(L"Idle", 0, 5);
    MakeAnimationClip(L"Attack", 15, 41);
    clips_[1]->ConnectToOther(L"Idle");

    assert(SetAnimationClip(L"Idle", 4.0f));
}

void AnimatorComponent::MakeAnimationClip(std::wstring clipName, int firstIndex, int lastIndex)
{
    std::unique_ptr<AnimationClip> clip = std::make_unique<AnimationClip>(clipName,firstIndex,lastIndex);
    clips_.push_back(move(clip));
}

bool AnimatorComponent::SetAnimationClip(std::wstring clipName,float speed)
{
    frameNumber_ = 0;
    for (short i = 0;i < clips_.size();i++)
    {
        if (clips_[i]->clipName_ == clipName)
        {
            targetClip_ = clips_[i].get();
            targetClip_->playbackSpeed = 1.0f / speed;
            return true;
        }
    }
    
    return false;
}
bool AnimatorComponent::SetAnimationClip(int index)
{
    frameNumber_ = 0;
    targetClip_ = clips_[index].get();

    if (targetClip_ != nullptr) return true;
    else return false;
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
        batch->Draw(originSheet_.get(), L"spritesheet_" + std::to_wstring(targetClip_->firstIndex_ + frameNumber_), location, { 1.f, 1.f }, angle);

        Time time;
        playTime += time.DeltaTime();
        if (playTime >= targetClip_->playbackSpeed)
        {
            playTime = 0;

            if (frameNumber_ < targetClip_->maxFrame_)
            {
                frameNumber_++;
            }
            else
            {
                if (targetClip_->isRepeat)
                {
                    frameNumber_ = 0;
                }
                
                //�ִϸ��̼� ��ȯ �ӽ�
                if (targetClip_->TransToOther(L"Idle"))
                {
                    SetAnimationClip(L"Idle", 4.0f);
                }
            }
        }
    }    
}