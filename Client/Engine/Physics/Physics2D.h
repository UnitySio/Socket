#pragma once
#include <vector>

#include "Math/Vector2.h"

class Actor;

class Physics2D
{
public:
    /**
     * 상자에 겹치는 액터를 찾습니다. \n
     * Owner로 지정된 액터는 결과에서 제외됩니다.
     * @param kCenter 상자의 중심
     * @param kSize 상자의 크기
     * @param kOwner 결과에서 제외할 액터
     * @param output_actor 겹치는 액터
     * @param layer 충돌 레이어
     * @return 겹치는 액터가 있으면 true, 없으면 false
     */
    static bool OverlapBox(const Math::Vector2& kCenter, const Math::Vector2& kSize, const Actor* kOwner, Actor** output_actor, MathTypes::uint16 layer = 0xFFFF);

    /**
     * 상자에 겹치는 모든 액터를 찾습니다. \n
     * Owner로 지정된 액터는 결과에서 제외됩니다.
     * @param kCenter 상자의 중심
     * @param kSize 상자의 크기
     * @param kOwner 결과에서 제외할 액터
     * @param output_actors 겹치는 액터들
     * @param layer 충돌 레이어
     * @return 겹쳐진 액터들이 있으면 true, 없으면 false
     */
    static bool OverlapBoxAll(const Math::Vector2& kCenter, const Math::Vector2& kSize, const Actor* kOwner, std::vector<Actor*>& output_actors, MathTypes::uint16 layer = 0xFFFF);

    /**
     * 원에 겹치는 액터를 찾습니다. \n
     * Owner로 지정된 액터는 결과에서 제외됩니다.
     * @param kCenter 원의 중심
     * @param radius 원의 반지름
     * @param kOwner 결과에서 제외할 액터
     * @param output_actor 겹치는 액터
     * @param layer 충돌 레이어
     * @return 겹치는 액터가 있으면 true, 없으면 false
     */
    static bool OverlapCircle(const Math::Vector2& kCenter, float radius, const Actor* kOwner, Actor** output_actor, MathTypes::uint16 layer = 0xFFFF);

    /**
     * 원에 겹치는 모든 액터를 찾습니다. \n
     * Owner로 지정된 액터는 결과에서 제외됩니다.
     * @param kCenter 원의 중심
     * @param radius 원의 반지름
     * @param kOwner 결과에서 제외할 액터
     * @param output_actors 겹치는 액터들
     * @param layer 충돌 레이어
     * @return 겹쳐진 액터들이 있으면 true, 없으면 false
     */
    static bool OverlapCircleAll(const Math::Vector2& kCenter, float radius, const Actor* kOwner, std::vector<Actor*>& output_actors, MathTypes::uint16 layer = 0xFFFF);

    static bool RayCast(const Math::Vector2& kStart, const Math::Vector2& kEnd);
};
