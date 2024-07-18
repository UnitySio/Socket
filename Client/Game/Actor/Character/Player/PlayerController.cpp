#include "pch.h"
#include "PlayerController.h"

#include "Actor/Box.h"
#include "Actor/Component/RigidBodyComponent.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Actor/Component/Animator/AnimationClip.h"
#include "Actor/Component/Animator/AnimatorComponent.h"
#include "Audio/AudioManager.h"
#include "Data/DataManager.h"
#include "imgui/imgui.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "UI/Canvas.h"
#include "UI/TextBlock.h"
#include "Windows/DX/Sprite.h"
#include "Logger/Logger.h"
#include "Resource/ResourceManager.h"
#include "Windows/DX/UITexture.h"

PlayerController::PlayerController(const std::wstring& kName) : CharacterBase(kName)
{
    sprite_ = std::make_shared<Sprite>();
    CHECK_IF(sprite_->Load(L".\\Game_Data\\Soldier.png"), L"Failed to load texture");
    
    sprite_->Split(9, 7, Sprite::kCenter);

    sprite_renderer_->SetSprite(sprite_);

    int temp[] = {0, 1, 2, 3, 4, 5};
    std::shared_ptr<AnimationClip> clip = animator_->AddClip(L"Idle", temp, 6);
    clip->SetRepeat(true);
    clip->SetFrameRate(6.f);

    int walk_indices[] = {9, 10, 11, 12, 13, 14, 15, 16};
    clip = animator_->AddClip(L"Walk", walk_indices, 8);
    clip->SetRepeat(true);
    clip->SetFrameRate(6.f);
    
    animator_->PlayClip(clip);

    GetTransform()->SetRelativeScale({2.f, 2.f});
    
    CHECK(AudioManager::Get()->AddSound(L"BGM", L".\\Game_Data\\bgm.mp3"));
    int id = AudioManager::Get()->PlaySound2D(L"BGM");

    // if (ResourceManager::Get()->Load<UITexture>(L"Soldier", L".\\Game_Data\\Soldier.png"))
    // {
    //     UITexture* texture = ResourceManager::Get()->GetResource<UITexture>(L"Soldier");
    // }
}

void PlayerController::BeginPlay()
{
    CharacterBase::BeginPlay();

    text_block_ = Canvas::Get()->CreateTextBlock();
    //text_block_->SetAnchorType(UIBase::AnchorType::Center);
    text_block_->SetText(L"Hello, World!");
    text_block_->SetAlignment(TextBlock::TextAlignment::Center, TextBlock::ParaAlignment::Center);
    text_block_->SetFontStyle(false, false);
    // text_block_->SetTextColor(Math::Color::Cyan);
    text_block_->SetSize({ 250,50 });

    float x = DataManager::GetFloat(L"PlayerX", 0.f);
    float y = DataManager::GetFloat(L"PlayerY", 0.f);
    GetTransform()->SetWorldPosition({x, y});
}

void PlayerController::EndPlay(EndPlayReason type)
{
    CharacterBase::EndPlay(type);
    
    Math::Vector2 position = GetTransform()->GetWorldPosition();
    DataManager::SetFloat(L"PlayerX", position.x);
    DataManager::SetFloat(L"PlayerY", position.y);
}

void PlayerController::PhysicsTick(float delta_time)
{
    CharacterBase::PhysicsTick(delta_time);

    Keyboard* keyboard = Keyboard::Get();

    const float h = keyboard->IsKeyDown(VK_RIGHT) - keyboard->IsKeyDown(VK_LEFT);
    if (h != 0.f)
    {
        sprite_renderer_->SetFlipX(h < 0.f);
        animator_->PlayClip(L"Walk");
    }
    else animator_->PlayClip(L"Idle");
    
    rigid_body_->SetVelocity({h * 2.f, rigid_body_->GetVelocity().y});
}

void PlayerController::Tick(float delta_time)
{
    CharacterBase::Tick(delta_time);
    
    Keyboard* keyboard = Keyboard::Get();
    
    if (keyboard->IsKeyPressed('C'))
    {
        rigid_body_->SetVelocity(Math::Vector2::Zero());
        rigid_body_->AddForce(Math::Vector2::Up() * 5.f, ForceMode::kImpulse);
    }
    
    if (keyboard->IsKeyPressed('Z'))
    {
        Box* box = new Box(L"Box");
        box->GetTransform()->SetRelativePosition(GetTransform()->GetWorldPosition());
        SpawnActor(box);
    }

    TransformComponent* transform = GetTransform();
    Math::Vector2 world_position = Renderer::Get()->ConvertWorldToScreen(transform->GetWorldPosition());
    text_block_->SetPosition(world_position);

    Mouse* mouse = Mouse::Get();
    // if (mouse->IsButtonDown(MouseButton::kLeft))
    // {
    //     LOG(L"Left Button Down");
    // }

    Math::Vector2 mouse_position = mouse->GetMousePosition();
    mouse_position = Renderer::Get()->ConvertScreenToWorld(mouse_position);
    
    if (mouse->IsButtonPressed(MouseButton::kLeft))
    {
        LOG(L"Left Button Pressed %d", 10);
        LOG_ERROR(L"Left Button Pressed %d", 10);
        LOG_WARNING(L"Left Button Pressed %d", 10);
        // GetTransform()->SetWorldPosition(mouse_position);
    }

    // if (mouse->IsButtonReleased(MouseButton::kLeft))
    // {
    //     LOG(L"Left Button Released");
    // }

    static int r = 255;
    static int g = 255;
    static int b = 255;
    static int a = 255;

    ImGui::SliderInt("R", &r, 0, 255);
    ImGui::SliderInt("G", &g, 0, 255);
    ImGui::SliderInt("B", &b, 0, 255);
    ImGui::SliderInt("A", &a, 0, 255);

    sprite_renderer_->SetColor(Math::Color(r, g, b, a));
    
}
