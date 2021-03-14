#pragma once

#include <vector>


namespace fff
{

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

enum class ImageType : std::uint8_t
{
	PNG,
};

enum class ModelType : std::uint8_t
{
	OBJ,
};

} // namespace fff
