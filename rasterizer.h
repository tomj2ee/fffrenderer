#pragma once

#include <vector>
#include "maths.h"
#include "graphics.h"


namespace fff {

class Rasterizer
{
public:
	Rasterizer(int _Width, int _Height);

    void SetPixel(int X, int Y, const fff::Color& Color);
    void SetPixel(const fff::IntPoint& Point, const fff::Color& Color);

	void DrawLine(const fff::IntPoint& Start, const fff::IntPoint& End, const fff::Color& Color);
	void DrawTriangle(fff::IntPoint V1, fff::IntPoint V2, fff::IntPoint V3, const fff::Color& Color);

    int GetWidth() const;
    int GetHeight() const;

	void LoadAndDrawModel(const char* Filename, const fff::RenderMode Mode = RenderMode::FRAME, const fff::ModelType Type = ModelType::OBJ);

	bool Serialize(const char* Filename, bool FlipVerticallyOnWrite = false, const int Components = 4, const fff::ImageType Type = fff::ImageType::PNG) const;

protected:

private:
    int GetIndex_Unsafe(int X, int Y) const;
    int GetIndex_Unsafe(const fff::IntPoint& Point) const;

    /** Width of frame buffer */
    int Width;
    /** Height of frame buffer */
    int Height;
    /** Frame buffer */
    std::vector<fff::Color> FrameBuffer;
};

} // namespace fff
