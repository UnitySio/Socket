﻿#pragma once
#include <Windows.h>

#include "Input/Mouse.h"

enum EventType
{
    kNone = 0,
    kWindowSize = (0x01<<0),
    kKeyPressed = (0x01<<1),
    kKeyReleased = (0x01<<2),
    kText = (0x01<<3),
    kMousePressed = (0x01<<4),
    kMouseReleased = (0x01<<5),
    kMouseMotion = (0x01<<6),
    kMouseWheel = (0x01<<7)
};

struct WindowEvent
{
    EventType type;
    int data1;
    int data2;
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

struct MouseButtonEvent
{
    EventType type;
    bool is_pressed;
    MouseButton button;
};

struct MouseMotionEvent
{
    EventType type;
    float x;
    float y;
};

struct MouseWheelEvent
{
    EventType type;
    float x;
    float y;
};

union Event
{
    MathTypes::uint32 type;
    WindowEvent window;
    KeyboardEvent key;
    TextEvent text;
    MouseButtonEvent button;
    MouseMotionEvent motion;
    MouseWheelEvent wheel;
};
