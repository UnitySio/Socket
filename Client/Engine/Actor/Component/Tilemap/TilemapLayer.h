#pragma once
#include <vector>

#include "Math/Vector2.h"
#include "Misc/EngineMacros.h"
#include "tmxlite/Map.hpp"

class TilemapChunk;
class Texture;

class TilemapLayer
{
public:
    TilemapLayer(const tmx::Map& map, const tmx::TileLayer& layer, const SHARED_PTR<Texture>& texture, const Math::Vector2& chunk_size);
    ~TilemapLayer() = default;

    void AddShapes(const Math::Vector2& position, const Math::Vector2& scale, const Math::Vector2& pivot = Math::Vector2::Zero());

    TilemapChunk* GetChunk(int tile_x, int tile_y);
    TilemapChunk* GetChunk(int tile_x, int tile_y, Math::Vector2& tile_relative_position);

private:
    void CreateChunks(const tmx::Map& map, const tmx::TileLayer& layer, const SHARED_PTR<Texture>& texture, const Math::Vector2& tile_size);

    Math::Vector2 chunk_size_;
    Math::Vector2 chunk_count_;
    Math::Vector2 map_tile_size_;

    std::vector<UNIQUE_PTR<TilemapChunk>> chunks_;
    
};
