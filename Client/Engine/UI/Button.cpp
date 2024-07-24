#include "pch.h"
#include "Button.h"

#include "Input/Mouse.h"
#include "Level/World.h"
#include "Math/Color.h"
#include "Windows/WindowsWindow.h"

UI::Button::Button(const std::wstring& kName) :
    UIBase(kName)
{
    size_ = {180.f, 30.f};
}

void UI::Button::Tick(float deltaTime)
{
    UIBase::Tick(deltaTime);

    Math::Vector2 mouse_position = Mouse::Get()->GetMousePosition();
    if (Mouse::Get()->IsButtonPressed(MouseButton::kLeft))
    {
        if (rect_.Contains(mouse_position))
        {
            on_click.Execute();
        }
    }
}

void UI::Button::Render()
{
    WindowsWindow* window = World::Get()->GetWindow();
    Renderer::Get()->DrawBox(window, rect_, pivot_, Math::Color::White);
    
    UIBase::Render();
}
