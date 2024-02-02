#include "Floor.h"

#include "../../Engine/Actor/Component/Scenecomponent/ShapeComponent/BoxComponent.h"

Floor::Floor(b2World* world, const std::wstring& kName) :
    Actor(world, kName)
{
    box_ = CreateComponent<BoxComponent>(L"Box");
    box_->SetBoxExtent(b2Vec2(683.f, 32.f));

    root_component_ = box_;
}
