#include "pch.h"
#include "Text.h"

#include "Level/World.h"
#include "Math/Color.h"
#include "Windows/WindowsWindow.h"

UI::Text::Text(const std::wstring& kName) :
    UIBase(kName),
    text_()
{
}

void UI::Text::Render()
{
    UIBase::Render();
    
    WindowsWindow* window = World::Get()->GetWindow();
    Renderer::Get()->DrawString(window, text_, rect_, pivot_, Math::Color::White);
}
