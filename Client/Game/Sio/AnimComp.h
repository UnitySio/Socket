#pragma once
#include "Actor/Component/ActorComponent.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/Animator/AnimatorComponent.h"
#include <memory>

class Actor;

class AnimComp : public ActorComponent
{
public:
	AnimComp(Actor* owner, const std::wstring& kName);

protected:
	using Super = ActorComponent;
	virtual void BeginPlay() override;
	virtual void TickComponent(float dt) override;
	virtual void Render(float alpha) override;

private:
	std::shared_ptr<class Sprite> sprite_;
	SpriteRendererComponent* sprite_renderer_;
	AnimatorComponent* animator_;
};

