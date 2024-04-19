#include "WindowsApplication.h"

#include "EventManager.h"
#include "ProjectSettings.h"
#include "WindowsWindow.h"
#include "Audio/AudioManager.h"
#include "Graphics/Graphics.h"
#include "Time/Time.h"
#include "Level/World.h"
#include "Input/InputManager.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "Level/Level.h"

WindowsApplication* windows_application = nullptr;

WindowsApplication* WindowsApplication::CreateWindowsApplication(HINSTANCE instance_handle, HICON icon_handle)
{
    windows_application = new WindowsApplication(instance_handle, icon_handle);
    return windows_application;
}

WindowsApplication::WindowsApplication(HINSTANCE instance_handle, HICON icon_handle) :
    instance_handle_(instance_handle),
    windows_(),
    resolution_(),
    window_area_(),
    hWnd_(nullptr),
    focus_(nullptr),
    logic_handle_(nullptr),
    is_running_(false),
    alpha_(0.f)
{
    RegisterClass(instance_handle, icon_handle);
}

ATOM WindowsApplication::RegisterClass(HINSTANCE instance_handle, HICON icon_handle)
{
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = StaticWndProc;
    wcex.hInstance = instance_handle;
    wcex.hIcon = icon_handle;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    wcex.lpszClassName = L"GEWindow";

    return RegisterClassEx(&wcex);
}

bool WindowsApplication::InitWindow()
{
    if (!Graphics::Get()->Init()) return false;
    
    if (!AudioManager::Get()->Init()) return false;

    Time::Get()->Init();
    World::Get()->Init();
    InputManager::Get()->Init();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    const std::wstring kPath = ProjectSettings::kPath.at(L"GameData");
    const std::string kPathStr(kPath.begin(), kPath.end());

    const std::string kFont_1 = kPathStr + "NanumBarunGothic.ttf";
    const std::string kFont_2 = kPathStr + "Silver.ttf";
    
    ImGuiIO& io = ImGui::GetIO();
    static_cast<void>(io);
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.Fonts->AddFontFromFileTTF(kFont_1.c_str(), 16.f, nullptr, io.Fonts->GetGlyphRangesKorean());
    io.Fonts->AddFontFromFileTTF(kFont_2.c_str(), 24.f, nullptr, io.Fonts->GetGlyphRangesKorean());
    io.FontDefault = io.Fonts->Fonts[0];

    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(hWnd_);
    ImGui_ImplDX11_Init(Graphics::Get()->GetD3DDevice(), Graphics::Get()->GetD3DDeviceContext());

    logic_handle_ = CreateThread(nullptr, 0, LogicThread, nullptr, 0, nullptr);

    return true;
}

void WindowsApplication::InitializeWindow()
{
    const std::shared_ptr<WindowsWindow> window = std::make_shared<WindowsWindow>();
    
    windows_.push_back(window);
    window->Initialize(this, instance_handle_);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam)) return 0;

    if (message == WM_CREATE)
    {
#ifdef _DEBUG
        AllocConsole();
        SetConsoleTitle(L"Debug Console");

        _tfreopen(L"CONOUT$", L"w", stdout);
#endif
        return 0;
    }

    if (message == WM_SETFOCUS || message == WM_KILLFOCUS)
    {
        // focus_ = GetFocus();
        return 0;
    }

    if (message == WM_GETMINMAXINFO)
    {
        // reinterpret_cast<MINMAXINFO*>(lParam)->ptMinTrackSize.x = window_area_.right - window_area_.left;
        // reinterpret_cast<MINMAXINFO*>(lParam)->ptMinTrackSize.y = window_area_.bottom - window_area_.top;
        // reinterpret_cast<MINMAXINFO*>(lParam)->ptMaxTrackSize.x = window_area_.right - window_area_.left;
        // reinterpret_cast<MINMAXINFO*>(lParam)->ptMaxTrackSize.y = window_area_.bottom - window_area_.top;

        return 0;
    }

    if (message == WM_DESTROY)
    {
        // is_running_ = false;
        // WaitForSingleObject(logic_handle_, INFINITE);

        // World::Get()->GetLevel()->Unload(EndPlayReason::kQuit);
        //
        // ImGui_ImplWin32_Shutdown();
        // ImGui_ImplDX11_Shutdown();
        // ImGui::DestroyContext();
        //
        // InputManager::Get()->Release();
        // World::Get()->Release();
        // Time::Get()->Release();
        // AudioManager::Get()->Release();
        // Graphics::Get()->Release();
        // EventManager::Get()->Release();

        CoUninitialize();
        PostQuitMessage(0);
        return 0;
    }

    if (message == WM_CLOSE)
    {
#ifdef _DEBUG
        FreeConsole();
#endif
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT WindowsApplication::StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return WndProc(hWnd, message, wParam, lParam);
}

DWORD WindowsApplication::LogicThread(LPVOID lpParam)
{
    // Get()->is_running_ = true;
    // while (Get()->is_running_)
    // {
    //     Get()->MainLogic();
    // }

    return 0;
}

void WindowsApplication::MainLogic()
{
    Time::Get()->Tick();

    Graphics::Get()->BeginFrame3D();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    Tick(Time::DeltaTime());
    AudioManager::Tick();

    Graphics::Get()->BeginFrame2D();

    Render(alpha_);

    Graphics::Get()->EndFrame2D();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    Graphics::Get()->EndFrame3D();

    World::Get()->DestroyActor();
    EventManager::Get()->Tick();
}

void WindowsApplication::Tick(float delta_time)
{
    InputManager::Get()->Tick();
    
    static float accumulator = 0.f;
    // 죽음의 나선형을 방지하기 위해 최대 프레임 시간을 0.25초로 제한
    const float kFrameTime = min(delta_time, .25f);
    accumulator += kFrameTime;

    while (accumulator >= ProjectSettings::kFixedTimeStep)
    {
        World::Get()->PhysicsTick(ProjectSettings::kFixedTimeStep);
        accumulator -= ProjectSettings::kFixedTimeStep;
    }
    
    // 물리 시뮬레이션으로 인해 발생한 오차를 보정하기 위해 보간을 수행
    alpha_ = accumulator / ProjectSettings::kFixedTimeStep;
    
    World::Get()->Tick(delta_time);
}

void WindowsApplication::Render(float alpha)
{
    World::Get()->Render(alpha);
}
