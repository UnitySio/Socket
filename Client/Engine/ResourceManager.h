#pragma once
#include <map>

#include "Singleton.h"

class ResourceManager : public Singleton<ResourceManager>
{
public:
    ResourceManager();
    virtual ~ResourceManager() final = default;

private:
    std::map<std::wstring, struct ID2D1Bitmap*> resources_;
    
};
