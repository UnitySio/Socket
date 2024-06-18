﻿#include "TilemapComponent.h"

#include "TransformComponent.h"
#include "Actor/Actor.h"
#include "tmxlite/Tileset.hpp"
#include "tmxlite/Layer.hpp"
#include "Windows/DX/Texture.h"
#include "tmxlite/TileLayer.hpp"
#include "Windows/DX/Shape.h"
#include "box2d/box2d.h"
#include "Level/World.h"
#include "tmxlite/ImageLayer.hpp"



TilemapComponent::TilemapComponent(const char* kPath, Actor* owner, const std::wstring& kName) :
	ActorComponent(owner, kName),
	map_size_(Math::Vector2::Zero())
{
	map_.load(kPath);
	Load();
}

TilemapComponent::TilemapComponent(Actor* owner, const std::wstring& kName)
	:ActorComponent(owner, kName)
{
}

void TilemapComponent::LoadImageLayerByName(const char* kLayer, const int& order)
{
	const auto& layers = map_.getLayers();

	for (int i = 0; i < layers.size(); ++i)
	{
		auto&& name = layers[i]->getName();
		if (name == kLayer)
		{
			auto&& layer = layers[i]->getLayerAs<tmx::ImageLayer>();
			std::wstring imagePath = std::wstring(layer.getImagePath().begin(), layer.getImagePath().end());
		}
	}
}

