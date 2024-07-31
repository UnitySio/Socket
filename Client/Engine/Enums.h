#pragma once

enum class LevelType : size_t
{
    kSplash = 0,
    kDefault,
    kEnd
};

enum class EventType : size_t
{
    kSpawnActor = 0,
    kDestroyActor,
    kActiveActor
};

enum class EndPlayReason : size_t
{
    kDestroyed,
    kLevelTransition,
    kQuit
};
