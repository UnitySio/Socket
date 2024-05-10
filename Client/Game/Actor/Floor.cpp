﻿#include "Floor.h"

#include "GameEngine.h"
#include "ProjectSettings.h"
#include "Actor/Component/BoxColliderComponent.h"

Floor::Floor(World* world, const std::wstring& kName) :
    Actor(world, kName)
{
    SetLayer(ActorLayer::kFloor);

    box_collider_ = CreateComponent<BoxColliderComponent>(L"BoxCollider");
    box_collider_->SetSize({5.f, 1.f});
}
