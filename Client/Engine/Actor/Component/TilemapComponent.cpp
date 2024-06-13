#include "TilemapComponent.h"

#include "TransformComponent.h"
#include "Actor/Actor.h"
#include "tmxlite/Tileset.hpp"
#include "tmxlite/Layer.hpp"
#include "Windows/DX/Texture.h"
#include "tmxlite/TileLayer.hpp"
#include "Windows/DX/Shape.h"
#include "box2d/box2d.h"
#include "Level/World.h"


TilemapComponent::TilemapComponent(const char* kPath, Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName),
    map_size_(Math::Vector2::Zero())
{
    map_.load(kPath);
    shape_ = MAKE_SHARED<Shape>();
    Load();
}

TilemapComponent::TilemapComponent(Actor* owner, const std::wstring& kName)
    :ActorComponent(owner, kName)
{
}

void TilemapComponent::Load()
{
    const auto& tilesets = map_.getTilesets();
    std::wstring tileset_path = std::wstring(tilesets[0].getImagePath().begin(), tilesets[0].getImagePath().end());

    tilemap_texture_ = MAKE_SHARED<Texture>();
    CHECK(tilemap_texture_->Load(tileset_path));

    const auto& layers = map_.getLayers();

    for (int i = 0; i < layers.size(); ++i)
    {
        auto&& name = layers[i]->getName();
        if (name == "Physics")
        {
            auto&& layer = layers[i]->getLayerAs<tmx::ObjectGroup>();            
            GeneratePhysics(layer);
        }
        else
        {
            const auto& layer = layers[i]->getLayerAs<tmx::TileLayer>();
            DrawImageTile(layer);
        }
    }
}

void TilemapComponent::Load(const char* kPath)
{
    map_.load(kPath);
    shape_ = MAKE_SHARED<Shape>();
    Load();
}

inline void TilemapComponent::Render(float alpha)
{
    if (shape_ == nullptr) return;
    shape_->SetVertices(vertices_);
    shape_->SetIndices(indices_);
    shape_->SetTexture(tilemap_texture_);
    shape_->SetPosition(GetOwner()->GetTransform()->GetWorldLocation());
    shape_->SetRotation(GetOwner()->GetTransform()->GetWorldRotationZ());
    shape_->SetScale({1.f / 64.f, 1.f / 64.f}); // 1.f / PPU
    shape_->SetPivot({map_size_.x / 2.f, -(map_size_.y / 2.f)});
    shape_->SetZOrder(1);
    World::Get()->AddShape(shape_);
}

void TilemapComponent::DrawImageTile(tmx::TileLayer layer)
{
    const auto map_size = map_.getTileCount();
    map_size_ = {static_cast<float>(map_size.x), static_cast<float>(map_size.y)};
    
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
                const float tile_pos_y = static_cast<float>(y * tile_size.y) + tile_size.y;

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

void TilemapComponent::GeneratePhysics(tmx::ObjectGroup object)
{
    auto&& objects = object.getObjects();
    
    for (int i = 0; i < objects.size(); ++i)
    {
        auto&& temp = objects.at(i);
        b2BodyDef bodyDef;
        //bodyDef.position.Set(temp.getAABB().left, temp.getAABB().top);
        bodyDef.position.Set(temp.getPosition().x * 0.02f, temp.getPosition().y * -0.01f);
        bodyDef.type = b2_staticBody;

        b2PolygonShape shape;
        shape.SetAsBox(temp.getAABB().width / 2 * 0.01f, temp.getAABB().height / 2 * 0.01f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;

        b2Body* body = World::Get()->physics_world_->CreateBody(&bodyDef);
        body->CreateFixture(&fixtureDef);
    }
}
