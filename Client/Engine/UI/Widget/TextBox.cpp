#include "pch.h"
#include "TextBox.h"

#include "Input/Keyboard.h"
#include "Level/World.h"
#include "Windows/WindowsWindow.h"
#include "Windows/DX/Renderer.h"

UI::TextBox::TextBox(const std::wstring& kName) :
    Widget(kName),
    text_(),
    cursor_position_(0),
    elapsed_(0.f),
    show_cursor_(false),
    advances_()
{
}

void UI::TextBox::Tick(float delta_time)
{
    Widget::Tick(delta_time);

    Keyboard* keyboard = Keyboard::Get();

    if (keyboard->GetKeyDown(VK_LEFT))
    {
        if (cursor_position_ > 0) cursor_position_--;
    }
    else if (keyboard->GetKeyDown(VK_RIGHT))
    {
        if (cursor_position_ < text_.size()) cursor_position_++;
    }
    else if (keyboard->GetKeyDown(VK_BACK))
    {
        if (text_.size() > 0 && cursor_position_ > 0)
        {
            text_.erase(cursor_position_ - 1, 1);
            cursor_position_--;
        }
    }
    else if (keyboard->GetKeyDown(VK_SPACE))
    {
        text_.insert(cursor_position_, L" ");
        cursor_position_++;
    }
    else if (keyboard->GetKeyDown(VK_HOME))
    {
        cursor_position_ = 0;
    }
    else if (keyboard->GetKeyDown(VK_END))
    {
        cursor_position_ = text_.size();
    }
    else if (keyboard->GetKeyDown(VK_DELETE))
    {
        if (text_.size() > 0 && cursor_position_ < text_.size())
        {
            text_.erase(cursor_position_, 1);
        }
    }
    else
    {
        text_.insert(cursor_position_, keyboard->GetInputString());
        cursor_position_ += keyboard->GetInputString().size();
    }

    elapsed_ += delta_time;
    if (elapsed_ >= .5f)
    {
        show_cursor_ = !show_cursor_;
        elapsed_ = 0.f;
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

    renderer->DrawBox(window, rect_, pivot_position, Math::Color::White, angle_);
    renderer->DrawString(window, text_, rect_, pivot_position, Math::Color::Black, angle_, 16.f, DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_CENTER, &advances_);

    if (show_cursor_)
    {
        float advance = 0.f;

        if (cursor_position_ - 1 < advances_.size())
        {
            for (int i = 0; i < cursor_position_; i++)
            {
                advance += advances_[i];
            }
        }
        
        Math::Vector2 cursor_position = Math::Vector2(rect_.x + advance + 1.f, rect_.y + 6.f);
        renderer->DrawLine(window, cursor_position, cursor_position + Math::Vector2(0.f, 18.f), Math::Color::Black);
    }
    
    advances_.clear();
}
