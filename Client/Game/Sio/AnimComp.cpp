#include "pch.h"
#include "AnimComp.h"
#include "Windows/DX/Sprite.h"
#include "Actor/Component/Animator/AnimationClip.h"
#include "Actor/Actor.h"

AnimComp::AnimComp(Actor* owner, const std::wstring& kName)
	:ActorComponent(owner, kName)
{
	owner_ = owner;
	name_ = kName;

	sprite_ = std::make_shared<Sprite>();
	sprite_renderer_ = owner_->CreateComponent<SpriteRendererComponent>(L"SpriteRenderer");
	animator_ = owner_->CreateComponent<AnimatorComponent>(L"Animator");

	CHECK_IF(sprite_->Load(L".\\Game_Data\\spritesheet.png"), L"Failed to load texture");

	sprite_->Split(15, 3, Sprite::kCenter);

	sprite_renderer_->SetSprite(sprite_);

	int temp[] = { 0, 1, 2, 3, 4, 5 };
	animator_->AddClip(L"Idle", temp, 6);
	animator_->GetClip(L"Idle")->SetRepeat(true);
	animator_->GetClip(L"Idle")->SetFrameRate(6.f);
	animator_->PlayClip(L"Idle");
}

void AnimComp::BeginPlay()
{
	ActorComponent::BeginPlay();
	
}

void AnimComp::TickComponent(float dt)
{
	Super::TickComponent(dt);
	
}

void AnimComp::Render(float alpha)
{
	Super::Render(alpha);
}
