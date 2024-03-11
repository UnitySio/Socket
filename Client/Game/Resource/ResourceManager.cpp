#include "ResourceManager.h"

const int FRAME24 = 25;

ResourceManager::ResourceManager()
{
	ImagePool.clear();
	AppleIMG = AddImage(L".\\Game\\Resource\\apple.jpg");
	const wchar_t* RootIMG[3] = { L".\\Game\\Resource\\test1.png" , L".\\Game\\Resource\\test2.png", L".\\Game\\Resource\\test3.png"};
	testAni = AddAnimation(RootIMG, 3);
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
	//ID2D1Bitmap* Animation[FRAME24] = {};
	AnimationClip* head = new AnimationClip();
	AnimationClip* current = head;

	Graphics* graphic = Graphics::Get();

	int i = 0;
	while (i<frame)
	{
		ID2D1Bitmap* frameImage = graphic->LoadTexture(*path++);
		AnimationClip* clip = new AnimationClip();
		clip->bitmap_ = frameImage;

		if (head->bitmap_ == nullptr)
		{
			head = clip;
			current = head;
		}
		else
		{
			current->nextClip = clip;
			current = current->nextClip;
		}

		i++;
		//Animation[i++] = graphic->LoadTexture(*path++);
	}

	return head;
}

//ID2D1Bitmap** ResourceManager::AddAnimation(const wchar_t** path, int frame)
//{
//	//ID2D1Bitmap* Animation[FRAME24] = {};
//	AnimationClip* head;
//	AnimationClip* clip = head;
//
//	Graphics* graphic = Graphics::Get();
//
//	int i = 0;
//	while (i < frame)
//	{
//		if (path == NULL) break;
//
//		clip->Animation = graphic->LoadTexture(*path++);
//		clip = clip->nextClip;
//		//Animation[i++] = graphic->LoadTexture(*path++);
//	}
//
//	return head;
//}