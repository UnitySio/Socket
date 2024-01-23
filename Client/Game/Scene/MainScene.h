#pragma once
#include "../../Engine/Scene/Scene.h"

class MainScene : public Scene
{
public:
    MainScene();
    virtual ~MainScene() final = default;

    virtual void Begin() final;
    virtual void Tick(float deltaTime) final;
    virtual void Render() final;
    virtual void End() final;
    
};
