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
        std::call_once(flag_, []() { instance_.reset(new T()); });
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
    static std::once_flag flag_;
    
};

template <typename T>
UNIQUE_PTR<T> Singleton<T>::instance_ = nullptr;

template <typename T>
std::once_flag Singleton<T>::flag_;