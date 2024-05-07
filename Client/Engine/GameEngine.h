#pragma once
#include <memory>

class World;
class ShapeBatch;
class WindowsWindow;

class GameEngine
{
public:
    GameEngine();
    ~GameEngine() = default;

    void Init(const std::shared_ptr<WindowsWindow>& window);
    void GameLoop(float delta_time);

private:
    std::shared_ptr<WindowsWindow> game_window_;
    std::shared_ptr<World> game_world_;
    std::shared_ptr<ShapeBatch> shape_batch_;
    
};

extern World* g_game_world;
