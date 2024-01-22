#pragma once

enum class KeyState : size_t;

struct Key
{
    KeyState state;
    bool is_down;
};
