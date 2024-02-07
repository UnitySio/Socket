﻿#include "Floor.h"

#include "../../Engine/Actor/Component/Scenecomponent/ShapeComponent/BoxComponent.h"

Floor::Floor(b2World* world, const std::wstring& kName) :
    Actor(world, kName)
{
    box_ = CreateComponent<BoxComponent>(L"Box");
    root_component_ = box_;
    
    box_->SetBoxExtent(b2Vec2(341.5f, 16.f));
}
