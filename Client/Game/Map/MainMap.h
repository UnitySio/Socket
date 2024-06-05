#pragma once
#include "Level/Level.h"
#include "../Engine/Input/Keyboard.h"

class MainMap : public Level
{
public:
    MainMap(const std::wstring& kName);
    virtual ~MainMap() override = default;

    virtual void Load() override;

    void OnKeyDown(EventKeyboard e);
    void OnKeyUp(EventKeyboard e);
};
