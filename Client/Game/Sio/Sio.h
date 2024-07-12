#pragma once
#include "Structure/Character.h"

class PhysicsComp;
class AnimComp;
class InputComp;

class Sio : public Character
{
public:
	Sio(const std::wstring& kName);
	inline PhysicsComp* GetPhysicsComponent() { return physics_; }
	inline AnimComp* GetAnimationComponent() { return anims_; }
	inline InputComp* GetInputComponent() { return input_; }

protected:
	using Super = Character;

private:
	PhysicsComp* physics_;
	AnimComp* anims_;
	InputComp* input_;
};