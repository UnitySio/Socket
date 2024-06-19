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

class Shape;

class TilemapComponent : public ActorComponent
{
    const float PPU = 32.f;
    const MathTypes::uint32 VertexBufferSize = 2048;
    const MathTypes::uint32 IndexBufferSize = 2048 * 6 / 4;
public:
    TilemapComponent(const char* kPath, class Actor* owner = nullptr, const std::wstring& kName = L"UnNamed");
    TilemapComponent(class Actor* owner, const std::wstring& kName);

    void LoadMap(const char* kPath);
    void LoadAll(const char* kPath);
    /// <summary>
    /// You should call LoadMap function before call this
    /// </summary>
    /// <param name="kLayer"></param>
    void LoadTileLayerByName(const char* kLayer, const int& order = 1);
    /// <summary>
    /// You should call LoadMap function before call this
    /// </summary>
    /// <param name="kLayer"></param>
    void GenerateBlockLayer();
    /// <summary>
    /// You should call LoadMap function before call this *Not Supported Yet
    /// </summary>
    /// <param name="kLayer"></param>
    void LoadImageLayerByName(const char* kLayer, const int& order = 1);

    void CreateChunks(const tmx::TileLayer& layer);

private:
    void Load();
    virtual inline void Render(float alpha) override;
    void DrawImageTile(tmx::TileLayer layer, const int& zOrder = 1);
    void GeneratePhysics(tmx::ObjectGroup object);

private:
    SHARED_PTR<class Texture> tilemap_texture_;
    tmx::Map map_;
    std::vector<DefaultVertex> vertices_;
    std::vector<MathTypes::uint32> indices_;
    std::vector<SHARED_PTR<Shape>> shape_;
    Math::Vector2 map_size_;

private:
    Math::Vector2 chunk_size_;
    Math::Vector2 chunk_count_;

    std::vector<UNIQUE_PTR<TilemapChunk>> chunks_;
    
};

