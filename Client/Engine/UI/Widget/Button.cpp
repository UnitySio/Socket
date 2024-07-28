#include "pch.h"
#include "Button.h"

#include "Level/World.h"
#include "Math/Color.h"
#include "Windows/WindowsWindow.h"

UI::Button::Button(const std::wstring& kName) :
    Widget(kName)
{
    size_ = {160.f, 30.f};
}

void UI::Button::OnMouseReleased()
{
    Widget::OnMouseReleased();

    on_click.Execute();
    
}

void UI::Button::Render()
{
    WindowsWindow* window = World::Get()->GetWindow();
    if (!window) return;
    
    Renderer* renderer = Renderer::Get();
    if (!renderer) return;

    Math::Vector2 pivot_position = GetPivotPosition();
    if (GetParent()) pivot_position = GetParent()->GetPivotPosition();

    renderer->DrawBox(window, rect_, pivot_position, Math::Color::White, angle_);
    
}
