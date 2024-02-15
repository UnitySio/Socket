#pragma once

class Vector
{
public:
    Vector();
    Vector(float x, float y);
    Vector& operator+=(const Vector& kVector);
    Vector& operator-=(const Vector& kVector);
    Vector& operator*=(const Vector& kVector);
    Vector& operator/=(const Vector& kVector);
    Vector& operator=(const Vector& kVector);

    Vector operator+(const Vector& kVector);
    Vector operator-(const Vector& kVector);
    Vector operator*(const Vector& kVector);
    Vector operator/(const Vector& kVector);

    Vector operator+(float val);
    Vector operator-(float val);
    Vector operator*(float val);
    Vector operator/(float val);
 
    ~Vector() = default;
 
    float x;
    float y;

    /**
     * \brief Vector(0.f, 0.f)
     * \return Vector
     */
    static Vector Zero();

    /**
     * \brief Vector(1.f, 1.f)
     * \return Vector
     */
    static Vector One();

    /**
     * \brief Vector(-1.f, 0.f)
     * \return Vector
     */
    static Vector Left();

    /**
     * \brief Vector(0.f, -1.f)
     * \return Vector
     */
    static Vector Up();

    /**
     * \brief Vector(1.f, 0.f)
     * \return Vector
     */
    static Vector Right();

    /**
     * \brief Vector(0.f, 1.f)
     * \return Vector
     */
    static Vector Down();

    /**
     * \brief 두 백터를 선형 보간합니다.
     * \param a 첫번째 백터
     * \param b 두번째 백터
     * \param t 비율
     * \return Vector
     */
    static Vector Lerp(Vector a, Vector b, float t);
 
    /**
     * \brief 두 백터의 거리를 반환합니다.
     * \param a 첫번째 백터
     * \param b 두번째 백터
     * \return float
     */
    static float Distance(Vector a, Vector b);

    /**
     * \brief 두 백터의 내적을 반환합니다.
     * \param a 첫번째 백터
     * \param b 두번째 백터
     * \return float
     */
    static float Dot(Vector a, Vector b);
 
    /**
     * \brief 백터를 정규화된 값으로 반환합니다.
     * \return Vector
     */
    Vector Normalized();

    bool operator==(const Vector& kVector) const;
    bool operator!=(const Vector& kVector) const;
    bool operator==(float val) const;
    bool operator!=(float val) const;

    /**
     * \brief 백터의 길이를 반환합니다.
     * \return float
     */
    float Magnitude();

    /**
     * \brief 백터를 정규화를 합니다.
     */
    void Normalize();
};
