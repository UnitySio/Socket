#include "Floor.h"

#include "../../Engine/Actor/Component/BoxColliderComponent.h"

Floor::Floor(b2World* world, const std::wstring& kName) :
    Actor(world, kName)
{
    box_collider_ = CreateComponent<BoxColliderComponent>(L"BoxCollider");
    box_collider_->SetSize({1000.f, 32.f});
}
