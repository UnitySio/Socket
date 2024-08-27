﻿#include "pch.h"
#include "TilemapChunk.h"

#include "Level/World.h"
#include "Windows/DX/Shape.h"
#include "Windows/DX/Texture.h"

TilemapChunk::TilemapChunk(const tmx::TileLayer& kLayer, const tmx::Tileset* kTileset, const Math::Vector2& kPosition, const Math::Vector2& kTileCount, const Math::Vector2& kTileSize, size_t row_size, const std::shared_ptr<Texture>& kTexture) :
    tile_count_(kTileCount),
    texture_(kTexture),
    chunk_tile_ids_(),
    vertices_(),
    indices_(),
    shape_(nullptr)
{
    MathTypes::uint32 pos_x = static_cast<MathTypes::uint32>(kPosition.x / kTileSize.x);
    MathTypes::uint32 pos_y = static_cast<MathTypes::uint32>(kPosition.y / kTileSize.y);

    for (MathTypes::uint32 y = pos_y; y < pos_y + kTileCount.y; ++y)
    {
        for (MathTypes::uint32 x = pos_x; x < pos_x + kTileCount.x; ++x)
        {
            MathTypes::uint32 idx = y * row_size + x;
            chunk_tile_ids_.push_back(kLayer.getTiles()[idx]);
        }
    }

    GenerateTiles(kTileset, pos_x, pos_y, kTileSize);
}

void TilemapChunk::AddShape(const Math::Vector2& kPosition, const Math::Vector2& kScale, const Math::Vector2& kPivot)
{
    shape_->SetPosition(kPosition);
    shape_->SetScale(kScale);
    shape_->SetPivot(kPivot);

    World::Get()->AddShape(shape_);
}

int TilemapChunk::GetTileIndex(int x, int y) const
{
    return y * tile_count_.x + x;
}

void TilemapChunk::GenerateTiles(const tmx::Tileset* kTileset, const MathTypes::uint32& kPosX, const MathTypes::uint32& kPosY, const Math::Vector2& kTileSize)
{
    MathTypes::uint32 idx = 0;
    MathTypes::uint32 tex_width = texture_->GetWidth();
    MathTypes::uint32 tex_height = texture_->GetHeight();

    const Math::Vector2 ts_tile_size = {static_cast<float>(kTileset->getTileSize().x), static_cast<float>(kTileset->getTileSize().y)};
    const Math::Vector2 ts_tile_count = {tex_width / ts_tile_size.x, tex_height / ts_tile_size.y};

    const float u_normal = ts_tile_size.x / tex_width;
    const float v_normal = ts_tile_size.y / tex_height;
    
    for (MathTypes::uint32 y = kPosY; y < kPosY + tile_count_.y; ++y)
    {
        for (MathTypes::uint32 x = kPosX; x < kPosX + tile_count_.x; ++x)
        {
            if (idx < chunk_tile_ids_.size() && chunk_tile_ids_[idx].ID >= kTileset->getFirstGID() &&
                chunk_tile_ids_[idx].ID <= kTileset->getLastGID())
            {
                MathTypes::uint32 id_idx = chunk_tile_ids_[idx].ID - kTileset->getFirstGID();
                float u = static_cast<float>(id_idx % static_cast<MathTypes::uint32>(ts_tile_count.x));
                float v = static_cast<float>(id_idx / static_cast<MathTypes::uint32>(ts_tile_count.x));
                u *= ts_tile_size.x;
                v *= ts_tile_size.y;

                u /= tex_width;
                v /= tex_height;

                const float tile_pos_x = static_cast<float>(x) * kTileSize.x;
                const float tile_pos_y = static_cast<float>(y) * kTileSize.y + kTileSize.y;
                
                DefaultVertex vertex = { {tile_pos_x, -tile_pos_y, 0.f}, {1.f, 1.f, 1.f, 1.f}, {u, v + v_normal} };
                vertices_.push_back(vertex);
                vertex = { {tile_pos_x + ts_tile_size.x, -tile_pos_y, 0.f}, {1.f, 1.f, 1.f, 1.f}, {u + u_normal, v + v_normal } };
                vertices_.push_back(vertex);
                vertex = { {tile_pos_x, -tile_pos_y + ts_tile_size.y, 0.f}, {1.f, 1.f, 1.f, 1.f}, {u, v } };
                vertices_.push_back(vertex);
                vertex = { {tile_pos_x + ts_tile_size.x, -tile_pos_y + ts_tile_size.y, 0.f}, {1.f, 1.f, 1.f, 1.f}, {u + u_normal, v } };
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

    shape_ = std::make_shared<Shape>();
    shape_->SetVertices(vertices_);
    shape_->SetIndices(indices_);
    shape_->SetTexture(texture_);
}
