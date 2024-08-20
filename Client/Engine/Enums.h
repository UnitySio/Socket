#pragma once

enum class LevelType : size_t
{
    kSplash = 0,
    kMainMenu,
    kDefault,
    kEnd
};

enum class EndPlayReason : size_t
{
    kDestroyed,
    kLevelTransition,
    kQuit
};
