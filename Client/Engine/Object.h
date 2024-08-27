#pragma once

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
    
};
