#include "pch.h"
#include "ScrollBox.h"

#include "Input/Mouse.h"
#include "Level/World.h"
#include "Math/Color.h"
#include "Windows/DX/Renderer.h"

UI::ScrollBox::ScrollBox(const std::wstring& kName) : UIBase(kName)
{
}

void UI::ScrollBox::Tick(float deltaTime)
{
    UIBase::Tick(deltaTime);

    Mouse* mouse = Mouse::Get();
    Math::Vector2 mouse_position = mouse->GetMousePosition();
    if (rect_.Contains(mouse_position))
    {
        int wheel_axis = mouse->GetWheelAxis();
        if (wheel_axis != 0)
        {
            Math::Vector2 scroll = Math::Vector2(0.0f, -wheel_axis * 10.0f);
            for (UIBase* child : children_)
            {
                child->Translate(scroll);
            }
        }
    }
}

void UI::ScrollBox::Render()
{
    WindowsWindow* window = World::Get()->GetWindow();
    Renderer::Get()->DrawBox(window, rect_, pivot_, Math::Color::Black);
    
    Renderer::Get()->BeginLayer(rect_);
    UIBase::Render();
    Renderer::Get()->EndLayer();
}
