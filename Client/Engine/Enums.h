#pragma once

enum class KeyState : size_t
{
    kNone = 0,
    kDown,
    kPressed,
    kUp
};

enum class LevelType : size_t
{
    kDefault = 0,
    kEnd
};

enum class EventType : size_t
{
    kSpawnActor = 0,
    kDestroyActor,
    kActiveActor,
    kLevelTransition
};

enum class EndPlayReason : size_t
{
    kDestroyed,
    kLevelTransition
};
