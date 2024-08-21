﻿#pragma once
#include "Math/MathTypes.h"
#include "Misc/EngineMacros.h"
#include "Windows/DX/Vertex.h"

class TilemapComponent;
class ShapeBatch;
class WindowsWindow;

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();

    void Init(const std::shared_ptr<WindowsWindow>& window);
    void GameLoop(float delta_time);
    void OnQuit();

private:
    void StartFrame();
    void Tick(float delta_time);
    void Render(float alpha);
    void EndFrame();
    
    std::shared_ptr<WindowsWindow> game_window_;
    std::shared_ptr<ShapeBatch> shape_batch_;

    float accumulator_;
    
};
