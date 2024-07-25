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
#include "UI/ScrollBox.h"
#include "UI/Slider.h"
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

    std::shared_ptr<UI::ScrollBox> scroll_box = std::make_shared<UI::ScrollBox>(L"ScrollBox");
    scroll_box->SetPosition({ 0.f, 0.f });
    scroll_box->SetSize({ 180.f, 200.f });
    scroll_box->SetAnchorPreset(AnchorPresets::kLeft, true);

    Canvas::Get()->AddUI(scroll_box);

    std::shared_ptr<UI::Button> button = std::make_shared<UI::Button>(L"Button");
    button->SetPosition({ 0.f, 0.f });
    button->SetSize({ 180.f, 30.f });
    button->SetAnchorPreset(AnchorPresets::kLeft, true);
    button->AttachToUI(scroll_box.get());
    button->on_click.Add([]()
    {
        Renderer::Get()->ChangeResolution(World::Get()->GetWindow(), 640, 480);
    });
    
    Canvas::Get()->AddUI(button);

    std::shared_ptr<UI::Text> text = std::make_shared<UI::Text>(L"ButtonText");
    text->SetPosition({ 0.f, 0.f });
    text->SetSize({ 0.f, 0.f });
    text->SetAnchorPreset(AnchorPresets::kStretch, true);
    text->SetColor(Math::Color::Black);
    text->SetText(L"640x480");
    text->AttachToUI(button.get());
    
    Canvas::Get()->AddUI(text);

    std::shared_ptr<UI::Button> button2 = std::make_shared<UI::Button>(L"Button2");
    button2->SetPosition({ 0.f, 40.f });
    button2->SetSize({ 180.f, 30.f });
    button2->SetAnchorPreset(AnchorPresets::kLeft, true);
    button2->AttachToUI(scroll_box.get());
    button2->on_click.Add([]()
    {
        Renderer::Get()->ChangeResolution(World::Get()->GetWindow(), 800, 480);
    });

    Canvas::Get()->AddUI(button2);

    std::shared_ptr<UI::Text> text2 = std::make_shared<UI::Text>(L"ButtonText2");
    text2->SetPosition({ 0.f, 0.f });
    text2->SetSize({ 0.f, 0.f });
    text2->SetAnchorPreset(AnchorPresets::kStretch, true);
    text2->SetColor(Math::Color::Black);
    text2->SetText(L"800x480");
    text2->AttachToUI(button2.get());

    Canvas::Get()->AddUI(text2);

    std::shared_ptr<UI::Slider> slider = std::make_shared<UI::Slider>(L"Slider");
    slider->SetPosition({ 0.f, 0.f });
    slider->SetSize({ 160.f, 20.f });
    slider->SetAnchorPreset(AnchorPresets::kTop, true);

    Canvas::Get()->AddUI(slider);
    
}

void MainMap::Tick(float delta_time)
{
    Level::Tick(delta_time);

    Math::Vector2 position = player->GetTransform()->GetWorldPosition();
    position = Renderer::Get()->ConvertWorldToScreen(position);

    ui->SetPositionScreen(position);
}
