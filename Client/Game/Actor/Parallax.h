#pragma once
#include "Actor/Actor.h"

class Parallax : public Actor
{
public:
    Parallax(const std::wstring& kName);
    virtual ~Parallax() override = default;
    
};
