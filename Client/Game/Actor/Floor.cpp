#include "Floor.h"

#include "ProjectSettings.h"
#include "Actor/Component/BoxColliderComponent.h"
#include "Actor/Component/AudioComponent.h"
#include "Audio/AudioManager.h"

Floor::Floor(const std::wstring& kName) :
    Actor(kName)
{
    SetLayer(ActorLayer::kFloor);
    
    box_collider_ = CreateComponent<BoxColliderComponent>(L"BoxCollider");
    box_collider_->SetSize({5.f, 1.f});
    
    //AudioManager::AddSound(L"BGM", L"bgm.mp3");
    //FMOD_SOUND* sound = AudioManager::GetSound(L"BGM");
    // AudioManager::SetLoop(sound, true);

    //audio_ = CreateComponent<AudioComponent>(L"Audio");
    //audio_->SetSound(sound);
    //
    //audio_->Play();
}
