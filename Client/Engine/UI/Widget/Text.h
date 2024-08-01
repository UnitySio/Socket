#pragma once
#include "Math/Color.h"
#include "UI/Widget.h"

namespace UI
{
    class Text : public Widget
    {
    public:
        Text(const std::wstring& kName);
        virtual ~Text() override = default;

        virtual void Render() override;

        inline void SetText(const std::wstring& kText) { text_ = kText; }
        inline void SetColor(const Math::Color& kColor) { color_ = kColor; }
        inline void SetFontSize(float kFontSize) { font_size_ = kFontSize; }

    private:
        std::wstring text_;

        Math::Color color_;

        float font_size_;
    
    };
}
