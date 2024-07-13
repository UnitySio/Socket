#pragma once
#include "Actor/Actor.h"

class Interactable : public Actor
{
public:
    Interactable(const std::wstring& kName);
    virtual ~Interactable() override;


protected:
    using Super = Actor;

};