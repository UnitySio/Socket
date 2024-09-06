#pragma once
#include <memory>
#include <vector>

#include "Math/Vector2.h"
#include "tmxlite/TileLayer.hpp"
#include "Windows/DX/Vertex.h"

namespace tmx
{
    class Tileset;
}

class Texture;

class TilemapChunk
{
public:
    TilemapChunk(const tmx::TileLayer& kLayer, const tmx::Tileset* kTileset, const Math::Vector2& kPosition, const Math::Vector2& kTileCount, const Math::Vector2& kTileSize, MathTypes::uint64 row_size, Texture* kTexture);

    void AddShape(const Math::Vector2& kPosition, const Math::Vector2& kScale, const Math::Vector2& kPivot = Math::Vector2::Zero());
    
    int GetTileIndex(int x, int y) const;

private:
    void GenerateTiles(const tmx::Tileset* kTileset, const MathTypes::uint32& kPosX, const MathTypes::uint32& kPosY, const Math::Vector2& kTileSize);

    Math::Vector2 tile_count_;
    
    Texture* texture_;
    
    std::vector<tmx::TileLayer::Tile> chunk_tile_ids_;
    
    std::vector<DefaultVertex> vertices_;
    std::vector<MathTypes::uint32> indices_;

    std::shared_ptr<class Shape> shape_;
    
};
