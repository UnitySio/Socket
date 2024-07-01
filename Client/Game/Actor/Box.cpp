#include "Box.h"

#include "Actor/Component/BoxColliderComponent.h"
#include "Actor/Component/CircleColliderComponent.h"
#include "Actor/Component/RigidBodyComponent.h"

Box::Box(const std::wstring& kName) : Actor(kName)
{
    box_collider_ = CreateComponent<CircleColliderComponent>(L"BoxCollider");
    box_collider_->SetRadius(0.5f);

    rigid_body_ = CreateComponent<RigidBodyComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kDynamic);
    
}
