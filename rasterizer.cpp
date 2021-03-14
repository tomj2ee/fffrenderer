#include "rasterizer.h"
#include <iostream>
#include <algorithm>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"


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

void fff::Rasterizer::LoadAndDrawModel(const char* Filename, const fff::RenderMode Mode /*= RenderMode::FRAME*/, const fff::ModelType Type /*= ModelType::OBJ*/)
{
	if (Type == ModelType::OBJ)
	{
		tinyobj::ObjReaderConfig ReaderConfig;
		tinyobj::ObjReader Reader;

		if (!Reader.ParseFromFile(Filename, ReaderConfig))
		{
			if (!Reader.Error().empty())
			{
				std::cerr << "TinyObjReader: " << Reader.Error();
			}
			return;
		}

		if (!Reader.Warning().empty())
		{
			std::cout << "TinyObjReader: " << Reader.Warning();
		}

		auto& attrib = Reader.GetAttrib();
		auto& shapes = Reader.GetShapes();
		auto& materials = Reader.GetMaterials();

		for (size_t s = 0; s < shapes.size(); s++)
		{
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
			{
				size_t fv = shapes[s].mesh.num_face_vertices[f];
				if (Mode == RenderMode::FRAME)
				{
					for (size_t v = 0; v < fv - 1; v++)
					{
						//
						tinyobj::index_t idx0 = shapes[s].mesh.indices[index_offset + v];
						tinyobj::real_t vx0 = attrib.vertices[3 * idx0.vertex_index + 0];
						tinyobj::real_t vy0 = attrib.vertices[3 * idx0.vertex_index + 1];
						tinyobj::real_t vz0 = attrib.vertices[3 * idx0.vertex_index + 2];
						//
						tinyobj::index_t idx1 = shapes[s].mesh.indices[index_offset + v + 1];
						tinyobj::real_t vx1 = attrib.vertices[3 * idx1.vertex_index + 0];
						tinyobj::real_t vy1 = attrib.vertices[3 * idx1.vertex_index + 1];
						tinyobj::real_t vz1 = attrib.vertices[3 * idx1.vertex_index + 2];
						//
						fff::IntPoint p0((int)((vx0 + 1.f)*Width / 2), (int)((vy0 + 1.f)*Height / 2));
						fff::IntPoint p1((int)((vx1 + 1.f)*Width / 2), (int)((vy1 + 1.f)*Height / 2));
						DrawLine(p0, p1, fff::Color::Blue);
					}
				}
				else if (Mode == RenderMode::FILLED)
				{
					{
						size_t v = 0;
						//
						tinyobj::index_t idx0 = shapes[s].mesh.indices[index_offset + v];
						tinyobj::real_t vx0 = attrib.vertices[3 * idx0.vertex_index + 0];
						tinyobj::real_t vy0 = attrib.vertices[3 * idx0.vertex_index + 1];
						tinyobj::real_t vz0 = attrib.vertices[3 * idx0.vertex_index + 2];
						//
						tinyobj::index_t idx1 = shapes[s].mesh.indices[index_offset + v + 1];
						tinyobj::real_t vx1 = attrib.vertices[3 * idx1.vertex_index + 0];
						tinyobj::real_t vy1 = attrib.vertices[3 * idx1.vertex_index + 1];
						tinyobj::real_t vz1 = attrib.vertices[3 * idx1.vertex_index + 2];
						//
						tinyobj::index_t idx2 = shapes[s].mesh.indices[index_offset + v + 2];
						tinyobj::real_t vx2 = attrib.vertices[3 * idx2.vertex_index + 0];
						tinyobj::real_t vy2 = attrib.vertices[3 * idx2.vertex_index + 1];
						tinyobj::real_t vz2 = attrib.vertices[3 * idx2.vertex_index + 2];
						//
						fff::IntPoint p0((int)((vx0 + 1.f)*Width / 2), (int)((vy0 + 1.f)*Height / 2));
						fff::IntPoint p1((int)((vx1 + 1.f)*Width / 2), (int)((vy1 + 1.f)*Height / 2));
						fff::IntPoint p2((int)((vx2 + 1.f)*Width / 2), (int)((vy2 + 1.f)*Height / 2));
						DrawTriangle(p0, p1, p2, fff::Color(rand() % 256, rand() % 256, rand() % 256, 255));
					}
				}
				index_offset += fv;
			}
		}
	}
}

bool fff::Rasterizer::Serialize(const char* Filename, bool FlipVerticallyOnWrite /*= false*/, const int Components /*= 4*/, const fff::ImageType Type /*= fff::ImageType::PNG*/) const
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

	stbi_flip_vertically_on_write(FlipVerticallyOnWrite);

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
