#include "pch.h"
#include "Text.h"

#include "Level/World.h"
#include "Math/Color.h"
#include "Windows/WindowsWindow.h"

UI::Text::Text() : text_(L"")
{
}

void UI::Text::Render()
{
    WindowsWindow* window = World::Get()->GetWindow();
    Renderer::Get()->DrawString(window, text_, rect_, pivot_, Math::Color::White);
    // Renderer::Get()->DrawBox(window, rect_, pivot_, Math::Color::Red);
}
