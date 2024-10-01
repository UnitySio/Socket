#pragma once
#include <Windows.h>

enum EventType
{
    kNone,
    kKeyPressed,
    kKeyReleased,
    kText
};

struct KeyboardEvent
{
    EventType type;
    WORD key_code;
    bool is_repeat;
};

struct TextEvent
{
    EventType type;
    wchar_t character;
};

union Event
{
    MathTypes::uint32 type;
    KeyboardEvent key;
    TextEvent text;
};
