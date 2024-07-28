#pragma once
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
        virtual void OnMouseReleased() override;
        virtual void Render() override;
        
    };
}
