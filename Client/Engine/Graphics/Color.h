#pragma once
typedef unsigned char BYTE;

class Color
{
public:
    Color();
    Color(BYTE r, BYTE g, BYTE b);
    Color(BYTE r, BYTE g, BYTE b, BYTE a);

    Color(const Color& kColor);

    Color& operator=(const Color& kColor);

    bool operator==(const Color& kColor) const;
    bool operator!=(const Color& kColor) const;

    inline void SetR(BYTE r) { rgba[0] = r; }
    inline void SetG(BYTE g) { rgba[1] = g; }
    inline void SetB(BYTE b) { rgba[2] = b; }
    inline void SetA(BYTE a) { rgba[3] = a; }

    inline constexpr BYTE R() const { return rgba[0]; }
    inline constexpr BYTE G() const { return rgba[1]; }
    inline constexpr BYTE B() const { return rgba[2]; }
    inline constexpr BYTE A() const { return rgba[3]; }
    
private:
    union
    {
        BYTE rgba[4];
        unsigned int color;
    };
};
