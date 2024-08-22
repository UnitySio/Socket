﻿#include "pch.h"
#include "Tilemap.h"
#include "Actor/Component/Tilemap/TilemapComponent.h"

Tilemap::Tilemap(const std::wstring& kName) : Actor(kName)
{
    tilemap_component_ = CreateComponent<TilemapComponent>(L"Tilemap");
    tilemap_component_->LoadMap(".\\Game_Data\\Tile\\Dummy.tmx");
}
 