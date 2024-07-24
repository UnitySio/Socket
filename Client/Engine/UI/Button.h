#pragma once
#include "UIBase.h"
#include "Misc/DelegateMacros.h"

DECLARE_DELEGATE(ButtonSignature);

namespace UI
{
    class Button : public UIBase
    {
    public:
        Button(const std::wstring& kName);
        virtual ~Button() override = default;
        
        ButtonSignature on_click;
        
    protected:
        virtual void Tick(float deltaTime) override;
        virtual void Render() override;
        
    };
}
