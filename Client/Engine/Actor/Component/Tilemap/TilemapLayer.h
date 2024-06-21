#pragma once
#include <vector>

#include "Math/Vector2.h"
#include "Misc/EngineMacros.h"
#include "tmxlite/Map.hpp"

class Texture;

class TilemapLayer
{
public:
    TilemapLayer(const tmx::Map& map, const tmx::TileLayer& layer, const SHARED_PTR<Texture>& texture, const Math::Vector2& chunk_size);
    ~TilemapLayer() = default;

    void AddShapes(const Math::Vector2& position, const Math::Vector2& scale, const Math::Vector2& pivot = Math::Vector2::Zero());

private:
    void CreateChunks(const tmx::Map& map, const tmx::TileLayer& layer, const SHARED_PTR<Texture>& texture, const Math::Vector2& tile_size);

    Math::Vector2 chunk_size_;
    Math::Vector2 chunk_count_;

    std::vector<UNIQUE_PTR<class TilemapChunk>> chunks_;
    
};
