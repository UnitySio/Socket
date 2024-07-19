﻿#pragma once

enum class LevelType : size_t
{
    kDefault = 0,
    kWorld = 1,
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
    kLevelTransition,
    kQuit
};
