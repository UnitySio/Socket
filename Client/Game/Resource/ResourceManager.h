#pragma once
#include "../../Client/Engine/Graphics/Graphics.h"
#include "../../Client/Engine/Singleton.h"
#include <vector>

class AnimationClip
{
public:
	AnimationClip();
	AnimationClip(ID2D1Bitmap*);
	ID2D1Bitmap* bitmap_;
	AnimationClip* nextClip;
};

class ResourceManager:public Singleton<ResourceManager>
{
public:
	ResourceManager();
	//virtual ~ResourceManager() override = default;
	~ResourceManager();

	ID2D1Bitmap* AddImage(const WCHAR* path);
	AnimationClip* AddAnimation(const wchar_t **path,int frame);
	ID2D1Bitmap* GetPointer(ID2D1Bitmap* target) { return target; }

	std::vector<ID2D1Bitmap*> ImagePool;
	ID2D1Bitmap* AppleIMG;
	AnimationClip* testAni;
};