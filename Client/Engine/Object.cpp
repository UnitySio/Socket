#include "pch.h"
#include "Object.h"

MathTypes::uint64 Object::next_instance_id_ = 0;

Object::Object() :
    instance_id_(next_instance_id_++)
{
}

bool Object::operator==(const Object& other) const
{
    return instance_id_ == other.instance_id_;
}
