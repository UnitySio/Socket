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
    std::map<std::wstring, std::shared_ptr<Resource>> resources_;
    
};

template <std::derived_from<Resource> T>
bool ResourceManager::Load(const std::wstring& kName, const std::wstring& kPath)
{
    std::shared_ptr<Resource> resource = std::make_shared<T>();
    if (!resource->Load(kPath)) return false;

    resources_[kName] = resource;
    return true;
}

template <std::derived_from<Resource> T>
T* ResourceManager::GetResource(const std::wstring& kName)
{
    auto iter = resources_.find(kName);
    if (iter == resources_.end()) return nullptr;

    return dynamic_cast<T*>(iter->second.get());
}
