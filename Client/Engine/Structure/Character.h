#pragma once
#include "Interactable.h"

class SpriteRendererComponent;
class AnimatorComponent;
class b2Body;

class Character : public Interactable
{
public:
	Character(const std::wstring& kName);
	//std::shared_ptr<SpriteRendererComponent>& GetSpriteRenderer();
	//std::shared_ptr<AnimatorComponent>& GetAnimatorComponent();
	//b2Body* GetBody();

protected:
	using Super = Interactable;
	/*std::shared_ptr<SpriteRendererComponent> spriteRenderer_;
	std::shared_ptr<AnimatorComponent> animator_;*/
};

