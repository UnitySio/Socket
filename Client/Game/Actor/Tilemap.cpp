#include "Tilemap.h"
#include "Actor/Component/TilemapComponent.h"

Tilemap::Tilemap(const std::wstring& kName) : Actor(kName)
{
    tilemap_component_ = CreateComponent<TilemapComponent>(L"Tilemap");
    //tilemap_component_->LoadAll(".\\Game_Data\\Tile\\demo.tmx");
    tilemap_component_->LoadMap(".\\Game_Data\\Tile\\Dummy.tmx");
    tilemap_component_->LoadTileLayerByName("Tile Layer 1", 5);
    // tilemap_component_->LoadTileLayerByName("Tile Layer 2");
    // tilemap_component_->LoadTileLayerByName("Tile Layer 3");
    //tilemap_component_->LoadImageLayerByName("Image Layer 1");
    tilemap_component_->GenerateBlockLayer();
}
 