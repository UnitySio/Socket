#pragma once
#include "Math/Color.h"
#include "UI/Widget.h"

namespace UI
{
    class TextBox : public Widget
    {
    public:
        TextBox(const std::wstring& kName);
        virtual ~TextBox() override = default;

        virtual void Tick(float delta_time) override;
        virtual void Render() override;

        inline const std::wstring& GetText() const { return text_; }

    private:
        std::wstring text_;
        
        Math::Color color_;

        float font_size_;
        float cursor_blink_time_;

        bool cursor_visible_;
        
    };
}
