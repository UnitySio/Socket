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
    std::shared_ptr<Actor> tilemap = std::make_shared<Tilemap>(L"Tilemap");
    AddActor(tilemap);

    std::shared_ptr<Actor> player = std::make_shared<PlayerController>(L"Player");
    AddActor(player);
    
    player->GetTransform()->SetRelativePosition({ 1.5f, 0.f });
    
    std::shared_ptr<Actor> camera = std::make_shared<FollowCamera>(L"FollowCamera");
    AddActor(camera);
    
    FollowCamera* follow_camera = dynamic_cast<FollowCamera*>(camera.get());
    follow_camera->SetFollow(player.get());
    

}

