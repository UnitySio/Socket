#pragma once
#include "Actor/Component/RayCastController.h"

class PlatformController : public RayCastController
{
public:
    PlatformController(Actor* owner, const std::wstring& kName);
    virtual ~PlatformController() override = default;
    
};
