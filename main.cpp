#include <iostream>
#include <Eigen/Dense>
#include "maths.h"
#include "graphics.h"
#include "rasterizer.h"


const int width = 800;
const int height = 800;

int main()
{
	const char* filename = "african_head.obj";

	fff::Rasterizer r(width, height);

	//r.LoadAndDrawModel(filename, fff::RenderMode::FRAME);
	r.LoadAndDrawModel(filename, fff::RenderMode::FILLED);

	r.Serialize("output.png", true);

    return 0;
}