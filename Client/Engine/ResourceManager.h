#pragma once
#include "Singleton.h"

class ResourceManager : public Singleton<ResourceManager>
{
public:
    ResourceManager();
    virtual ~ResourceManager() final = default;
    
};
