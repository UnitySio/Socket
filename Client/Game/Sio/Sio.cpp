#include "pch.h"
#include "Sio.h"
#include "PhysicsComp.h"
#include "AnimComp.h"
#include "InputComp.h"

Sio::Sio(const std::wstring& kName)
	:Super(kName)
{
	physics_ = CreateComponent<PhysicsComp>(L"PhysicsComponent");
	anims_ = CreateComponent<AnimComp>(L"AnimationComponent");
	input_ = CreateComponent<InputComp>(L"InputComponent");
}


