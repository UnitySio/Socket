#include "pch.h"
#include "Resource.h"

Resource::Resource()
{
}

RTTR_REGISTRATION
{
    using namespace rttr;
    
    registration::class_<Resource>("Resource");
}
