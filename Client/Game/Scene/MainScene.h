#pragma once
#include "../../Engine/Scene/Scene.h"

class MainScene : public Scene
{
public:
    MainScene(const std::wstring& name);
    virtual ~MainScene() override = default;
    
};
