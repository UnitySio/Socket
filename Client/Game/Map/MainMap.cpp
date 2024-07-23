#include "pch.h"
#include "MainMap.h"

#include "Actor/FollowCamera.h"
#include "Actor/Tilemap.h"
#include "Actor/Character/Player/PlayerController.h"
#include "Actor/Component/TransformComponent.h"
#include "Sio/Sio.h"
#include "UI/Canvas.h"
#include "UI/UIBase.h"


MainMap::MainMap(const std::wstring& kName) : Level(kName)
{
}

void MainMap::Load()
{
    std::shared_ptr<Actor> tilemap = std::make_shared<Tilemap>(L"Tilemap");
    AddActor(tilemap);

    std::shared_ptr<Actor> player = std::make_shared<PlayerController>(L"Player");
    AddActor(player);
    
    player->GetTransform()->SetRelativePosition({ 1.5f, 0.f });
    
    std::shared_ptr<Actor> camera = std::make_shared<FollowCamera>(L"FollowCamera");
    AddActor(camera);
    
    FollowCamera* follow_camera = dynamic_cast<FollowCamera*>(camera.get());
    follow_camera->SetFollow(player.get());
    
    std::shared_ptr<Sio> sio = std::make_shared<Sio>(L"Sio");
    AddActor(sio);
    sio->GetTransform()->SetRelativePosition({ -1.5f, 0.f });

    std::shared_ptr<UIBase> ui = std::make_shared<UIBase>();
    ui->SetPosition({0.f, 0.f});
    ui->SetSize({0.f, 0.f});
    
    Canvas::Get()->AddUI(ui);
    
}

