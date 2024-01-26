#include "MainScene.h"

#include "../../Engine/Actor/Camera.h"
#include "../Actor/Box.h"
#include "../Actor/Ground.h"
#include "../Actor/Player.h"

MainScene::MainScene()
{
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(GetWorld());
    camera->SetName(L"Camera");

    AddActor(camera);
    
    std::shared_ptr<Actor> ground = std::make_shared<Ground>(GetWorld());
    ground->SetName(L"Ground");
    
    AddActor(ground);

    std::shared_ptr<Actor> player = std::make_shared<Player>(GetWorld());
    player->SetName(L"Player");

    AddActor(player);
}
