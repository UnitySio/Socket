#pragma once
#include "Actor/Actor.h"

class SpriteRendererComponent;
class Sprite;

class TopDownCharacter : public Actor
{
    SHADER_CLASS_HELPER(TopDownCharacter)
    GENERATED_BODY(TopDownCharacter, Actor)
    
public:
    TopDownCharacter(const std::wstring& name);
    virtual ~TopDownCharacter() override = default;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float delta_time) override;
    virtual void PostTick(float delta_time) override;
    
    SpriteRendererComponent* shadow_renderer_;
    SpriteRendererComponent* sprite_renderer_;

    Sprite* shadow_;
    Sprite* sprite_;

    float gravity_;
    float z_;
    float z_height_;
    float z_floor_;
    float z_speed_;
    
};
