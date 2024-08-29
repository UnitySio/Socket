#pragma once

enum class LevelType : MathTypes::uint64
{
    kSplash = 0,
    kMainMenu,
    kDefault,
    kEnd
};

enum class EndPlayReason : MathTypes::uint64
{
    kDestroyed,
    kLevelTransition,
    kQuit
};
