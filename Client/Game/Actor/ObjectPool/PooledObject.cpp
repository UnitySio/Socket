﻿#include "pch.h"
#include "PooledObject.h"

PooledObject::PooledObject(const std::wstring& kName) :
    Actor(kName),
    pool_index_(-1)
{
}

void PooledObject::OnEnable()
{
    Actor::OnEnable();

    TimerManager::Get()->SetTimer(this, &PooledObject::Deactivate, 2.f);
}

void PooledObject::Deactivate()
{
    SetActive(false);
    on_despawn.Execute(this);
}

RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<PooledObject>("PooledObject")
        .constructor<const std::wstring&>()
        (
            policy::ctor::as_std_shared_ptr
        );
}
