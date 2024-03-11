#pragma once
#define Top_Left Vector(-50.0f, -50.0f)
#define Top_Right Vector(50.0f, -50.0f)
#define Bottom_Left Vector(-50.0f, 50.0f)
#define Bottom_Right Vector(50.0f, 50.0f)
#define Center Vector(0.0f, 0.0f)

#include "SceneComponent.h"
#include "../../Client/Engine/Graphics/Graphics.h"
#include "../../Client/Game/Resource/ResourceManager.h"

class AnimationComponent : public SceneComponent
{
public:
    AnimationComponent(Actor* owner, const std::wstring& kName);
    virtual ~AnimationComponent() override = default;
    void Render();
    void ChangeTargetAnimation(AnimationClip* AfterAni);
    void PlayAnimation();
    virtual void TickComponent(float delta_time) override;

    AnimationClip* frameImage_;
    AnimationClip* beginingImage_;
    int frameNumber_ = 0;
    Vector ImageScale_ = { 1.0f,1.0f };
    Vector align_ = Top_Left;
    bool repeat = true;

    //TickComponent를 아직 쓸 줄 몰라서 만든 쓰레기 변수
    const float FramePerSec = 3;
    float deltaTime = 0;
};
