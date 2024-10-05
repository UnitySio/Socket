#include "pch.h"
#include "Editor.h"

#include "imgui/imgui.h"
#include "Level/World.h"

#include "Windows/WindowsWindow.h"

Editor::Editor()
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
    }
    
    ImGui::EndMainMenuBar();
}
