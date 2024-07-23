#include "pch.h"
#include "Button.h"

#include "Input/Mouse.h"
#include "Level/World.h"
#include "Logger/Logger.h"
#include "Math/Color.h"
#include "Windows/WindowsWindow.h"

UI::Button::Button(const std::wstring& kName) :
    UIBase(kName)
{
}

void UI::Button::Tick(float deltaTime)
{
    UIBase::Tick(deltaTime);

    Math::Vector2 mouse_position = Mouse::Get()->GetMousePosition();
    if (Mouse::Get()->IsButtonPressed(MouseButton::kLeft))
    {
        if (rect_.Contains(mouse_position))
        {
            LOG(L"Button Clicked");
        }
    }
}

void UI::Button::Render()
{
    UIBase::Render();
    
    WindowsWindow* window = World::Get()->GetWindow();
    Renderer::Get()->DrawBox(window, rect_, pivot_, Math::Color::White);
}
