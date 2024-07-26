#pragma once
#include "UIBase.h"

namespace UI
{
    class ScrollBox : public UIBase
    {
    public:
        ScrollBox(const std::wstring& kName);
        virtual ~ScrollBox() override = default;

    protected:
        virtual void Tick(float deltaTime) override;
        virtual void Render() override;

    private:
        Math::Rect content_rect_;
        Math::Rect scroll_bar_;
        Math::Rect scroll_bar_thumb_;

        bool is_dragging_;

        float scroll_offset_;
        
    };
}
