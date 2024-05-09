#pragma once
#include <mutex>
#include "Misc/EngineMacros.h"

template <typename T>
class Singleton
{
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static T* Get()
    {
        if (!instance_) instance_ = MAKE_UNIQUE<T>();
        return instance_.get();
    }

    virtual void Release()
    {
        instance_.reset();
    }

protected:
    Singleton() = default;
    virtual ~Singleton() = default;
    
private:
    static UNIQUE_PTR<T> instance_;
    
};

template <typename T>
UNIQUE_PTR<T> Singleton<T>::instance_ = nullptr;