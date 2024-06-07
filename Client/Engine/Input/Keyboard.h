#pragma once
#include <Windows.h>

#include "Singleton.h"
#include "Math/MathTypes.h"
#include "Misc/DelegateMacros.h"

DECLARE_DELEGATE_RetVal(KeyDownDelegate, bool, WORD, MathTypes::uint32, bool);
DECLARE_DELEGATE_RetVal(KeyUpDelegate, bool, WORD, MathTypes::uint32);
DECLARE_DELEGATE_RetVal(KeyCharDelegate, bool, WCHAR);

class Keyboard : public Singleton<Keyboard>
{
public:
    Keyboard();
    virtual ~Keyboard() override = default;

private:
    friend class Core;
    
    bool ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result);
    bool OnKeyDown(WORD key_code, MathTypes::uint32 char_code, bool is_repeat);
    bool OnKeyUp(WORD key_code, MathTypes::uint32 char_code);
    bool OnKeyChar(WCHAR character);
    
    KeyDownDelegate key_down_delegate_;
    KeyUpDelegate key_up_delegate_;
    KeyCharDelegate key_char_delegate_;
    
};