#pragma once
#include "../Actor.h"
#include "../Engine/Windows/DX/Sprite.h"
#include "SpriteRendererComponent.h"
#include "AnimationClip.h"

class AnimatorComponent :public ActorComponent
{
public:
	AnimatorComponent(Actor* owner, const std::wstring& kName);
	void Tick(float delta_time);
	void MakeAnimationClip(std::wstring clipname,int selected[],int size);
	void MakeAnimationClip(std::wstring clipname, int start_index, int end_index);

	SpriteRendererComponent* sprite_renderer_;

	std::map<std::wstring, std::shared_ptr<AnimationClip>> clips_;
	std::shared_ptr<AnimationClip> playing_clip_;
private:
	float timer_;
	float playSpeed_;
	int playing_index_;
};