#pragma once
#include "Level/Level.h"
#include "../Engine/Input/Keyboard.h"

class MainMap : public Level
{
public:
    MainMap(const std::wstring& kName);
    virtual ~MainMap() override = default;

    virtual void Load() override;

    SHARED_PTR<Actor> pawn;

    void OnKeyDown(const EventKeyboard& e);
    void OnKeyPressed(const EventKeyboard& e);
    void OnKeyUp(const EventKeyboard& e);
};
