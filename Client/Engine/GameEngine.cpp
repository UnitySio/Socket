#include "GameEngine.h"

#include <cwchar>
#include <Windows.h>

#include "Windows/WindowsWindow.h"

GameEngine::GameEngine() :
    game_window_(nullptr)
{
}

void GameEngine::Init(const std::shared_ptr<WindowsWindow>& window)
{
    game_window_ = window;
}

void GameEngine::Tick(float delta_time)
{
    static float timer = 0.f;
    timer += delta_time;

    wchar_t buffer[256];
    swprintf(buffer, 256, L"Timer: %f", timer);
    SetWindowText(game_window_->GetHWnd(), buffer);
}

void GameEngine::Render()
{
}
