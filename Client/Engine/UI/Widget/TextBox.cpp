#include "pch.h"
#include "TextBox.h"

#include "Input/Keyboard.h"
#include "Level/World.h"
#include "Windows/WindowsWindow.h"
#include "Windows/DX/Renderer.h"

UI::TextBox::TextBox(const std::wstring& kName) :
    Widget(kName),
    text_area_(),
    text_(),
    placeholder_(),
    cursor_position_(0),
    elapsed_(0.f),
    show_cursor_(false),
    advances_()
{
}

void UI::TextBox::BeginPlay()
{
    Widget::BeginPlay();

    text_area_ = rect_;
}

void UI::TextBox::Tick(float delta_time)
{
    Widget::Tick(delta_time);
    if (!is_focused_) return;

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

    renderer->BeginLayer(rect_);

    if (text_.empty())
    {
        renderer->DrawString(window, placeholder_, text_area_, pivot_position, Math::Color::Gray, angle_, L"Nanum16", DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }
    else
    {
        renderer->DrawString(window, text_, text_area_, pivot_position, Math::Color::Black, angle_, L"Nanum16", DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }

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
        
        Math::Vector2 cursor_position = Math::Vector2(text_area_.x + advance + 1.f, text_area_.y + 6.f);
        renderer->DrawLine(window, cursor_position, cursor_position + Math::Vector2(0.f, 18.f), Math::Color::Black);
    }

    renderer->EndLayer();
}

void UI::TextBox::OnBlur()
{
    Widget::OnBlur();

    elapsed_ = 0.f;
    show_cursor_ = false;
}

void UI::TextBox::OnKeyEvent(MathTypes::uint16 key_code, bool is_pressed)
{
    Widget::OnKeyEvent(key_code, is_pressed);

    if (is_pressed)
    {
        if (key_code == VK_LEFT)
        {
            if (cursor_position_ > 0) cursor_position_--;
        }
        else if (key_code == VK_RIGHT)
        {
            if (cursor_position_ < text_.size()) cursor_position_++;
        }
        else if (key_code == VK_BACK)
        {
            if (text_.size() > 0 && cursor_position_ > 0)
            {
                text_.erase(cursor_position_ - 1, 1);
                cursor_position_--;
            }
        }
        else if (key_code == VK_SPACE)
        {
            text_.insert(cursor_position_, L" ");
            cursor_position_++;
        }
        else if (key_code == VK_HOME)
        {
            cursor_position_ = 0;
        }
        else if (key_code == VK_END)
        {
            cursor_position_ = text_.size();
        }
        else if (key_code == VK_DELETE)
        {
            if (text_.size() > 0 && cursor_position_ < text_.size())
            {
                text_.erase(cursor_position_, 1);
            }
        }
    }
}

void UI::TextBox::OnCharEvent(MathTypes::uint16 character)
{
    Widget::OnCharEvent(character);

    text_.insert(cursor_position_, 1, character);
    cursor_position_++;

    if (Renderer* renderer = Renderer::Get())
    {
        advances_.clear();
        renderer->GetTextAdvances(text_, L"Nanum16", advances_);
    }
}
