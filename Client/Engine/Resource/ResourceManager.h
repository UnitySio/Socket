#pragma once
#include "Resource.h"
#include "Singleton.h"

class ResourceManager : public Singleton<ResourceManager>
{
public:
    ResourceManager();
    virtual ~ResourceManager() override = default;

    template <std::derived_from<Resource> T>
    bool Load(const std::wstring& kName, const std::wstring& kPath);

    template <std::derived_from<Resource> T>
    T* GetResource(const std::wstring& kName);

private:
    std::map<std::wstring, std::unique_ptr<Resource>> resources_;
    
};

template <std::derived_from<Resource> T>
bool ResourceManager::Load(const std::wstring& kName, const std::wstring& kPath)
{
    if (resources_.contains(kName)) return true;

    T* resource = new T();
    if (!resource->Load(kPath)) return false;

    resources_[kName] = std::unique_ptr<T>(resource);
    return true;
}

template <std::derived_from<Resource> T>
T* ResourceManager::GetResource(const std::wstring& kName)
{
    if (!resources_.contains(kName)) return nullptr;
    return dynamic_cast<T*>(resources_[kName].get());
}
