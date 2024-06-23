#pragma once
#include "Actor/Actor.h"
#include "Math/Bounds.h"
#include "Math/Vector2.h"

struct FocusArea
{
    Math::Vector2 center;
    Math::Vector2 velocity;

    float left;
    float right;
    float top;
    float bottom;

    FocusArea(const Bounds& bounds, const Math::Vector2 size)
    {
        left = bounds.center.x - size.x / 2.f;
        right = bounds.center.x + size.x / 2.f;
        top = bounds.min.y + size.y;
        bottom = bounds.min.y;

        center = {(left + right) / 2.f, (top + bottom) / 2.f};
    }

    void Tick(const Bounds& bounds)
    {
        float shift_x = 0.f;
        if (bounds.min.x < left)
        {
            shift_x = bounds.min.x - left;
        }
        else if (bounds.max.x > right)
        {
            shift_x = bounds.max.x - right;
        }
        left += shift_x;
        right += shift_x;

        float shift_y = 0.f;
        if (bounds.min.y < bottom)
        {
            shift_y = bounds.min.y - bottom;
        }
        else if (bounds.max.y > top)
        {
            shift_y = bounds.max.y - top;
        }
        top += shift_y;
        bottom += shift_y;

        center = {(left + right) / 2.f, (top + bottom) / 2.f};
        velocity = {shift_x, shift_y};
    }
};

class FollowCamera : public Actor
{
public:
    FollowCamera(const std::wstring& kName);
    virtual ~FollowCamera() override = default;

    virtual void BeginPlay() override;
    virtual void PhysicsTick(float delta_time) override;
    virtual void Tick(float delta_time) override;

    inline void SetFollow(class Actor* target) { target_ = target; }

private:
    class CameraComponent* camera_;
    
    class Actor* target_;

    class BoxColliderComponent* box_collider_;

    UNIQUE_PTR<FocusArea> focus_area_;

    Math::Vector2 focus_area_size_;
    
    float vertical_offset_;
    
};
