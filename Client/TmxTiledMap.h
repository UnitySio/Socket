#pragma once
#include "Actor/Component/ActorComponent.h"
#include <vector>
#include "Engine/Windows/DX/Vertex.h"
#include "Math/MathTypes.h"
#include "Misc/EngineMacros.h"
#include "tmxlite/Map.hpp"

class Shape;

class TmxTiledMap : public ActorComponent
{
public:
	TmxTiledMap(const char* kPath, class Actor* owner = nullptr, const std::wstring& kName = L"UnNamed");
	TmxTiledMap(class Actor* owner, const std::wstring& kName);

	void Load();
	void Load(const char* kPath);


private:
	virtual inline void Render(float alpha) override;

private:
	SHARED_PTR<class Texture> tilemap_texture_;
	tmx::Map map_;
	std::vector<DefaultVertex> vertices_;
	std::vector<MathTypes::uint32> indices_;
	
	SHARED_PTR<Shape> shape_;
	
	//SHARED_PTR<Shape> Render();

};

