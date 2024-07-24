#include "pch.h"
#include "Slider.h"

#include "Input/Mouse.h"
#include "Level/World.h"
#include "Logger/Logger.h"
#include "Math/Color.h"
#include "Math/Math.h"
#include "Windows/DX/Renderer.h"

UI::Slider::Slider(const std::wstring& kName) :
    UIBase(kName),
    value_(0),
    min_value_(0),
    max_value_(100)
{
    size_ = {160.f, 20.f};
}

void UI::Slider::Tick(float deltaTime)
{
    UIBase::Tick(deltaTime);

    Mouse* mouse = Mouse::Get();
    Math::Vector2 mouse_position = mouse->GetMousePosition();
    if (mouse->IsButtonDown(MouseButton::kLeft))
    {
        if (rect_.Contains(mouse_position))
        {
            value_ = static_cast<int>((mouse_position.x - rect_.x) / size_.x * max_value_);
            value_ = Math::Clamp(value_, min_value_, max_value_);

            LOG(L"value: %d", value_);
        }
    }
}

void UI::Slider::Render()
{
    WindowsWindow* window = World::Get()->GetWindow();
    Renderer::Get()->DrawBox(window, rect_, pivot_, Math::Color::White);
    Renderer::Get()->DrawBox(window, {rect_.x, rect_.y, size_.x * value_ / max_value_, size_.y}, pivot_, Math::Color::Red);
    
    UIBase::Render();
}
