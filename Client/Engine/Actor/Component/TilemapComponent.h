#pragma once
#include "Actor/Component/ActorComponent.h"
#include <vector>
#include "Math/MathTypes.h"
#include "Math/Vector2.h"
#include "Misc/EngineMacros.h"
#include "tmxlite/Map.hpp"
#include "Windows/DX/Vertex.h"

class Shape;

class TilemapComponent : public ActorComponent
{
public:
	TilemapComponent(const char* kPath, class Actor* owner = nullptr, const std::wstring& kName = L"UnNamed");
	TilemapComponent(class Actor* owner, const std::wstring& kName);

	void Load();
	void Load(const char* kPath);

private:
	virtual inline void Render(float alpha) override;
	void DrawImageTile(tmx::TileLayer layer);
	void GeneratePhysics(tmx::ObjectGroup object);

private:
	SHARED_PTR<class Texture> tilemap_texture_;
	tmx::Map map_;
	std::vector<DefaultVertex> vertices_;
	std::vector<MathTypes::uint32> indices_;
	
	SHARED_PTR<Shape> shape_;
	
	//SHARED_PTR<Shape> Render();

	Math::Vector2 map_size_;

};

