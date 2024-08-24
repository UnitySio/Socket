﻿#pragma once
#include "Actor/Component/ActorComponent.h"
#include <vector>
#include "Math/MathTypes.h"
#include "Math/Vector2.h"
#include "tmxlite/Map.hpp"

#include "TilemapChunk.h"
#include "TilemapLayer.h"
#include "box2d/id.h"

class Shape;

class TilemapComponent : public ActorComponent
{
    SHADER_CLASS_HELPER(TilemapComponent)
    
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

    std::shared_ptr<class Texture> tilemap_texture_;
    tmx::Map map_;
    Math::Vector2 map_size_;

    std::vector<std::unique_ptr<TilemapLayer>> tilemap_layers_;

    b2BodyId tilemap_body_id_;
    
};
