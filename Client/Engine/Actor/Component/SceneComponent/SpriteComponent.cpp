#include "SpriteComponent.h"
#include "../../Client/Engine/Actor/Actor.h"
#include "../../Client/Engine/Level/Level.h"
#include "../Engine/Level/World.h"
#include "../../Client/Game/Resource/ResourceManager.h"

SpriteComponent::SpriteComponent(Actor* owner, const std::wstring& kName) : SceneComponent(owner, kName)
{
    ResourceManager* resourceManager = ResourceManager::Get();
    Graphics* graphics = Graphics::Get();
    targetImage_ = resourceManager->AppleIMG;
    assert(targetImage_); // bitmap_가 null일 경우 오류 발생
}

void SpriteComponent::Render()
{
    Graphics* graphics = Graphics::Get();

    Actor* Object = SpriteComponent::GetOwner();

    //피봇코드 추가. 컴포넌트 로컬 스케일은 오너의 스케일에 비례함.
    Vector ownerScale = { 1.0f, 1.0f };
    Vector scaleOffset = ownerScale * ImageScale_;

    Vector position = Object->GetActorLocation(); // 컴포넌트 개발시엔 컴포넌트 위치로
    Level* level = World::Get()->GetLevel();
    b2Vec2 level_RenderPosition = level->GetRenderPosition({ position.x, position.y });
    Vector render_position = Vector(level_RenderPosition.x, level_RenderPosition.y) + (scaleOffset / 2.0f) * align_;

    float angle = Object->GetRootComponent()->GetRelativeRotation();

    graphics->DrawTexture(targetImage_, b2Vec2(render_position.x, render_position.y), { .1f * scaleOffset.x, .1f * scaleOffset.y }, angle);
}

void SpriteComponent::ChangeTargetImage(ID2D1Bitmap* newTarget) { targetImage_ = newTarget; }
