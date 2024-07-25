#include "pch.h"
#include "TextBox.h"

#include "Input/Keyboard.h"
#include "Level/World.h"
#include "Math/Color.h"
#include "Windows/WindowsWindow.h"
#include "Windows/DX/Renderer.h"

UI::TextBox::TextBox(const std::wstring& kName) :
    UIBase(kName),
    text_(),
    text_rect_(),
    cursor_position_()
{
}

void UI::TextBox::Tick(float deltaTime)
{
    UIBase::Tick(deltaTime);
    if (!is_focused_) return;

    static float text_rect_x = 0.f;
    
    WindowsWindow* window = World::Get()->GetWindow();
    Math::Vector2 text_size = Math::Vector2::Zero();
    Renderer::Get()->GetStringSize(window, text_, 24.f, text_size);

    text_rect_ = {
        rect_.x + text_rect_x,
        rect_.y,
        text_size.x + text_size.x / text_.size(),
        rect_.height
    };

    Keyboard* keyboard = Keyboard::Get();
    if (keyboard->IsKeyPressed(VK_BACK))
    {
        if (!text_.empty() && cursor_position_ > 0)
        {
            text_.erase(cursor_position_ - 1, 1);
            cursor_position_--;

            if (text_size.x > rect_.width && text_rect_x < 0.f)
            {
                text_rect_x += text_size.x / text_.size();
            }
        }
    }
    else if (keyboard->IsKeyPressed(VK_LEFT))
    {
        if (cursor_position_ > 0)
        {
            cursor_position_--;

            if (rect_.x + text_rect_x + cursor_position_ * (text_size.x / text_.size()) < rect_.x)
            {
                text_rect_x += text_size.x / text_.size();
            }
        }
    }
    else if (keyboard->IsKeyPressed(VK_RIGHT))
    {
        if (cursor_position_ < text_.size())
        {
            cursor_position_++;
            
            if (rect_.x + text_rect_x + cursor_position_ * (text_size.x / text_.size()) > rect_.x + rect_.width)
            {
                text_rect_x -= text_size.x / text_.size();
            }
        }
    }
    else
    {
        std::wstring input_string = keyboard->GetInputString();
        if (!input_string.empty())
        {
            text_.insert(cursor_position_, input_string);
            cursor_position_ += input_string.size();

            if (text_size.x > rect_.width)
            {
                text_rect_x -= text_size.x / text_.size();
            }
        }
    }
}

void UI::TextBox::Render()
{
    WindowsWindow* window = World::Get()->GetWindow();
    Math::Vector2 text_size = Math::Vector2::Zero();
    Renderer::Get()->GetStringSize(window, text_, 24.f, text_size);

    Renderer* renderer = Renderer::Get();
    renderer->DrawBox(window, rect_, pivot_, Math::Color::Black);

    renderer->BeginLayer(rect_);
    renderer->DrawString(window, text_, text_rect_, pivot_, Math::Color::White);

    if (is_focused_)
    {
        float cursor_x = text_rect_.x + cursor_position_ * (text_size.x / text_.size());
        renderer->DrawLine(window, { cursor_x, rect_.y }, { cursor_x, rect_.y + rect_.height }, Math::Color::White);
    }
    
    renderer->EndLayer();
    
    UIBase::Render();
}