void TilemapComponent::Load()
{
	const auto& layers = map_.getLayers();

	for (int i = 0; i < layers.size(); ++i)
	{
		auto&& name = layers[i]->getName();
		if (name == "Block")
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

void TilemapComponent::LoadMap(const char* kPath)
{
	map_.load(kPath);
	const auto& tilesets = map_.getTilesets();
	std::wstring tileset_path = std::wstring(tilesets[0].getImagePath().begin(), tilesets[0].getImagePath().end());
	tilemap_texture_ = MAKE_SHARED<Texture>();
	CHECK(tilemap_texture_->Load(tileset_path));

}

void TilemapComponent::LoadAll(const char* kPath)
{
	map_.load(kPath);
	const auto& tilesets = map_.getTilesets();
	std::wstring tileset_path = std::wstring(tilesets[0].getImagePath().begin(), tilesets[0].getImagePath().end());
	tilemap_texture_ = MAKE_SHARED<Texture>();
	CHECK(tilemap_texture_->Load(tileset_path));
	Load();
}

void TilemapComponent::LoadTileLayerByName(const char* kLayer, const int& order)
{
	
	const auto& layers = map_.getLayers();

	for (int i = 0; i < layers.size(); ++i)
	{
		auto&& name = layers[i]->getName();
		if (name == kLayer)
		{
			auto&& layer = layers[i]->getLayerAs<tmx::TileLayer>();
			DrawImageTile(layer, order);
		}
	}
}

void TilemapComponent::GenerateBlockLayer()
{
	const auto& layers = map_.getLayers();

	for (int i = 0; i < layers.size(); ++i)
	{
		auto&& name = layers[i]->getName();
		if (name == "Block")
		{
			auto&& layer = layers[i]->getLayerAs<tmx::ObjectGroup>();
			GeneratePhysics(layer);
		}
	}
}

inline void TilemapComponent::Render(float alpha)
{
	if (shape_.size() == 0) return;
	
	for (int i = 0; i < shape_.size(); ++i)
	{
		World::Get()->AddShape(shape_[i]);
	}
}

void TilemapComponent::DrawImageTile(tmx::TileLayer layer, const int& zOrder)
{
	const auto map_size = map_.getTileCount();
	map_size_ = { static_cast<float>(map_size.x), static_cast<float>(map_size.y) };

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
				auto temp = tileset.getTile(tile_ids[idx].ID)->imagePosition;
				//auto id_index = (tile_ids[idx].ID - tileset.getFirstGID());
				//float u = static_cast<float>(id_index % tile_count_x);
				//float v = static_cast<float>(id_index / tile_count_y);
				//u *= tile_size.x;
				//v *= tile_size.y;
				//
				//u /= tex_width;
				//v /= tex_height;
				float u = static_cast<float>(tileset.getTile(tile_ids[idx].ID)->imagePosition.x) / tex_width;
				float v = static_cast<float>(tileset.getTile(tile_ids[idx].ID)->imagePosition.y) / tex_height;

				const float tile_pos_x = static_cast<float>(x * tile_size.x);
				const float tile_pos_y = static_cast<float>(y * tile_size.y) + tile_size.y;

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
		}
	}


	if (vertices_.size() > VertexBufferSize)
	{
		int number = static_cast<int>(vertices_.size() / VertexBufferSize);
		int rest = vertices_.size() - VertexBufferSize * number;

		for (int i = 0; i < number + 1; ++i)
		{
			if (i == number)
			{
				std::vector<DefaultVertex> vertices;
				std::vector<MathTypes::uint32> indices;

				vertices.assign(vertices_.begin() + i * VertexBufferSize, vertices_.begin() + i * VertexBufferSize + rest);
				indices.assign(indices_.begin(), indices_.begin() + IndexBufferSize + rest * 6 / 4);

				SHARED_PTR<Shape> shape = MAKE_SHARED<Shape>();
				shape->SetVertices(vertices);
				shape->SetIndices(indices);
				shape->SetTexture(tilemap_texture_);
				shape->SetPosition(GetOwner()->GetTransform()->GetWorldLocation());
				shape->SetScale({ 1.f / PPU, 1.f / PPU }); // 1.f / PPU
				shape->SetPivot({ map_size_.x / 2.f, -(map_size_.y / 2.f) });
				shape->SetZOrder(zOrder);
				shape_.push_back(std::move(shape));
				break;
			}


			std::vector<DefaultVertex> vertices;
			std::vector<MathTypes::uint32> indices;
			vertices.assign(vertices_.begin() + i * VertexBufferSize, vertices_.begin() + (i + 1) * VertexBufferSize);
			indices.assign(indices_.begin(), indices_.begin() + IndexBufferSize);

			SHARED_PTR<Shape> shape = MAKE_SHARED<Shape>();
			shape->SetVertices(vertices);
			shape->SetIndices(indices);
			shape->SetTexture(tilemap_texture_);
			shape->SetPosition(GetOwner()->GetTransform()->GetWorldLocation());
			shape->SetScale({ 1.f / PPU, 1.f / PPU }); // 1.f / PPU
			shape->SetPivot({ map_size_.x / 2.f, -(map_size_.y / 2.f) });
			shape->SetZOrder(zOrder);
			shape_.push_back(std::move(shape));
		}
	}


	else
	{
		SHARED_PTR<Shape> shape = MAKE_SHARED<Shape>();
		shape->SetVertices(vertices_);
		shape->SetIndices(indices_);
		shape->SetTexture(tilemap_texture_);
		shape->SetPosition(GetOwner()->GetTransform()->GetWorldLocation());
		shape->SetScale({ 1.f / PPU, 1.f / PPU }); // 1.f / PPU
		shape->SetPivot({ map_size_.x / 2.f, -(map_size_.y / 2.f) });
		shape->SetZOrder(zOrder);
		shape_.push_back(std::move(shape));
	}
	//SHARED_PTR<Shape> shape = MAKE_SHARED<Shape>();
	//shape->SetVertices(vertices_);
	//shape->SetIndices(indices_);
	//shape->SetTexture(tilemap_texture_);
	//shape->SetPosition(GetOwner()->GetTransform()->GetWorldLocation());
	//shape->SetScale({ 1.f / PPU, 1.f / PPU }); // 1.f / PPU
	//shape->SetPivot({ map_size_.x / 2.f, -(map_size_.y / 2.f) });
	//shape->SetZOrder(zOrder);
	//shape_.push_back(std::move(shape));
}

void TilemapComponent::GeneratePhysics(tmx::ObjectGroup object)
{
	auto&& objects = object.getObjects();

	for (int i = 0; i < objects.size(); ++i)
	{
		auto&& temp = objects.at(i);
		b2BodyDef bodyDef;
		//bodyDef.position.Set(temp.getAABB().left, temp.getAABB().top);
		bodyDef.position.Set(temp.getPosition().x / PPU + ((temp.getAABB().width / 2) / PPU) - map_size_.x / 2.f, -1 * temp.getPosition().y / PPU - ((temp.getAABB().height / 2) / PPU) + map_size_.y / 2.f);
		bodyDef.type = b2_staticBody;

		b2PolygonShape shape;
		shape.SetAsBox(temp.getAABB().width / 2 / PPU, temp.getAABB().height / 2 / PPU);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;

		b2Body* body = World::Get()->physics_world_->CreateBody(&bodyDef);
		body->CreateFixture(&fixtureDef);
	}
}
