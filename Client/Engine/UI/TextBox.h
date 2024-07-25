#pragma once
#include "UIBase.h"

namespace UI
{
    class TextBox : public UIBase
    {
    public:
        TextBox(const std::wstring& kName);
        virtual ~TextBox() override = default;

        virtual void Tick(float deltaTime) override;
        virtual void Render() override;

    private:
        std::wstring text_;

        Math::Rect text_rect_;

        MathTypes::uint32 cursor_position_;
    
    };
}
