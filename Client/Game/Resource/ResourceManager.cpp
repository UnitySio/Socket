#include "ResourceManager.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

AnimationClip::AnimationClip(): bitmap_(nullptr), nextClip(nullptr)
{
}
AnimationClip::AnimationClip(ID2D1Bitmap* bitmap) : bitmap_(nullptr), nextClip(nullptr)
{
	bitmap_ = bitmap;
}

ResourceManager::ResourceManager():AppleIMG(nullptr),testAni(nullptr)
{
	ImagePool.clear();
	AppleIMG = AddImage(L".\\Game\\Resource\\apple.jpg");
	const wchar_t* RootIMG[3] = { L".\\Game\\Resource\\test1.png" , L".\\Game\\Resource\\test2.png", L".\\Game\\Resource\\test3.png"};
	testAni = AddAnimation(RootIMG, 3);
}

ResourceManager::~ResourceManager()
{
	/*for (ID2D1Bitmap* Image : ImagePool)
	{
		free(&Image);
	}*/

	ImagePool.clear();

	//_crtBreakAlloc = 417;
	_CrtDumpMemoryLeaks();
}

ID2D1Bitmap* ResourceManager::AddImage(const WCHAR* path)
{
	Graphics* graphic = Graphics::Get();

	ID2D1Bitmap* InstanceIMG = graphic->LoadTexture(path);
	ImagePool.push_back(InstanceIMG);

	return InstanceIMG;
}

AnimationClip* ResourceManager::AddAnimation(const wchar_t **path,int frame)
{
	AnimationClip* head = nullptr;
	AnimationClip* current = nullptr;

	Graphics* graphic = Graphics::Get();

	while (frame--)
	{
		ID2D1Bitmap* frameImage = graphic->LoadTexture(*path++);
		ImagePool.push_back(frameImage);

		if (head == nullptr)
		{
			head = new AnimationClip(frameImage);

			current = head;
			continue;
		}

		while (current->nextClip != nullptr)
		{
			current = current->nextClip;
		}
		current->nextClip = new AnimationClip(frameImage);
	}

	return head;
}