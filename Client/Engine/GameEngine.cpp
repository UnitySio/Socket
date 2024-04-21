#include "GameEngine.h"

#include "Windows/WindowsWindow.h"

GameEngine* game_engine = nullptr;

GameEngine::GameEngine() :
    game_window_(nullptr)
{
}

void GameEngine::Init(WindowsApplication* application)
{
    game_window_ = application->MakeWindow();
    application->InitWindow(game_window_, nullptr);
    application->AddMessageHandler(*this);

    game_thread_ = CreateThread(nullptr, 0, GameThread, nullptr, 0, nullptr);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool GameEngine::ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam)) return true;

    if (message == WM_DESTROY)
    {
        WaitForSingleObject(game_thread_, INFINITE);
        return true;
    }
    
    return false;
}

DWORD GameEngine::GameThread(LPVOID lpParam)
{
    while (true)
    {
        break;
    }
    
    return 0;
}
