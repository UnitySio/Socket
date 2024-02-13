#include "Box.h"

#include "../../Engine/Actor/Component/Scenecomponent/ShapeComponent/BoxComponent.h"

Box::Box(b2World* world, const std::wstring& kName) :
    Actor(world, kName)
{
    box_ = CreateComponent<BoxComponent>(L"Box");
    SetRootComponent(box_);

    box_->SetBoxExtent(b2Vec2(16.f, 16.f));
}
