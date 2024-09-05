#pragma once
#pragma comment(lib, "Xinput.lib")

#include "Singleton.h"

class Gamepad : public Singleton<Gamepad>
{
public:
    Gamepad();
    virtual ~Gamepad() override = default;

private:
    friend class GameEngine;

    void Tick();
    
};
