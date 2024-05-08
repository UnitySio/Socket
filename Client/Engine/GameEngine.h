#pragma once
#include "Misc/EngineMacros.h"

class World;
class ShapeBatch;
class WindowsWindow;

class GameEngine
{
public:
    GameEngine();
    ~GameEngine() = default;

    void Init(const SharedPtr<WindowsWindow>& window);
    void GameLoop(float delta_time);

private:
    SharedPtr<WindowsWindow> game_window_;
    SharedPtr<World> game_world_;
    SharedPtr<ShapeBatch> shape_batch_;
    
};

extern World* g_game_world;
