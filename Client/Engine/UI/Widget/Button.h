#pragma once
#include "Math/Color.h"
#include "Misc/DelegateMacros.h"
#include "UI/Widget.h"

namespace UI
{
    DECLARE_DELEGATE(ButtonSignature);
    
    class Button : public Widget
    {
    public:
        Button(const std::wstring& kName);
        virtual ~Button() override = default;

        ButtonSignature on_click;

    protected:
        virtual void OnMousePressed() override;
        virtual void OnMouseReleased() override;
        virtual void OnMouseHover() override;
        virtual void OnMouseLeave() override;
        virtual void Render() override;

    private:
        Math::Color color_;
        
    };
}
