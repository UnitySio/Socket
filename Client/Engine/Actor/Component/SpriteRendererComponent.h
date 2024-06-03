#pragma once
#include "../Actor.h"
#include "../Engine/Windows/DX/Sprite.h"

class SpriteRendererComponent :public ActorComponent
{
public:
	SpriteRendererComponent(Actor* owner, const std::wstring& kName);
	void RenderSprite();
	void SetRenderTarget();
	void SetFlipX(bool value) { flipX = value; }
	bool GetFlipX() { return flipX; }

private:
	std::unique_ptr<Sprite> sprite_;
	bool flipX, flipY;
};