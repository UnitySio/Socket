#include "pch.h"
#include "ObjectPool.h"

#include "Bullet.h"
#include "Actor/Actor.h"
#include "Actor/Component/TransformComponent.h"

ObjectPool::ObjectPool(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName),
    object_pool_(),
    spawned_pool_indexes_()
{
}

void ObjectPool::BeginPlay()
{
    ActorComponent::BeginPlay();

    for (int i = 0; i < 20; ++i)
    {
        PooledObject* poolable_actor = World::Get()->SpawnActor<Bullet>(L"Bullet");
        if (poolable_actor)
        {
            poolable_actor->SetActive(false);
            poolable_actor->SetPoolIndex(i);
            poolable_actor->on_despawn.Add(this, &ObjectPool::OnPooledObjectDespawn);
            object_pool_.push_back(poolable_actor);
        }
    }
}

PooledObject* ObjectPool::SpawnPooledObject()
{
    for (const auto& poolable_actor : object_pool_)
    {
        if (poolable_actor != nullptr && !poolable_actor->IsActive())
        {
            poolable_actor->GetTransform()->SetPosition({0.f, 0.f});
            poolable_actor->SetActive(true);
            spawned_pool_indexes_.push_back(poolable_actor->GetPoolIndex());
            
            return poolable_actor;
        }
    }

    if (spawned_pool_indexes_.size() > 0)
    {
        int pooled_object_index = spawned_pool_indexes_[0];
        std::erase(spawned_pool_indexes_, pooled_object_index);
        PooledObject* poolable_actor = object_pool_[pooled_object_index];

        if (poolable_actor)
        {
            poolable_actor->SetActive(false);
            
            poolable_actor->GetTransform()->SetPosition({0.f, 0.f});
            poolable_actor->SetActive(true);
            spawned_pool_indexes_.push_back(poolable_actor->GetPoolIndex());
            
            return poolable_actor;
        }
    }
    
    return nullptr;
}

void ObjectPool::OnPooledObjectDespawn(PooledObject* pool_actor)
{
    std::erase(spawned_pool_indexes_, pool_actor->GetPoolIndex());
}

RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<ObjectPool>("ObjectPool")
        .constructor<Actor*, const std::wstring&>();
}
