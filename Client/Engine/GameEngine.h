#pragma once
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
    std::shared_ptr<WindowsWindow> game_window_;
    std::shared_ptr<ShapeBatch> shape_batch_;
    
};
