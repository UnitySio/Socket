#include "Scene.h"

#include "Core.h"
#include "imgui/imgui.h"
#include "Time/Time.h"

Scene::Scene()
{
}

void Scene::Release()
{
    Singleton<Scene>::Release();
}

void Scene::Tick(float delta_time)
{
}

void Scene::Render()
{
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu(u8"파일"))
        {
            if (ImGui::MenuItem(u8"종료"))
            {
                PostMessage(Core::GetInstance()->GetWindowHandle(), WM_CLOSE, 0, 0);
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
    
    if (ImGui::Begin(u8"콘솔"))
    {
        ImGui::Text(u8"FPS: %.f", Time::GetInstance()->GetFPS());
        ImGui::Text(u8"서버 상태: ");
        ImGui::Text(u8"현재 클라이언트 수: ");
        ImGui::Separator();

        const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
        if (ImGui::BeginChild("Logs", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar))
        {
            for (auto& log : logs_)
            {
                ImGui::Text(log.c_str());
            }
        }
        
        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);
        
        ImGui::EndChild();
        ImGui::Separator();

        bool reclaim_focus = false;
        if (ImGui::InputText(u8"명령어", input_buffer_, IM_ARRAYSIZE(input_buffer_), ImGuiInputTextFlags_EnterReturnsTrue))
        {
            AddLog(input_buffer_);
            reclaim_focus = true;
        }

        ImGui::SetItemDefaultFocus();
        if (reclaim_focus)
            ImGui::SetKeyboardFocusHere(-1);
    }

    ImGui::End();
}

void Scene::AddLog(std::string format, ...)
{
    va_list args;
    va_start(args, format);

    char buffer[1024];
    vsprintf_s(buffer, format.c_str(), args);

    va_end(args);
    
    logs_.push_back(buffer);
}
