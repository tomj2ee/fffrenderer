#include "rasterizer.h"

fff::Color fff::Color::White = fff::Color(255, 255, 255, 255);
fff::Color fff::Color::Black = fff::Color(0, 0, 0, 255);
fff::Color fff::Color::Red = fff::Color(255, 0, 0, 255);
fff::Color fff::Color::Green = fff::Color(0, 255, 0, 255);
fff::Color fff::Color::Blue = fff::Color(0, 0, 255, 255);

fff::Rasterizer::Rasterizer(int _Width, int _Height, int _Components /* = 3 */)
    : Width(_Width)
    , Height(_Height)
    , Components(_Components)
{
    FrameBuffer.resize(_Width*_Height);
}

void fff::Rasterizer::SetPixel(int X, int Y, const fff::Color& Color)
{
    if (X < 0 || Y < 0 || X >= Width || Y >= Height)
    {
        return;
    }
    FrameBuffer[Y * Width + X] = Color;
}

void fff::Rasterizer::SetPixel(const fff::IntPoint& Point, const fff::Color& Color)
{
    if (Point.X < 0 || Point.Y < 0 || Point.X >= Width || Point.Y >= Height)
    {
        return;
    }
    FrameBuffer[Point.Y * Width + Point.X] = Color;
}

void fff::Rasterizer::DrawLine(const fff::IntPoint& Start, const fff::IntPoint& End, const fff::Color& Color)
{
	int x1 = Start.X;
	int y1 = Start.Y;
	int x2 = End.X;
	int y2 = End.Y;

	int dx = (x1 < x2) ? x2 - x1 : x1 - x2;
	int dy = (y1 < y2) ? y2 - y1 : y1 - y2;

	int derror = 0;

	if (dx >= dy)
	{
		if (x2 < x1)
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
		}

		int y = y1;

		for (int x = x1; x <= x2; ++x)
		{
			SetPixel(x, y, Color);

			derror += dy;
			if (derror >= dx)
			{
				y += (y2 > y1) ? 1 : -1;
				derror -= dx;
			}
		}
	}
	else
	{
		if (y2 < y1)
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
		}

		int x = x1;

		for (int y = y1; y <= y2; ++y)
		{
			SetPixel(x, y, Color);

			derror += dx;
			if (derror >= dy)
			{
				x += (x2 > x1) ? 1 : -1;
				derror -= dy;
			}
		}
	}
}

int fff::Rasterizer::GetWidth() const
{
    return Width;
}

int fff::Rasterizer::GetHeight() const
{
    return Height;
}

int fff::Rasterizer::GetComponents() const
{
    return Components;
}

bool fff::Rasterizer::Serialize(char const* Filename) const
{
	unsigned char* RawData = new unsigned char[Height*Width*Components];
	std::memset(RawData, 255, Height*Width*Components);
	for (int i = 0; i < Height; ++i)
	{
		for (int j = 0; j < Width; ++j)
		{
			for (int k = 0; k < Components; ++k)
			{
				RawData[(i * Width + j) * Components + k] = FrameBuffer[i * Width + j].Raw[k];
			}
		}
	}
	bool bResult = stbi_write_png(Filename, Width, Height, Components, RawData, 0);
	delete RawData;
	return bResult;
}

int fff::Rasterizer::GetIndex_Unsafe(int X, int Y) const
{
    return Y * Width + X;
}

int fff::Rasterizer::GetIndex_Unsafe(const fff::IntPoint& Point) const
{
    return Point.Y * Width + Point.X;
}
