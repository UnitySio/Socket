#pragma once
#include "Math/MathTypes.h"

struct KeyState
{
    bool is_down;
    bool was_down;
};

class Keyboard
{
public:
    static void Process(MathTypes::uint32 vk_code, bool was_down, bool is_down);
    static bool IsKeyDown(MathTypes::uint32 key_code);
    static bool IsKeyPressed(MathTypes::uint32 key_code);
    static bool IsKeyUp(MathTypes::uint32 key_code);

    static KeyState keys[26];
    
};
