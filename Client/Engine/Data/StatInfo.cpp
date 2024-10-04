#include "pch.h"
#include "StatInfo.h"

#include <rttr/registration>

RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<StatInfo>("StatInfo")
        .property("hp", &StatInfo::hp)
        .property("maxHp", &StatInfo::maxHp)
        .property("moveSpeed", &StatInfo::moveSpeed)
        .property("name", &StatInfo::name);
}
