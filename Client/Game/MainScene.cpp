#include "MainScene.h"

#include "../Engine/Graphics/Graphics.h"
#include "../Engine/Input/InputManager.h"
#include "box2d/b2_body.h"
#include "box2d/b2_contact.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"

MainScene::MainScene()
    : gravity_(0.f, 9.8f * 100.f), world_(gravity_)
{
}

void MainScene::Begin()
{
    b2BodyDef ground_body_def;
    ground_body_def.position.Set(0.f, 448.f);
    ground_body_ = world_.CreateBody(&ground_body_def);

    b2PolygonShape ground_box;
    ground_box.SetAsBox(512.f, 32.f);

    ground_body_->CreateFixture(&ground_box, 0.f);
    
    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
    body_def.position.Set(32.f, 32.f);
    dynamic_body_ = world_.CreateBody(&body_def);

    b2PolygonShape dynamic_box;
    dynamic_box.SetAsBox(16.f, 16.f);

    b2FixtureDef fixture_def;
    fixture_def.shape = &dynamic_box;
    fixture_def.density = 1.f;
    fixture_def.friction = .3f;

    dynamic_body_->CreateFixture(&fixture_def);
}

void MainScene::End()
{
}

void MainScene::Tick(float deltaTime)
{
    std::shared_ptr<InputManager> input_manager = InputManager::GetInstance();

    const int h = input_manager->IsKeyPressed(VK_RIGHT) - input_manager->IsKeyPressed(VK_LEFT);
    dynamic_body_->SetLinearVelocity(b2Vec2(h * 100.f, dynamic_body_->GetLinearVelocity().y));

    if (input_manager->IsKeyDown(VK_UP))
    {
        dynamic_body_->ApplyLinearImpulse(b2Vec2(0.f, -500000.f), dynamic_body_->GetWorldCenter(), true);
    }
    
    world_.Step(deltaTime, 8, 3);
}

void MainScene::Render()
{
    Graphics::GetInstance()->FillRectangle(dynamic_body_->GetPosition(), dynamic_body_->GetAngle());
}
