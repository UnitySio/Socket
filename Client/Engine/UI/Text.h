#pragma once
#include "UIBase.h"

namespace UI
{
    class Text : public UIBase
    {
    public:
        Text(const std::wstring& kName);
        virtual ~Text() override = default;

        void SetText(const std::wstring& text) { text_ = text; }
        
    protected:
        virtual void Render() override;

    private:
        std::wstring text_;
        
    };
}
