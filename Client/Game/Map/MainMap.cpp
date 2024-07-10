#include "MainMap.h"

#include "Actor/FollowCamera.h"
#include "Actor/Tilemap.h"
#include "Actor/Character/Player/PlayerController.h"
#include "Actor/Component/TransformComponent.h"
#include "Misc/Delegate.h"
#include "Misc/Function.h"
#include "UI/Canvas.h"
#include "UI/Button.h"
#include "UI/ProgressBar.h"
#include "UI/ScrollView.h"
#include "UI/TextBlock.h"
#include "UI/BitmapComponent.h"
#include "UI/StringComponent.h"
#include "UI/Image.h"


MainMap::MainMap(const std::wstring& kName) : Level(kName)
{
}

void MainMap::Load()
{
    /*SHARED_PTR<Actor> tilemap = MAKE_SHARED<Tilemap>(L"Tilemap");
    AddActor(tilemap);

    SHARED_PTR<Actor> player = MAKE_SHARED<PlayerController>(L"Player");
    AddActor(player);
    
    player->GetTransform()->SetRelativePosition({ 1.5f, 0.f });*/
    
    /*SHARED_PTR<Actor> camera = MAKE_SHARED<FollowCamera>(L"FollowCamera");
    AddActor(camera);
    
    FollowCamera* follow_camera = dynamic_cast<FollowCamera*>(camera.get());
    follow_camera->SetFollow(player.get());*/
    
    Button* button = Canvas::Get()->CreateButton();
    button->SetPosition({ 200,200 });
    button->SetSize({ 50,50 });
    button->SetImage(L"D:\\2024\\Cocos\\Socket\\Client\\Game_Data\\box.png");
    
    Image* image = Canvas::Get()->CreateImage();
    image->SetPosition({ 400,200 });
    image->SetSize({ 50,50 });
    image->SetImage(L"D:\\2024\\Cocos\\Socket\\Client\\Game_Data\\box.png");
    image->SetOpacity(0.5f);
}

