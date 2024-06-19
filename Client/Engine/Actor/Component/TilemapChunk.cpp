﻿#include "TilemapChunk.h"

#include "Windows/DX/Texture.h"

TilemapChunk::TilemapChunk(const tmx::TileLayer& layer, const tmx::Tileset* tileset, const Math::Vector2& position, const Math::Vector2& tile_count, const Math::Vector2& tile_size, size_t row_size, Texture* texture) :
    texture_(texture),
    chunk_tile_ids_(),
    vertices_(),
    indices_()
{
    MathTypes::uint32 pos_x = static_cast<MathTypes::uint32>(position.x / tile_size.x);
    MathTypes::uint32 pos_y = static_cast<MathTypes::uint32>(position.y / tile_size.y);

    for (MathTypes::uint32 y = pos_y; y < pos_y + tile_count.y; ++y)
    {
        for (MathTypes::uint32 x = pos_x; x < pos_x + tile_count.x; ++x)
        {
            MathTypes::uint32 idx = y * row_size + x;
            chunk_tile_ids_.push_back(layer.getTiles()[idx]);
        }
    }

    GenerateTiles(tileset, pos_x, pos_y, tile_count, tile_size);
}

void TilemapChunk::GenerateTiles(const tmx::Tileset* tileset, const MathTypes::uint32& pos_x, const MathTypes::uint32& pos_y, Math::Vector2 tile_count, const Math::Vector2& tile_size)
{
    MathTypes::uint32 idx = 0;
    MathTypes::uint32 tex_width = texture_->GetWidth();
    MathTypes::uint32 tex_height = texture_->GetHeight();

    const float u_normal = tile_size.x / tex_width;
    const float v_normal = tile_size.y / tex_height;
    
    for (MathTypes::uint32 y = pos_y; y < pos_y + tile_count.y; ++y)
    {
        for (MathTypes::uint32 x = pos_x; x < pos_x + tile_count.x; ++x)
        {
            if (idx < chunk_tile_ids_.size() && chunk_tile_ids_[idx].ID >= tileset->getFirstGID() &&
                chunk_tile_ids_[idx].ID < (tileset->getFirstGID() + tileset->getTileCount()))
            {
                MathTypes::uint32 id_idx = chunk_tile_ids_[idx].ID - tileset->getFirstGID();
                float u = static_cast<float>(id_idx % static_cast<MathTypes::uint32>(tile_count.x));
                float v = static_cast<float>(id_idx / static_cast<MathTypes::uint32>(tile_count.x));
                u *= tile_size.x;
                v *= tile_size.y;

                u /= tex_width;
                v /= tex_height;

                const float tile_pos_x = static_cast<float>(x) * tile_size.x;
                const float tile_pos_y = static_cast<float>(y) * tile_size.y + tile_size.y;
                
                DefaultVertex vertex = { {tile_pos_x, -tile_pos_y, 0.f}, {1.f, 1.f, 1.f, 1.f}, {u, v + v_normal} };
                vertices_.push_back(vertex);
                vertex = { {tile_pos_x + tile_size.x, -tile_pos_y, 0.f}, {1.f, 1.f, 1.f, 1.f}, {u + u_normal, v + v_normal } };
                vertices_.push_back(vertex);
                vertex = { {tile_pos_x, -tile_pos_y + tile_size.y, 0.f}, {1.f, 1.f, 1.f, 1.f}, {u, v } };
                vertices_.push_back(vertex);
                vertex = { {tile_pos_x + tile_size.x, -tile_pos_y + tile_size.y, 0.f}, {1.f, 1.f, 1.f, 1.f}, {u + u_normal, v } };
                vertices_.push_back(vertex);

                auto base_index = static_cast<MathTypes::uint32>(vertices_.size() - 4);
                indices_.push_back(base_index + 0);
                indices_.push_back(base_index + 1);
                indices_.push_back(base_index + 2);
                indices_.push_back(base_index + 2);
                indices_.push_back(base_index + 1);
                indices_.push_back(base_index + 3);
            }

            ++idx;
        }
    }
}
