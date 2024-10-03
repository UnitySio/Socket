#include "pch.h"
#include "Tilemap.h"
#include "Actor/Component/Tilemap/TilemapComponent.h"
#include "rttr/registration.h"
#include "rttr/detail/registration/registration_impl.h"

Tilemap::Tilemap(const std::wstring& kName) : Actor(kName)
{
    SetLayer(ActorLayer::kGround);
    
    tilemap_component_ = AddComponent<TilemapComponent>(L"Tilemap");
    tilemap_component_->LoadMap(".\\Game_Data\\Tile\\Dummy.tmx");
}

RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<Tilemap>(L"Tilemap")
        .constructor<const std::wstring&>();
}
 