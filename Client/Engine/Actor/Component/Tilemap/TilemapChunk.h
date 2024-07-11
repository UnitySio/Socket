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
    TilemapChunk(const tmx::TileLayer& layer, const tmx::Tileset* tileset, const Math::Vector2& position, const Math::Vector2& tile_count, const Math::Vector2& tile_size, size_t row_size, const std::shared_ptr<Texture>& texture);

    void AddShape(const Math::Vector2& position, const Math::Vector2& scale, const Math::Vector2& pivot = Math::Vector2::Zero());
    
    int GetTileIndex(int x, int y) const;

private:
    void GenerateTiles(const tmx::Tileset* tileset, const MathTypes::uint32& pos_x, const MathTypes::uint32& pos_y, const Math::Vector2& tile_size);

    Math::Vector2 tile_count_;
    
    std::shared_ptr<Texture> texture_;
    
    std::vector<tmx::TileLayer::Tile> chunk_tile_ids_;
    
    std::vector<DefaultVertex> vertices_;
    std::vector<MathTypes::uint32> indices_;

    std::shared_ptr<class Shape> shape_;
    
};
