#pragma once
#include "Character.h"

class PhysicsComp;
class AnimComp;
class InputComp;

class Sio : public Character
{
public:
	Sio(const std::wstring& kName);
	PhysicsComp* GetPhysicsComponent();
	AnimComp* GetAnimationComponent();
	InputComp* GetInputComponent();

protected:
	using Super = Character;

private:
	PhysicsComp* physics_;
	AnimComp* anims_;
	InputComp* input_;
};