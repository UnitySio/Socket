#include "pch.h"
#include "Text.h"

#include "Level/World.h"
#include "Math/Color.h"
#include "Windows/WindowsWindow.h"

UI::Text::Text(const std::wstring& kName) :
    UIBase(kName),
    text_(),
    color_(Math::Color::White)
{
}

void UI::Text::Render()
{
    WindowsWindow* window = World::Get()->GetWindow();
    Renderer::Get()->DrawString(window, text_, rect_, pivot_, color_);
    
    UIBase::Render();
}
