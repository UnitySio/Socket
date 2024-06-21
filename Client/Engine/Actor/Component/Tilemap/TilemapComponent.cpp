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
	tilemap_layers_()
{
}

void TilemapComponent::InitializeComponent()
{
	ActorComponent::InitializeComponent();

	for (const auto& body : bodies_)
	{
		body->SetEnabled(true);
	}
}

void TilemapComponent::UninitializeComponent()
{
	ActorComponent::UninitializeComponent();

	for (const auto& body : bodies_)
	{
		World::Get()->physics_world_->DestroyBody(body);
	}
}

void TilemapComponent::Render(float alpha)
{
	ActorComponent::Render(alpha);

	for (const auto& tilemap_layer : tilemap_layers_)
	{
		tilemap_layer->AddShapes(
			GetOwner()->GetTransform()->GetWorldLocation(),
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

	for (const auto& temp : objects)
	{
		b2BodyDef bodyDef;
		bodyDef.position.Set(temp.getPosition().x / PPU + ((temp.getAABB().width / 2) / PPU) - map_size_.x / 2.f, -1 * temp.getPosition().y / PPU - ((temp.getAABB().height / 2) / PPU) + map_size_.y / 2.f);
		bodyDef.type = b2_staticBody;

		b2PolygonShape shape;
		shape.SetAsBox(temp.getAABB().width / 2 / PPU, temp.getAABB().height / 2 / PPU);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;

		b2Body* body = World::Get()->physics_world_->CreateBody(&bodyDef);
		body->CreateFixture(&fixtureDef);

		body->SetEnabled(false);
		bodies_.push_back(body);
	}
}
