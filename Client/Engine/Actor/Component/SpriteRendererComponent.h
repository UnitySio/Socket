#pragma once
#include "../Actor.h"
#include "../Engine/Windows/DX/Sprite.h"

class SpriteRendererComponent :public ActorComponent
{
public:
	SpriteRendererComponent(Actor* owner, const std::wstring& kName);
	void SetRenderTarget(std::shared_ptr<Sprite> sprite);
	void SetFlipX(bool value);
	bool GetFlipX();

	std::shared_ptr<Sprite> sprite_;

private:
	bool flipX, flipY;
};