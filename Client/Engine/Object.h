#pragma once
#include "rttr/registration_friend.h"
#include "rttr/rttr_enable.h"

class Object
{
public:
    Object();
    virtual ~Object() = default;

    bool operator==(const Object& kOther) const;

    inline MathTypes::uint64 GetInstanceID() const { return instance_id_; }

private:
    static MathTypes::uint64 next_instance_id_;
    
    MathTypes::uint64 instance_id_;

    RTTR_ENABLE()
    RTTR_REGISTRATION_FRIEND
    
};
