#include "MainScene.h"

#include "../Engine/Graphics/Graphics.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"

MainScene::MainScene()
    : gravity_(0.f, 9.8f), world_(gravity_)
{
}

void MainScene::Begin()
{
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

    b2BodyDef body_def2;
    body_def2.type = b2_dynamicBody;
    body_def2.position.Set(64.f, 48.f);
    dynamic_body2_ = world_.CreateBody(&body_def2);

    b2PolygonShape dynamic_box2;
    dynamic_box2.SetAsBox(16.f, 16.f);

    b2FixtureDef fixture_def2;
    fixture_def2.shape = &dynamic_box2;
    fixture_def2.density = 1.f;
    fixture_def2.friction = .3f;

    dynamic_body2_->CreateFixture(&fixture_def2);
}

void MainScene::End()
{
}

void MainScene::Tick(float deltaTime)
{
    world_.Step(deltaTime, 8, 3);
    
    dynamic_body_->ApplyForce(b2Vec2(100000.f, 0.f), dynamic_body_->GetWorldCenter(), true);
}

void MainScene::Render()
{
    Graphics::GetInstance()->FillRectangle(dynamic_body_->GetPosition(), dynamic_body_->GetAngle());
    Graphics::GetInstance()->FillRectangle(dynamic_body2_->GetPosition(), dynamic_body2_->GetAngle());
}
