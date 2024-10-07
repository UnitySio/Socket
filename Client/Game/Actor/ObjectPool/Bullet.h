#pragma once
#include "PooledObject.h"

class Bullet : public PooledObject
{
    SHADER_CLASS_HELPER(Bullet)
    GENERATED_BODY(Bullet, PooledObject)
    
public:
    Bullet(const std::wstring& kName);
    virtual ~Bullet() override = default;
    
};
