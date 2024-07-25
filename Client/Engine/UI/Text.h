#pragma once
#include "UIBase.h"
#include "Math/Color.h"

namespace UI
{
    class Text : public UIBase
    {
    public:
        Text(const std::wstring& kName);
        virtual ~Text() override = default;

        inline void SetText(const std::wstring& text) { text_ = text; }
        inline void SetColor(const Math::Color& color) { color_ = color; }
        
    protected:
        virtual void Render() override;

        std::wstring text_;

        Math::Color color_;
        
    };
}
