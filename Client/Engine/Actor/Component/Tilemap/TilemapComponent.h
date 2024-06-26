#pragma once
#include "Actor/Component/ActorComponent.h"
#include <vector>
#include "Math/MathTypes.h"
#include "Math/Vector2.h"
#include "Misc/EngineMacros.h"
#include "tmxlite/Map.hpp"
#include "Windows/DX/Vertex.h"
#include "wrl.h"
#include <d3d11.h>

#include "TilemapChunk.h"
#include "TilemapLayer.h"

class Shape;

class TilemapComponent : public ActorComponent
{
    const float PPU = 32.f;
    const MathTypes::uint32 VertexBufferSize = 2048;
    const MathTypes::uint32 IndexBufferSize = 2048 * 6 / 4;
public:
    TilemapComponent(class Actor* owner, const std::wstring& kName);

    virtual void InitializeComponent() override;
    virtual void UninitializeComponent() override;
    virtual void Render(float alpha) override;

    void LoadMap(const char* kPath);

private:
    void GeneratePhysics(const tmx::ObjectGroup& object);

    SHARED_PTR<class Texture> tilemap_texture_;
    tmx::Map map_;
    Math::Vector2 map_size_;

    std::vector<UNIQUE_PTR<TilemapLayer>> tilemap_layers_;
    class b2Body* tilemap_body_;
    
};
