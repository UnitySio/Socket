#include "pch.h"
#include "UIBase.h"

UIBase::UIBase() :
    relative_position_(Math::Vector2::Zero()),
    anchor_min_(Math::Vector2::Zero()),
    anchor_max_(Math::Vector2::One())
{
}
