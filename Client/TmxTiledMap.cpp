#include "TmxTiledMap.h"
#include "tmxlite/Config.hpp"
#include "tmxlite/Tileset.hpp"
#include "tmxlite/Layer.hpp"
#include "Windows/DX/Texture.h"
#include "tmxlite/TileLayer.hpp"
#include "Windows/DX/Shape.h"
#include "Engine/Level/World.h"


TmxTiledMap::TmxTiledMap(const char* kPath, Actor* owner, const std::wstring& kName)
	:ActorComponent(owner, kName)
{
    
    map_.load(kPath);
    shape_ = MAKE_SHARED<Shape>();
    Load();
}

TmxTiledMap::TmxTiledMap(Actor* owner, const std::wstring& kName)
    :ActorComponent(owner, kName)
{
}

void TmxTiledMap::Load()
{
    const auto& tilesets = map_.getTilesets();
    std::wstring tileset_path = std::wstring(tilesets[0].getImagePath().begin(), tilesets[0].getImagePath().end());

    tilemap_texture_ = MAKE_SHARED<Texture>();
    CHECK(tilemap_texture_->Load(tileset_path));


    const auto& layers = map_.getLayers();
    const auto& layer = layers[0]->getLayerAs<tmx::TileLayer>();
    const auto map_size = map_.getTileCount();
    const auto tile_size = map_.getTileSize();

    const auto& tileset = map_.getTilesets()[0];
    const auto& tile_ids = layer.getTiles();

    const auto tex_width = tilemap_texture_->GetWidth();
    const auto tex_height = tilemap_texture_->GetHeight();


    const auto tile_count_x = tex_width / tile_size.x;
    const auto tile_count_y = tex_height / tile_size.y;

    const auto u_normal = static_cast<float>(tile_size.x) / static_cast<float>(tex_width);
    const auto v_normal = static_cast<float>(tile_size.y) / static_cast<float>(tex_height);

    for (auto y = 0u; y < map_size.y; ++y)
    {
        for (auto x = 0u; x < map_size.x; ++x)
        {
            const auto idx = y * map_size.x + x;
            if (idx < tile_ids.size() && tile_ids[idx].ID >= tileset.getFirstGID() &&
                tile_ids[idx].ID < (tileset.getFirstGID() + tileset.getTileCount()))
            {
                auto id_index = (tile_ids[idx].ID - tileset.getFirstGID());
                float u = static_cast<float>(id_index % tile_count_x);
                float v = static_cast<float>(id_index / tile_count_x);
                u *= tile_size.x;
                v *= tile_size.y;

                u /= tex_width;
                v /= tex_height;

                const float tile_pos_x = static_cast<float>(x * tile_size.x);
                const float tile_pos_y = static_cast<float>(y * tile_size.y);

                DefaultVertex vertex = { {tile_pos_x, -tile_pos_y, 0.f}, {1.f, 1.f, 1.f, 1.f}, {u, v + v_normal} };
                vertices_.push_back(vertex);
                vertex = { {tile_pos_x + tile_size.x, -tile_pos_y, 0.f}, {1.f, 1.f, 1.f, 1.f}, {u + u_normal, v + v_normal} };
                vertices_.push_back(vertex);
                vertex = { {tile_pos_x, -tile_pos_y + tile_size.y, 0.f}, {1.f, 1.f, 1.f, 1.f}, {u, v} };
                vertices_.push_back(vertex);
                vertex = { {tile_pos_x + tile_size.x, -tile_pos_y + tile_size.y, 0.f}, {1.f, 1.f, 1.f, 1.f}, {u + u_normal, v} };
                vertices_.push_back(vertex);

                auto base_index = static_cast<MathTypes::uint32>(vertices_.size() - 4);
                indices_.push_back(base_index + 0);
                indices_.push_back(base_index + 1);
                indices_.push_back(base_index + 2);
                indices_.push_back(base_index + 2);
                indices_.push_back(base_index + 1);
                indices_.push_back(base_index + 3);
            }
        }
    }
}

void TmxTiledMap::Load(const char* kPath)
{
    map_.load(kPath);
    shape_ = MAKE_SHARED<Shape>();
    Load();
}

inline void TmxTiledMap::Render(float alpha)
{
    if (shape_ == nullptr) return;
    shape_->SetVertices(vertices_);
    shape_->SetIndices(indices_);
    shape_->SetTexture(tilemap_texture_);
    shape_->SetScale({ 0.01f, 0.01f });
    shape_->SetZOrder(1);
    World::Get()->AddShape(shape_);
}
