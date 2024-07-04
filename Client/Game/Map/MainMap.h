#pragma once
#include "Level/Level.h"

class TilemapComponent;
class ProgressBar;
class Button;

class MainMap : public Level
{
public:
    MainMap(const std::wstring& kName);
    virtual ~MainMap() override = default;

    virtual void Load() override;
    virtual void Tick(float dt) override;

    ProgressBar* bar;
    Button* button;
    float Timer;
};

