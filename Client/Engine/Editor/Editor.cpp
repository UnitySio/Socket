#include "pch.h"
#include "Editor.h"

#include "imgui/imgui.h"
#include "Level/World.h"

#include "Windows/WindowsWindow.h"
#include "Windows/DX/Texture.h"

Editor::Editor() :
    show_sprite_animator_(false),
    sprite_sheet_(nullptr)
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
            ImGui::MenuItem("Sprite Animator", nullptr, &show_sprite_animator_);
            
            ImGui::EndMenu();
        }
    }
    
    ImGui::EndMainMenuBar();

    if (show_sprite_animator_) OpenSpriteAnimator(&show_sprite_animator_);
}

void Editor::OpenSpriteAnimator(bool* p_open)
{
    if (!ImGui::Begin("Sprite Animator", p_open))
    {
        ImGui::End();
        return;
    }

    ImGui::End();
}
