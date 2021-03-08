#include "rasterizer.h"
#include <algorithm>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


fff::Rasterizer::Rasterizer(int _Width, int _Height)
    : Width(_Width)
    , Height(_Height)
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

			derror += 2 * dy;
			if (derror >= dx)
			{
				y += (y2 > y1) ? 1 : -1;
				derror -= 2 * dx;
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

			derror += 2 * dx;
			if (derror >= dy)
			{
				x += (x2 > x1) ? 1 : -1;
				derror -= 2 * dy;
			}
		}
	}
}

void fff::Rasterizer::DrawTriangle(fff::IntPoint V1, fff::IntPoint V2, fff::IntPoint V3, const fff::Color& Color)
{
	fff::BoundingBox Bounds = fff::BoundingBox::BuildAABB(V1, V2, V3);

	fff::IntPoint P;
	for (P.X = Bounds.Min.X; P.X <= Bounds.Max.X; ++P.X)
	{
		for (P.Y = Bounds.Min.Y; P.Y <= Bounds.Max.Y; ++P.Y)
		{
			fff::Vector Coord = fff::Vector::Barycentric(V1, V2, V3, P);
			if (Coord.X < 0 || Coord.Y < 0 || Coord.Z < 0)
			{
				continue;
			}
			SetPixel(P.X, P.Y, Color);
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

bool fff::Rasterizer::Serialize(const char* Filename, const int Components /*= 4*/, const fff::ImageType Type /*= fff::ImageType::PNG*/) const
{
	bool bResult = false;

	if (Components < 0 || Components > 4)
	{
		return bResult;
	}

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

	switch (Type)
	{
	case ImageType::PNG:
		bResult = stbi_write_png(Filename, Width, Height, Components, RawData, 0);
		break;
	default:
		bResult = false;
	}

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
