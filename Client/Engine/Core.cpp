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
#include "UI/Canvas.h"

Core::Core() :
    current_application_(nullptr),
    game_window_(),
    game_engine_(nullptr),
    is_running_(false),
    main_thread_(),
    mutex_(),
    current_time_(0.),
    last_time_(0.),
    delta_time_(0.),
    resize_width_(0),
    resize_height_(0)
{
}

void Core::Init(const HINSTANCE instance_handle)
{
    // 윈도우 애플리케이션을 생성하고 메시지 핸들러로 등록
    HICON icon_handle = LoadIcon(instance_handle, MAKEINTRESOURCE(IDI_ICON1));
    current_application_ = std::make_shared<WindowsApplication>(instance_handle, icon_handle);
    current_application_->AddMessageHandler(*this);

    // DirectX 11 렌더러 초기화
    CHECK_IF(Renderer::Get()->Init(), L"Failed to initialize renderer.");

    // 게임 윈도우 정의 생성
    std::shared_ptr<WindowDefinition> definition = std::make_shared<WindowDefinition>();
    definition->title = L"Fusion2D";
    definition->screen_x = 100;
    definition->screen_y = 100;
    definition->width = 800;
    definition->height = 600;

    // 게임 윈도우 생성
    std::shared_ptr<WindowsWindow> new_window = current_application_->MakeWindow();
    current_application_->InitWindow(new_window, definition, nullptr);

    // 렌더러에 뷰포트 생성
    CHECK_IF(Renderer::Get()->CreateViewport(new_window, {definition->width, definition->height}),
             L"Failed to create viewport.");
    CHECK_IF(Renderer::Get()->CreateD2DViewport(new_window), L"Failed to create D2D viewport.");

    game_window_ = new_window;

    // 게임 엔진 생성
    game_engine_ = std::make_shared<GameEngine>();
    game_engine_->Init(new_window);

    current_time_ = Time::Init();

    Start();
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool Core::ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam)) return true;
    if (Keyboard::Get()->ProcessMessage(message, wParam, lParam, handler_result)) return true;
    
    if (Canvas::Get()->ProcessMessage(hWnd, message, wParam, lParam, handler_result)) return true;

    if (message == WM_SIZE)
    {
        if (wParam == SIZE_MINIMIZED) return false;

        resize_width_ = LOWORD(lParam);
        resize_height_ = HIWORD(lParam);
    }

    if (message == WM_KILLFOCUS)
    {
        Keyboard::Get()->Clear();
    }

    if (message == WM_DESTROY)
    {
        if (const auto window = game_window_.lock())
        {
            if (window->GetHWnd() == hWnd)
            {
                Stop();
                game_engine_->OnQuit();

                World::Get()->Release();
                Renderer::Get()->Release();
                Canvas::Get()->Release();
            }
        }
    }

    return false;
}

void Core::MainThread()
{
    while (true)
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (!is_running_) break;
        }
        
#pragma region DeltaTime
        last_time_ = current_time_;
        current_time_ = Time::Seconds();

        double elapsed_time = current_time_ - last_time_;
        delta_time_ = elapsed_time;
#pragma endregion
        
        if (const auto& window = game_window_.lock())
        {
            if (resize_width_ > 0 && resize_height_ > 0)
            {
                Renderer::Get()->ResizeViewport(window, resize_width_, resize_height_);

                resize_width_ = 0;
                resize_height_ = 0;
            }

            game_engine_->GameLoop(delta_time_);
        }
    }
}

void Core::Start()
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        is_running_ = true;
    }
    
    main_thread_ = std::thread(&Core::MainThread, this);
}

void Core::Stop()
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        is_running_ = false;
    }
    
    if (main_thread_.joinable())
    {
        main_thread_.join();
    }
}
