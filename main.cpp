#include <vector>

#include <iostream>
#include <cstring>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "rasterizer.h"


int main()
{
	fff::Rasterizer r(100, 100, 4);
	r.DrawLine(fff::IntPoint(20, 60), fff::IntPoint(20, 60), fff::Color::Blue);
    r.Serialize("C:\\Users\\travm\\Repos\\travmygit\\fffrenderer\\output\\output1.png");

    return 0;
}