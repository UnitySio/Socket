#include "pch.h"
#include "Text.h"

#include "Level/World.h"
#include "Windows/WindowsWindow.h"
#include "Windows/DX/Renderer.h"

UI::Text::Text(const std::wstring& kName) :
    Widget(kName),
    text_(),
    color_(Math::Color::White)
{
}

void UI::Text::Render()
{
    WindowsWindow* window = World::Get()->GetWindow();
    if (!window) return;

    Renderer* renderer = Renderer::Get();
    if (!renderer) return;
    
    Math::Vector2 pivot_position = GetPivotPosition();
    if (GetParent()) pivot_position = GetParent()->GetPivotPosition();

    renderer->DrawString(window, text_, rect_, pivot_position, color_, angle_, L"Nanum18", DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
}
