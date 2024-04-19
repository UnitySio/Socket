#pragma once

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();

    void Tick();
    
};

extern GameEngine* GEngine;
