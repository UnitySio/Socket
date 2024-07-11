#include "Character.h"
#include "Actor/Component/Animator/AnimatorComponent.h"
#include "Actor/Component/SpriteRendererComponent.h"

Character::Character(const std::wstring& kName)
	:Super(kName)
{
	spriteRenderer_ = std::make_shared<SpriteRendererComponent>(this, kName);
	animator_ = std::make_shared<AnimatorComponent>(this, kName);
}

std::shared_ptr<SpriteRendererComponent>& Character::GetSpriteRenderer()
{
	return spriteRenderer_;
}

std::shared_ptr<AnimatorComponent>& Character::GetAnimatorComponent()
{
	return animator_;
}
