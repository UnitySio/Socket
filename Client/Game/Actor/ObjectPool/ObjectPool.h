#pragma once
#include "PooledObject.h"
#include "Actor/Component/ActorComponent.h"

class ObjectPool : public ActorComponent
{
    SHADER_CLASS_HELPER(ObjectPool)
    GENERATED_BODY(ObjectPool, ActorComponent)
    
public:
    ObjectPool(Actor* owner, const std::wstring& kName);
    virtual ~ObjectPool() override = default;

    virtual void BeginPlay() override;

    PooledObject* SpawnPooledObject();

    void OnPooledObjectDespawn(PooledObject* pool_actor);

protected:
    std::vector<PooledObject*> object_pool_;
    std::vector<int> spawned_pool_indexes_;
    
};
