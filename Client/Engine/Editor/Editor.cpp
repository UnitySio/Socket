#include "pch.h"
#include "Editor.h"

#include "imgui/imgui.h"
#include "Level/World.h"

#include "Windows/WindowsWindow.h"

Editor::Editor() :
    show_level_(false)
{
}

void Editor::Tick(float delta_time)
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
            {
                WindowsWindow* window = World::Get()->GetWindow();
                PostMessage(window->GetHWnd(), WM_USER, 0, 0);
            }
            
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Window"))
        {
            ImGui::MenuItem("Level", nullptr, &show_level_);
            
            ImGui::EndMenu();
        }
    }
    
    ImGui::EndMainMenuBar();

    if (show_level_) DrawLevelWindow(&show_level_);
}

void Editor::DrawLevelWindow(bool* p_open)
{
    if (!ImGui::Begin("Level", p_open))
    {
        ImGui::End();
        return;
    }

    ImGui::Text("Hello, world!");

    ImGui::End();
}
