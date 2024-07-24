#include "pch.h"
#include "MainMap.h"

#include "Actor/FollowCamera.h"
#include "Actor/Tilemap.h"
#include "Actor/Character/Player/PlayerController.h"
#include "Actor/Component/TransformComponent.h"
#include "Level/World.h"
#include "Sio/Sio.h"
#include "UI/Button.h"
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

    ui = std::make_shared<UI::Text>(L"Text");
    ui->SetPosition({0.f, 0.f});
    ui->SetSize({100.f, 100.f});
    ui->SetAnchorPreset(AnchorPresets::kTop, true);
    ui->SetText(L"이방인");
    
    Canvas::Get()->AddUI(ui);

    std::shared_ptr<UI::Button> button = std::make_shared<UI::Button>(L"Button");
    button->SetPosition({ 0.f, 0.f });
    button->SetSize({ 180.f, 30.f });
    button->SetAnchorPreset(AnchorPresets::kLeft, true);
    button->on_click.Add(this, &MainMap::OnCallback);
    
    Canvas::Get()->AddUI(button);

    std::shared_ptr<UI::Text> text = std::make_shared<UI::Text>(L"ButtonText");
    text->SetPosition({ 0.f, 0.f });
    text->SetSize({ 0.f, 0.f });
    text->SetAnchorPreset(AnchorPresets::kStretch, true);
    text->SetColor(Math::Color::Black);
    text->SetText(L"다음 맵");
    text->AttachToUI(button.get());
    
    Canvas::Get()->AddUI(text);
    
}

void MainMap::Tick(float delta_time)
{
    Level::Tick(delta_time);

    Math::Vector2 position = player->GetTransform()->GetWorldPosition();
    position = Renderer::Get()->ConvertWorldToScreen(position);

    ui->SetPositionScreen(position);
}

void MainMap::OnCallback()
{
    World::Get()->OpenLevel(LevelType::kWorld);
}
