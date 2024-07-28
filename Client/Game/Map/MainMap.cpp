#include "pch.h"
#include "MainMap.h"

#include "Actor/FollowCamera.h"
#include "Actor/Tilemap.h"
#include "Actor/Character/Player/PlayerController.h"
#include "Actor/Component/TransformComponent.h"
#include "Logger/Logger.h"
#include "Resource/ResourceManager.h"
#include "UI/Canvas.h"
#include "UI/Widget/Button.h"
#include "UI/Widget/Image.h"
#include "Windows/DX/UITexture.h"

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

    ResourceManager::Get()->Load<UITexture>(L"box", L".\\Game_Data\\box.png");
    UITexture* texture = ResourceManager::Get()->GetResource<UITexture>(L"box");
    if (texture)
    {
        std::shared_ptr<UI::Image> image = std::make_shared<UI::Image>(L"Image");
        image->SetPosition({ 0.f, 0.f });
        image->SetSize({ 256.f, 256.f });
        image->SetAnchorPreset(AnchorPresets::kLeft, true);
        image->SetTexture(texture);

        Canvas::Get()->AddWidget(image);
    }

    std::shared_ptr<UI::Button> button = std::make_shared<UI::Button>(L"Button");
    button->SetPosition({ 0.f, 0.f });
    button->SetAnchorPreset(AnchorPresets::kTop, true);
    button->on_click.Add([]()
    {
        LOG(L"Button Clicked");
    });

    Canvas::Get()->AddWidget(button);
    
    std::shared_ptr<UI::Button> button2 = std::make_shared<UI::Button>(L"Button");
    button2->SetPosition({ 90.f, 0.f });
    button2->SetAnchorPreset(AnchorPresets::kTop, true);
    button2->on_click.Add([]()
    {
        LOG(L"Button2 Clicked");
    });

    Canvas::Get()->AddWidget(button2);
}
