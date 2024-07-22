#pragma once
#include "UIBase.h"

namespace UI
{
    class Text : public UIBase
    {
    public:
        Text();
        virtual ~Text() override = default;

        virtual void Render() override;

        inline void SetText(const std::wstring& text) { text_ = text; }

    private:
        std::wstring text_;
    
    };
}
