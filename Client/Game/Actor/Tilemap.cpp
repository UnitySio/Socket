#include "Tilemap.h"
#include "Actor/Component/TilemapComponent.h"

Tilemap::Tilemap(const std::wstring& kName) : Actor(kName)
{
    tilemap_component_ = CreateComponent<TilemapComponent>(L"Tilemap");
    tilemap_component_->Load(".\\Game_Data\\Tile\\demo.tmx");
}
