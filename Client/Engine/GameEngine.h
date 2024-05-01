#pragma once
#include <memory>

class WindowsWindow;

class GameEngine
{
public:
    GameEngine();
    ~GameEngine() = default;

    void Init(const std::shared_ptr<WindowsWindow>& window);
    void Tick(float delta_time);
    void Render();

private:
    std::shared_ptr<WindowsWindow> game_window_;
    
};
