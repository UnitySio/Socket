#include "MainScene.h"

#include "../../Engine/Actor/Camera.h"
#include "../Actor/Box.h"
#include "../Actor/Ground.h"
#include "../Actor/Player.h"

MainScene::MainScene()
{
    Camera* camera = new Camera(GetWorld());
    camera->SetName(L"Camera");

    Ground* ground = new Ground(GetWorld());
    ground->SetName(L"Ground");

    Player* player = new Player(GetWorld());
    player->SetName(L"Player");

    AddActor(camera);
    AddActor(ground);
    AddActor(player);
}
