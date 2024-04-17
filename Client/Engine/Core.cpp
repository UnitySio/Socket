#include "Core.h"

#include "EventManager.h"
#include "ProjectSettings.h"
#include "Audio/AudioManager.h"
#include "Graphics/Graphics.h"
#include "Time/Time.h"
#include "Level/World.h"
#include "Input/InputManager.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "Level/Level.h"

Core::Core() :
    resolution_(),
    window_area_(),
    hWnd_(nullptr),
    focus_(nullptr),
    logic_handle_(nullptr),
    is_running_(false),
    alpha_(0.f)
{
}

ATOM Core::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = StaticWndProc;
    wcex.hInstance = hInstance;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    wcex.lpszClassName = ProjectSettings::kProjectClassName.c_str();

    return RegisterClassEx(&wcex);
}

BOOL Core::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    const int kScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    const int kScreenHeight = GetSystemMetrics(SM_CYSCREEN);

    resolution_ = {ProjectSettings::kScreenWidth, ProjectSettings::kScreenHeight};
    window_area_ = {0, 0, resolution_.x, resolution_.y};
    AdjustWindowRect(&window_area_, WS_OVERLAPPEDWINDOW, FALSE);

    hWnd_ = CreateWindowEx(
        0,
        ProjectSettings::kProjectClassName.c_str(),
        ProjectSettings::kProjectName.c_str(),
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX,
        (kScreenWidth - (window_area_.right - window_area_.left)) / 2,
        (kScreenHeight - (window_area_.bottom - window_area_.top)) / 2,
        window_area_.right - window_area_.left,
        window_area_.bottom - window_area_.top,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (!hWnd_) return FALSE;
    ShowWindow(hWnd_, nCmdShow);

    return TRUE;
}

bool Core::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow)) return false;
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);

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

LRESULT Core::StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return Get()->WndProc(hWnd, message, wParam, lParam);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT Core::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
        focus_ = GetFocus();
        return 0;
    }

    if (message == WM_GETMINMAXINFO)
    {
        reinterpret_cast<MINMAXINFO*>(lParam)->ptMinTrackSize.x = window_area_.right - window_area_.left;
        reinterpret_cast<MINMAXINFO*>(lParam)->ptMinTrackSize.y = window_area_.bottom - window_area_.top;
        reinterpret_cast<MINMAXINFO*>(lParam)->ptMaxTrackSize.x = window_area_.right - window_area_.left;
        reinterpret_cast<MINMAXINFO*>(lParam)->ptMaxTrackSize.y = window_area_.bottom - window_area_.top;

        return 0;
    }

    if (message == WM_DESTROY)
    {
        is_running_ = false;
        WaitForSingleObject(logic_handle_, INFINITE);

        World::Get()->GetLevel()->Unload(EndPlayReason::kQuit);

        ImGui_ImplWin32_Shutdown();
        ImGui_ImplDX11_Shutdown();
        ImGui::DestroyContext();

        InputManager::Get()->Release();
        World::Get()->Release();
        Time::Get()->Release();
        AudioManager::Get()->Release();
        Graphics::Get()->Release();
        EventManager::Get()->Release();
        Get()->Release();

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

DWORD Core::LogicThread(LPVOID lpParam)
{
    Get()->is_running_ = true;
    while (Get()->is_running_)
    {
        Get()->MainLogic();
    }

    return 0;
}

void Core::MainLogic()
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

void Core::Tick(float delta_time)
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

void Core::Render(float alpha)
{
    World::Get()->Render(alpha);
}
