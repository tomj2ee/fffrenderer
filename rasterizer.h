#pragma once

#include <vector>
#include "stb_image.h"
#include "stb_image_write.h"

namespace fff {

struct Color
{
    union
    {
        struct
        {
            unsigned char R, G, B, A;
        };
        unsigned char Raw[4];
        unsigned int Value;
    };

    /** Number of components */
    int N;

    Color() : Value(0), N(1)
    {}

    Color(unsigned char _R, unsigned char _G, unsigned char _B, unsigned char _A) : R(_R), G(_G), B(_B), A(_A), N(4)
    {}

    Color(int _Value, int _N) : Value(_Value), N(_N)
    {}

    Color(const unsigned char* _Raw, int _N) : Value(0), N(_N)
    {
        for (int i = 0; i < _N; ++i)
        {
            Raw[i] = _Raw[i];
        }
    }

    Color(const Color& Others) : Value(Others.Value), N(Others.N)
    {}

    Color& operator = (const Color& Others)
    {
        if (this != &Others)
        {
            Value = Others.Value;
            N = Others.N;
        }
        return *this;
    }

    static Color White;
    static Color Black;
    static Color Red;
    static Color Green;
    static Color Blue;
};

struct IntPoint
{
    int X, Y;

    IntPoint() : X(0), Y(0)
    {}

    IntPoint(int _X, int _Y) : X(_X), Y(_Y)
    {}

    IntPoint(const IntPoint& Others) : X(Others.X), Y(Others.Y)
    {}

    IntPoint& operator = (const IntPoint& Others)
    {
        if (this != &Others)
        {
            X = Others.X;
            Y = Others.Y;
        }
        return *this;
    }
};

class Rasterizer
{
public:
	Rasterizer(int _Width, int _Height, int _Components = 3);

    void SetPixel(int X, int Y, const fff::Color& Color);
    void SetPixel(const fff::IntPoint& Point, const fff::Color& Color);

	void DrawLine_V1(const fff::IntPoint& Start, const fff::IntPoint& End, const fff::Color& Color);
	void DrawLine_V2(const fff::IntPoint& Start, const fff::IntPoint& End, const fff::Color& Color);
	void DrawLine_V3(const fff::IntPoint& Start, const fff::IntPoint& End, const fff::Color& Color);
	void DrawLine_V4(const fff::IntPoint& Start, const fff::IntPoint& End, const fff::Color& Color);
	void DrawLine_V5(const fff::IntPoint& Start, const fff::IntPoint& End, const fff::Color& Color);

    int GetWidth() const;
    int GetHeight() const;
    int GetComponents() const;

	bool Serialize(char const* Filename) const;

private:
    int GetIndex_Unsafe(int X, int Y) const;
    int GetIndex_Unsafe(const fff::IntPoint& Point) const;

    /** Width of frame buffer */
    int Width;
    /** Height of frame buffer */
    int Height;
    /** Number of components of color */
    int Components;
    /** Frame buffer */
    std::vector<fff::Color> FrameBuffer;
};

} // namespace fff
