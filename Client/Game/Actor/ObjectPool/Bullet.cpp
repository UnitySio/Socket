#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(const std::wstring& kName) :
    PooledObject(kName)
{
}

RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<Bullet>("Bullet")
        .constructor<const std::wstring&>();
}
