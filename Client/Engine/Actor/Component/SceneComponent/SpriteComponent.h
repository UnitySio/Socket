#pragma once
#define Top_Left Vector(-50.0f, -50.0f)
#define Top_Right Vector(50.0f, -50.0f)
#define Bottom_Left Vector(-50.0f, 50.0f)
#define Bottom_Right Vector(50.0f, 50.0f)
#define Center Vector(0.0f, 0.0f)

#include "SceneComponent.h"
#include "../../Client/Engine/Graphics/Graphics.h"

class SpriteComponent : public SceneComponent
{
public:
    SpriteComponent(Actor* owner, const std::wstring& kName);
    void Render();
    virtual ~SpriteComponent() override = default;
    void ChangeTargetImage(ID2D1Bitmap* newTarget);
    
    class ID2D1Bitmap* targetImage_ = {};
    Vector ImageScale_ = { 0.5f,0.5f };
    Vector align_ = Bottom_Right;
};
