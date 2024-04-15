#pragma once
#include "ColliderComponent.h"

class BoxColliderComponent : public ColliderComponent
{
public:
    BoxColliderComponent(Actor* owner, const std::wstring& kName);
    virtual ~BoxColliderComponent() override = default;

    virtual void SetOffset(const Math::Vector2& kOffset) override;

    void SetSize(Math::Vector2 size);

private:
    void SetBox();
    
    Math::Vector2 size_;
    
};
