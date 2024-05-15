#pragma once
#include "Misc/EngineMacros.h"

class ShapeBatch;
class WindowsWindow;

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();

    void Init(const SHARED_PTR<WindowsWindow>& window);
    void GameLoop(float delta_time);
    void OnQuit();

private:
    SHARED_PTR<WindowsWindow> game_window_;
    SHARED_PTR<ShapeBatch> shape_batch_;
    
};
