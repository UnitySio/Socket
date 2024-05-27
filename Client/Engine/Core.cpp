#include "Core.h"

#include "GameEngine.h"
#include "Input/Keyboard.h"
#include "Level/World.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
#include "Time/Time.h"
#include "Windows/WindowDefinition.h"
#include "Windows/WindowsWindow.h"
#include "Windows/DX/Renderer.h"

double Core::current_time_ = 0.;
double Core::last_time_ = 0.;
double Core::delta_time_ = 0.;

MathTypes::uint32 Core::resize_width_ = 0;
MathTypes::uint32 Core::resize_height_ = 0;

Core::Core() :
    current_application_(nullptr),
    game_window_(),
    game_thread_handle_(nullptr),
    is_game_running_(false)
{
}

void Core::Init(const HINSTANCE instance_handle)
{
    // 윈도우 애플리케이션을 생성하고 메시지 핸들러로 등록
    HICON icon_handle = LoadIcon(instance_handle, MAKEINTRESOURCE(IDI_ICON1));
    current_application_ = MAKE_SHARED<WindowsApplication>(instance_handle, icon_handle);
    current_application_->AddMessageHandler(*this);

    // DirectX 11 렌더러 초기화
    CHECK_IF(Renderer::Get()->Init(), L"Failed to initialize renderer.");

    // 게임 윈도우 정의 생성
    SHARED_PTR<WindowDefinition> definition = MAKE_SHARED<WindowDefinition>();
    definition->title = L"Fusion2D";
    definition->screen_x = 100;
    definition->screen_y = 100;
    definition->width = 640;
    definition->height = 480;

    // 게임 윈도우 생성
    SHARED_PTR<WindowsWindow> new_window = current_application_->MakeWindow();
    current_application_->InitWindow(new_window, definition, nullptr);

    // 렌더러에 뷰포트 생성
    CHECK_IF(Renderer::Get()->CreateViewport(new_window, {definition->width, definition->height}), L"Failed to create viewport.");
    CHECK_IF(Renderer::Get()->CreateD2DViewport(new_window), L"Failed to create D2D viewport.");
    
    game_window_ = new_window;
    
    // 게임 엔진 생성
    game_engine_ = MAKE_SHARED<GameEngine>();
    game_engine_->Init(new_window);

    current_time_ = Time::Init();

    // 게임 스레드 생성
    game_thread_handle_ = CreateThread(nullptr, 0, GameThread, this, 0, nullptr);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool Core::ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam)) return true;
    if (Keyboard::Get()->ProcessMessage(message, wParam, lParam, handler_result)) return true;

    if (message == WM_SIZE)
    {
        if (wParam == SIZE_MINIMIZED) return false;
        
        resize_width_ = LOWORD(lParam);
        resize_height_ = HIWORD(lParam);
    }
    
    if (message == WM_DESTROY)
    {
        if (const auto window = game_window_.lock())
        {
            if (window->GetHWnd() == hWnd)
            {
                is_game_running_ = false;
                
                // 게임 스레드가 종료될 때까지 대기
                WaitForSingleObject(game_thread_handle_, INFINITE);
                game_engine_->OnQuit();

                World::Get()->Release();
                Renderer::Get()->Release();
            }
        }
    }
    
    return false;
}

DWORD Core::GameThread(LPVOID lpParam)
{
    Core* core = static_cast<Core*>(lpParam);
    if (!core) return 0;

    GameEngine* game_engine = core->game_engine_.get();
    core->is_game_running_ = true;
    
    while (true)
    {
#pragma region DeltaTime
        last_time_ = current_time_;
        current_time_ = Time::Seconds();
        
        float elapsed_time = static_cast<float>(current_time_ - last_time_);
        float sleep_time = (1.f / 60.f) - elapsed_time;
        if (sleep_time > 0.f)
        {
            DWORD sleep_ms = static_cast<DWORD>(sleep_time * 1000.f);
            Sleep(sleep_ms);
        }

        delta_time_ = elapsed_time + sleep_time;
#pragma endregion
        
        if (const auto& window = core->game_window_.lock())
        {
            if (resize_width_ > 0 && resize_height_ > 0)
            {
                Renderer::Get()->ResizeViewport(window, resize_width_, resize_height_);
                
                resize_width_ = 0;
                resize_height_ = 0;
            }
            
            game_engine->GameLoop(delta_time_);
        }
        
        if (!core->is_game_running_) break;
    }
    
    return 0;
}
