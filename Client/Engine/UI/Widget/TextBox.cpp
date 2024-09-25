#include "pch.h"
#include "TextBox.h"

#include "Input/Keyboard.h"
#include "Level/World.h"
#include "Windows/WindowsWindow.h"
#include "Windows/DX/Renderer.h"

UI::TextBox::TextBox(const std::wstring& kName) :
    Widget(kName),
    text_(),
    color_(Math::Color::Black),
    font_size_(16.f),
    cursor_blink_time_(0.f),
    cursor_visible_(false)
{
}

void UI::TextBox::Tick(float delta_time)
{
    Widget::Tick(delta_time);

    Keyboard* keyboard = Keyboard::Get();

    if (keyboard->GetKeyDown(VK_BACK))
    {
        if (!text_.empty())
        {
            text_.pop_back();
        }
    }
    else text_ += keyboard->GetInputString();

    cursor_blink_time_ += delta_time;
    if (cursor_blink_time_ >= .5f)
    {
        cursor_blink_time_ = 0.f;
        cursor_visible_ = !cursor_visible_;
    }
}

void UI::TextBox::Render()
{
    WindowsWindow* window = World::Get()->GetWindow();
    if (!window) return;

    Renderer* renderer = Renderer::Get();
    if (!renderer) return;
    
    Math::Vector2 pivot_position = GetPivotPosition();
    if (GetParent()) pivot_position = GetParent()->GetPivotPosition();

    std::wstring text = text_;
    if (cursor_visible_) text += L"|";

    renderer->DrawBox(window, rect_, pivot_position, Math::Color::White, angle_);
    renderer->DrawString(window, text, rect_, pivot_position, color_, angle_, font_size_, DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
}
