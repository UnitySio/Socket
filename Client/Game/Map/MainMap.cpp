#include "MainMap.h"

#include "Actor/FollowCamera.h"
#include "Actor/Pawn.h"
#include "../Engine/Actor/Component/RigidBodyComponent.h"
#include <Windows.h>

#include "Actor/Box.h"
#include "Actor/Tilemap.h"
#include "Actor/Character/Player/PlayerController.h"
#include "tmxlite/Map.hpp"
#include "Actor/Component/Tilemap/TilemapComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Misc/Delegate.h"
#include "Misc/Function.h"
#include "../Canvas.h"
#include "../Button.h"
#include "../ProgressBar.h"
#include "../ScrollView.h"
#include "../TextBlock.h"

MainMap::MainMap(const std::wstring& kName) : Level(kName)
{
    Timer = 0.0f;
}

void MainMap::Load()
{
    /*SHARED_PTR<Actor> tilemap = MAKE_SHARED<Tilemap>(L"Tilemap");
    AddActor(tilemap);*/

    // SHARED_PTR<Actor> pawn = MAKE_SHARED<Pawn>(L"Pawn");
    // AddActor(pawn);

    // SHARED_PTR<Actor> box = MAKE_SHARED<Box>(L"Box");
    // AddActor(box);

    // pawn->GetTransform()->SetRelativePosition({.5f, 2.f});

    // box->GetTransform()->SetRelativePosition({-5.f, 2.f});

    /*SHARED_PTR<Actor> player = MAKE_SHARED<PlayerController>(L"Player");
    AddActor(player);
    
    player->GetTransform()->SetRelativePosition({.5f, 2.f});
    
    SHARED_PTR<Actor> camera = MAKE_SHARED<FollowCamera>(L"FollowCamera");
    AddActor(camera);
    
    FollowCamera* follow_camera = dynamic_cast<FollowCamera*>(camera.get());
    follow_camera->SetFollow(player.get());*/
    
    /*auto string = UIManager::Get()->CreateString();
    string->SetPosition({ 200,200 });
    string->SetText(L"Test");*/

    //auto button = Canvas::Get()->CreateButton();
    ////button->SetPosition({ 300,300 });
    //button->SetAnchorType(UIBase::AnchorType::Center);
    //button->SetBoxSize({ 50,50 });
    //button->SetText(L"Test");

    //auto button2 = Canvas::Get()->CreateButton();
    //button2->SetParent(button);
    //button2->SetAnchorType(UIBase::AnchorType::LeftTop);
    //button2->SetBoxSize({ 50,50 });
    //button2->SetText(L"Test2");

    //auto button3 = Canvas::Get()->CreateButton();
    //button3->SetParent(button);
    //button3->SetAnchorType(UIBase::AnchorType::RightTop);
    //button3->SetBoxSize({ 50,50 });
    //button3->SetText(L"Test2");

    //auto button4 = Canvas::Get()->CreateButton();
    //button4->SetParent(button);
    //button4->SetAnchorType(UIBase::AnchorType::LeftBottom);
    //button4->SetBoxSize({ 50,50 });
    //button4->SetText(L"Test2");
    //
    /*button = Canvas::Get()->CreateButton();
    button->SetBoxSize({ 50,50 });
    button->SetText(L"Click To Change On/Off");
    button->SetPosition({ 300,300 });
    button->SetEnable(true);
    button->SetVisibility(true);
    button->BindAction(UIBase::EventType::OnClicked, [this]() 
        {
        
            if (bar->IsEnalbed())
            {
                bar->SetEnable(false);
                bar->SetTouchEnable(false);
                button->SetText(L"Off");
            }
            
            else
            {
                bar->SetEnable(true);
                bar->SetTouchEnable(true);
                button->SetText(L"On");
            }
        });


    bar = Canvas::Get()->CreateProgressBar();
    bar->SetPosition({ 200, 200 });
    bar->SetBoxSize({ 50,50 });
    bar->SetValue(0.0f);
    bar->SetEnable(true);
    bar->SetTouchEnable(true);
    bar->SetVertical(false);

    auto bar2 = Canvas::Get()->CreateProgressBar();
    bar2->SetPosition({ 225, 200 });
    bar2->SetBoxSize({ 50,50 });
    bar2->SetValue(0.0f);
    bar2->SetEnable(true);
    bar2->SetTouchEnable(true);
    bar2->SetVertical(true);
    bar2->SetVisibility(true);

    auto view = Canvas::Get()->CreateScrollView();
    view->SetPosition({ 100,150 });
    view->SetEnable(true);*/

    text = Canvas::Get()->CreateTextBlock();
    text->SetText(L"Test");
    text->SetPosition({ 50,50 });
    text->SetVisibility(true);

    
}

void MainMap::Tick(float dt)
{
    Level::Tick(dt);
    Timer += dt;

    
    wchar_t buffer[100];
    swprintf(buffer, 100, L"%.1f", Timer);
    
    text->SetText(buffer);

}