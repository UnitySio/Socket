#pragma once
#include "Math/MathTypes.h"
#include "tmxlite/Map.hpp"
#include "Math/Vector2.h"
#include "Misc/EngineMacros.h"
#include "tmxlite/TileLayer.hpp"
#include "Windows/DX/Vertex.h"

class Texture;

class TilemapChunk
{
public:
    TilemapChunk(const tmx::TileLayer& kLayer, const tmx::Tileset* kTileset, const Math::Vector2& kPosition, const Math::Vector2& kTileCount, const Math::Vector2& kTileSize, size_t row_size, const std::shared_ptr<Texture>& kTexture);

    void AddShape(const Math::Vector2& kPosition, const Math::Vector2& kScale, const Math::Vector2& kPivot = Math::Vector2::Zero());
    
    int GetTileIndex(int x, int y) const;

private:
    void GenerateTiles(const tmx::Tileset* kTileset, const MathTypes::uint32& kPosX, const MathTypes::uint32& kPosY, const Math::Vector2& kTileSize);

    Math::Vector2 tile_count_;
    
    std::shared_ptr<Texture> texture_;
    
    std::vector<tmx::TileLayer::Tile> chunk_tile_ids_;
    
    std::vector<DefaultVertex> vertices_;
    std::vector<MathTypes::uint32> indices_;

    std::shared_ptr<class Shape> shape_;
    
};
