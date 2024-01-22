#pragma once

enum class KeyState : size_t
{
    kNone = 0,
    kDown,
    kPressed,
    kUp
};

enum class SceneType : size_t
{
    kDefault = 0,
    kEnd
};
