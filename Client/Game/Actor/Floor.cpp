﻿#include "Floor.h"

#include "Actor/Component/BoxColliderComponent.h"
#include "Actor/Component/AudioComponent.h"
#include "Audio/AudioManager.h"

Floor::Floor(b2World* world, const std::wstring& kName) :
    Actor(world, kName)
{
    box_collider_ = CreateComponent<BoxColliderComponent>(L"BoxCollider");
    box_collider_->SetSize({5.f, 1.f});
    
    AudioManager::AddSound(L"BGM", L".\\bgm.mp3");

    audio_ = CreateComponent<AudioComponent>(L"Audio");
    audio_->SetSound(AudioManager::GetSound(L"BGM"));

    audio_->Play();
}
