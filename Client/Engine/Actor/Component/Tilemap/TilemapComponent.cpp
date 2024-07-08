#include "TilemapComponent.h"

#include "Actor/Actor.h"
#include "Actor/Component/TransformComponent.h"
#include "tmxlite/Tileset.hpp"
#include "tmxlite/Layer.hpp"
#include "Windows/DX/Texture.h"
#include "tmxlite/TileLayer.hpp"
#include "box2d/box2d.h"
#include "Level/World.h"
#include "tmxlite/ImageLayer.hpp"

TilemapComponent::TilemapComponent(Actor* owner, const std::wstring& kName) :
	ActorComponent(owner, kName),
	tilemap_layers_(),
	tilemap_body_(nullptr)
{
}

void TilemapComponent::InitializeComponent()
{
	ActorComponent::InitializeComponent();

	if (tilemap_body_) tilemap_body_->SetEnabled(true);
}

void TilemapComponent::UninitializeComponent()
{
	ActorComponent::UninitializeComponent();

	if (tilemap_body_) World::Get()->physics_world_->DestroyBody(tilemap_body_);
}

void TilemapComponent::Render(float alpha)
{
	ActorComponent::Render(alpha);

	for (const auto& tilemap_layer : tilemap_layers_)
	{
		tilemap_layer->AddShapes(
			GetOwner()->GetTransform()->GetWorldPosition(),
			{ 1.f / PPU, 1.f / PPU },
			{ map_size_.x / 2.f, -(map_size_.y / 2.f) }
		);
	}
}

void TilemapComponent::LoadMap(const char* kPath)
{
	map_.load(kPath);

	map_size_.x = static_cast<float>(map_.getTileCount().x);
	map_size_.y = static_cast<float>(map_.getTileCount().y);
	
	const auto& tilesets = map_.getTilesets();
	std::wstring tileset_path = std::wstring(tilesets[0].getImagePath().begin(), tilesets[0].getImagePath().end());
	
	tilemap_texture_ = MAKE_SHARED<Texture>();
	CHECK(tilemap_texture_->Load(tileset_path));
	
	const auto& layers = map_.getLayers();
	for (const auto& layer : layers)
	{
		if (layer->getType() == tmx::Layer::Type::Object)
		{
			const auto& object = layer->getLayerAs<tmx::ObjectGroup>();
			GeneratePhysics(object);
		}
		else if (layer->getType() == tmx::Layer::Type::Tile)
		{
			const auto& tile_layer = layer->getLayerAs<tmx::TileLayer>();
			
			Math::Vector2 chunk_size = {512.f, 512.f};
			tilemap_layers_.emplace_back(MAKE_UNIQUE<TilemapLayer>(map_, tile_layer, tilemap_texture_, chunk_size));
		}
	}
}

void TilemapComponent::GeneratePhysics(const tmx::ObjectGroup& object)
{
	const auto& objects = object.getObjects();

	b2BodyDef body_def;
	body_def.userData.pointer = reinterpret_cast<uintptr_t>(GetOwner());
	
	tilemap_body_ = World::Get()->physics_world_->CreateBody(&body_def);

	for (const auto& temp : objects)
	{
		b2PolygonShape shape;
		
		if (temp.getShape() == tmx::Object::Shape::Rectangle)
		{
			shape.SetAsBox(
				temp.getAABB().width / 2 / PPU, temp.getAABB().height / 2 / PPU,
				{temp.getPosition().x / PPU + ((temp.getAABB().width / 2) / PPU) - map_size_.x / 2.f, -1 * temp.getPosition().y / PPU - ((temp.getAABB().height / 2) / PPU) + map_size_.y / 2.f},
				0.f
			);
		}
		else if (temp.getShape() == tmx::Object::Shape::Polygon)
		{
			std::vector<b2Vec2> vertices;
			
			for (const auto& point : temp.getPoints())
			{
				b2Vec2 vertex = {point.x / PPU + temp.getPosition().x / PPU - map_size_.x / 2.f, -1 * point.y / PPU - temp.getPosition().y / PPU + map_size_.y / 2.f};
				vertices.push_back(vertex);
			}

			shape.Set(vertices.data(), vertices.size());
		}
		
		b2Filter filter;
		filter.categoryBits = GetOwner()->GetLayer();
		filter.maskBits = ProjectSettings::kLayerCollisionMatrix.at(GetOwner()->GetLayer());
		
		b2FixtureDef fixture_def;
		fixture_def.shape = &shape;
		fixture_def.filter = filter;
		
		tilemap_body_->CreateFixture(&fixture_def);
	}

	tilemap_body_->SetEnabled(false);
}
