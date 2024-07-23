#include "pch.h"
#include "MainMap.h"

#include "Actor/FollowCamera.h"
#include "Actor/Tilemap.h"
#include "Actor/Character/Player/PlayerController.h"
#include "Actor/Component/TransformComponent.h"
#include "Sio/Sio.h"
#include "UI/Canvas.h"
#include "UI/Text.h"
#include "UI/UIBase.h"
#include "Windows/DX/Renderer.h"

MainMap::MainMap(const std::wstring& kName) : Level(kName)
{
}

void MainMap::Load()
{
    std::shared_ptr<Actor> tilemap = std::make_shared<Tilemap>(L"Tilemap");
    AddActor(tilemap);

    player = std::make_shared<PlayerController>(L"Player");
    AddActor(player);
    
    player->GetTransform()->SetRelativePosition({ 1.5f, 0.f });
    
    std::shared_ptr<Actor> camera = std::make_shared<FollowCamera>(L"FollowCamera");
    AddActor(camera);
    
    FollowCamera* follow_camera = dynamic_cast<FollowCamera*>(camera.get());
    follow_camera->SetFollow(player.get());
    
    std::shared_ptr<Sio> sio = std::make_shared<Sio>(L"Sio");
    AddActor(sio);
    sio->GetTransform()->SetRelativePosition({ -1.5f, 0.f });

    ui = std::make_shared<UI::Text>();
    ui->SetPosition({0.f, 0.f});
    ui->SetSize({100.f, 100.f});
    ui->SetAnchorPreset(AnchorPresets::kTop, true);
    ui->SetText(L"이방인");
    
    Canvas::Get()->AddUI(ui);
    
}

void MainMap::Tick(float delta_time)
{
    Level::Tick(delta_time);

    Math::Vector2 position = player->GetTransform()->GetWorldPosition();
    position = Renderer::Get()->ConvertWorldToScreen(position);

    ui->SetPositionScreen(position);
}

