#include "MainMap.h"

#include "Actor/FollowCamera.h"
#include "Actor/Tilemap.h"
#include "Actor/Character/Player/PlayerController.h"
#include "Actor/Component/TransformComponent.h"
<<<<<<< HEAD
#include "Misc/Delegate.h"
#include "Misc/Function.h"
#include "UI/Canvas.h"
#include "UI/Button.h"
#include "UI/ProgressBar.h"
#include "UI/ScrollView.h"
#include "UI/TextBlock.h"
#include "UI/BitmapComponent.h"
#include "UI/StringComponent.h"
=======
>>>>>>> 57566bd121a03d52e76d71b4e6a98ffc491806fe

MainMap::MainMap(const std::wstring& kName) : Level(kName)
{
}

void MainMap::Load()
{
    SHARED_PTR<Actor> tilemap = MAKE_SHARED<Tilemap>(L"Tilemap");
    AddActor(tilemap);

    SHARED_PTR<Actor> player = MAKE_SHARED<PlayerController>(L"Player");
    AddActor(player);
    
    player->GetTransform()->SetRelativePosition({ 1.5f, 0.f });
    
    SHARED_PTR<Actor> camera = MAKE_SHARED<FollowCamera>(L"FollowCamera");
    AddActor(camera);
    
    FollowCamera* follow_camera = dynamic_cast<FollowCamera*>(camera.get());
    follow_camera->SetFollow(player.get());
<<<<<<< HEAD
    
    temp = Canvas::Get()->CreateButton();
    temp->SetPosition({ 200,200 });
    temp->SetSize({ 50,50 });
    temp->SetImage(L"D:\\2024\\Cocos\\Socket\\Client\\Game_Data\\box.png");
    temp->GetTextComponent()->SetText(L"버튼 쥑이네!");
    temp->GetTextComponent()->SetSize({ 150,50 });
    temp->SetEnable(true);
}

void MainMap::Tick(float dt)
{
    Level::Tick(dt);
    if (temp->OnMouse())
    {
        temp->GetTextComponent()->SetText(L"마우스 올라감");
        temp->RemoveImage();
    }
        

    else if (!temp->OnMouse())
    {
        temp->GetTextComponent()->SetText(L"마우스 내려감");
        temp->SetImage(L"D:\\2024\\Cocos\\Socket\\Client\\Game_Data\\box.png");
    }
        
=======

>>>>>>> 57566bd121a03d52e76d71b4e6a98ffc491806fe
}
