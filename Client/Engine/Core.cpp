#include "Core.h"

#include "Windows/WindowsWindow.h"

Core* core = nullptr;

Core* Core::Create()
{
    core = new Core();
    return core;
}

Core::Core() :
    current_application_(nullptr),
    game_window_(),
    game_thread_handle_(nullptr),
    is_game_running_(false)
{
}

Core::~Core()
{
}

void Core::Init(const HINSTANCE instance_handle)
{
    // 윈도우 애플리케이션을 생성하고 메시지 핸들러로 등록
    HICON icon_handle = LoadIcon(instance_handle, MAKEINTRESOURCE(IDI_ICON1));
    current_application_ = std::shared_ptr<WindowsApplication>(WindowsApplication::CreateWindowsApplication(instance_handle, icon_handle));
    current_application_->AddMessageHandler(*this);

    // 게임 윈도우 생성
    std::shared_ptr<WindowsWindow> new_window = current_application_->MakeWindow();
    current_application_->InitWindow(new_window, nullptr);
    game_window_ = new_window;

    // 게임 스레드 생성
    game_thread_handle_ = CreateThread(nullptr, 0, GameThread, nullptr, 0, nullptr);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool Core::ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam)) return true;
    if (message == WM_DESTROY)
    {
        if (const auto window = game_window_.lock())
        {
            if (window->GetHWnd() == hWnd)
            {
                is_game_running_ = false;
                
                // 게임 스레드가 종료될 때까지 대기
                WaitForSingleObject(game_thread_handle_, INFINITE);
            }
        }
    }
    
    return false;
}

DWORD Core::GameThread(LPVOID lpParam)
{
    core->is_game_running_ = true;
    
    while (true)
    {
        if (!core->is_game_running_) break;
    }
    
    return 0;
}
