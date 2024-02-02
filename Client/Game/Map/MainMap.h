#pragma once
#include "../../Engine/Scene/Scene.h"

class MainMap : public Scene
{
public:
    MainMap(const std::wstring& kName);
    virtual ~MainMap() override = default;
    
};
