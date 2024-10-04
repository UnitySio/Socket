#include "pch.h"
#include "StatInfo.h"

#include <rttr/registration>

RTTR_REGISTRATION
{
    using namespace rttr;
    
    registration::class_<StatInfo>("StatInfo")
        .constructor<>()
        .property("name", &StatInfo::name)
        .property("maxHp", &StatInfo::maxHp)
        .property("maxMp", &StatInfo::maxMp)
        .property("moveSpeed", &StatInfo::moveSpeed);
}
