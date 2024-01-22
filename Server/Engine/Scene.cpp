#include "Scene.h"

#include "Core.h"
#include "Extension/STDEx.h"
#include "imgui/imgui.h"
#include "Network/NetworkManager.h"
#include "Time/Time.h"

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
    
    std::shared_ptr<NetworkManager> network_manager = NetworkManager::GetInstance();

    if (ImGui::Begin(u8"콘솔"))
    {
        ImGui::Text(u8"FPS: %.f", Time::GetInstance()->GetFPS());
        ImGui::Text(u8"서버 상태: ");
        ImGui::Text(u8"현재 클라이언트 수: ");
        ImGui::Separator();

        const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
        if (ImGui::BeginChild("Logs", ImVec2(0, -footer_height_to_reserve), false,
                              ImGuiWindowFlags_HorizontalScrollbar))
        {
            for (auto& log : logs_)
            {
                ImVec4 color;
                bool has_color = false;

                if (log.find(u8"[에러]") != std::string::npos)
                {
                    color = ImVec4(1.f, .4f, .4f, 1.f);
                    has_color = true;
                }
                else if (log.compare(0, 2, "# ") == 0)
                {
                    color = ImVec4(1.f, .8f, .6f, 1.f);
                    has_color = true;
                }

                if (has_color) ImGui::PushStyleColor(ImGuiCol_Text, color);
                ImGui::TextUnformatted(log.c_str());
                if (has_color) ImGui::PopStyleColor();
            }

            if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                ImGui::SetScrollHereY(1.f);
        }

        ImGui::EndChild();
        ImGui::Separator();

        bool reclaim_focus = false;
        if (ImGui::InputText(u8"명령어", input_buffer_, IM_ARRAYSIZE(input_buffer_), ImGuiInputTextFlags_EnterReturnsTrue))
        {
            std::string command = input_buffer_;
            std::StringTrim(command);

            if (input_buffer_[0])
            {
                AddLog(u8"# %s", command.c_str());
                if (_stricmp(command.c_str(), u8"Start") == 0)
                {
                    AddLog(u8"서버를 시작합니다.");
                    
                    if (network_manager->InitServer())
                    {
                        network_manager->StartServer();
                    }
                }
                else if (_stricmp(command.c_str(), u8"Clear") == 0)
                {
                    logs_.clear();
                }
                else if (_stricmp(command.c_str(), u8"Exit") == 0)
                {
                    PostMessage(Core::GetInstance()->GetWindowHandle(), WM_CLOSE, 0, 0);
                }
                else AddLog(u8"알 수 없는 명령어입니다.");
            }

            strcpy_s(input_buffer_, "");
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
