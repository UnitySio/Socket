#include "pch.h"
#include "Image.h"

#include "Level/World.h"
#include "Math/Color.h"
#include "Windows/WindowsWindow.h"
#include "Windows/DX/Renderer.h"
#include "Windows/DX/UITexture.h"

UI::Image::Image(const std::wstring& kName) :
    Widget(kName),
    texture_(nullptr)
{
}

void UI::Image::Render()
{
    WindowsWindow* window = World::Get()->GetWindow();
    if (!window) return;

    Renderer* renderer = Renderer::Get();
    if (!renderer) return;

    Math::Vector2 pivot_position = GetPivotPosition();
    if (GetParent()) pivot_position = GetParent()->GetPivotPosition();

    if (!texture_)
    {
        renderer->DrawBox(window, rect_, pivot_position, Math::Color::White, angle_);
        return;
    }

    renderer->DrawBitmap(window, texture_->GetTexture(), rect_, pivot_position, angle_);
}
