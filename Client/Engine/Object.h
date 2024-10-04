﻿#pragma once
#include <rttr/registration>

#include "Misc/EngineMacros.h"
#include "rttr/registration_friend.h"

class Object : public std::enable_shared_from_this<Object>
{
    SHADER_CLASS_HELPER(Object)
    GENERATED_BODY(Object)
    
public:
    Object();
    virtual ~Object() = default;

    bool operator==(const Object& kOther) const;

    inline MathTypes::uint64 GetInstanceID() const { return instance_id_; }

private:
    static MathTypes::uint64 next_instance_id_;
    
    MathTypes::uint64 instance_id_;
    
};
