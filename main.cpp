#include <vector>

#include <iostream>
#include <cstring>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "rasterizer.h"


int main()
{
	fff::Rasterizer r(100, 100, 4);
	//r.DrawLine_V1(fff::IntPoint(20, 60), fff::IntPoint(80, 40), fff::Color::Blue);
	//r.DrawLine_V2(fff::IntPoint(20, 60), fff::IntPoint(80, 40), fff::Color::Blue);
	//r.DrawLine_V2(fff::IntPoint(80, 40), fff::IntPoint(20, 60), fff::Color::Red);
	//r.DrawLine_V2(fff::IntPoint(20, 40), fff::IntPoint(40, 80), fff::Color::Red);
	//r.DrawLine_V3(fff::IntPoint(20, 60), fff::IntPoint(80, 40), fff::Color::Blue);
	//r.DrawLine_V3(fff::IntPoint(80, 40), fff::IntPoint(20, 60), fff::Color::Red);
	//r.DrawLine_V3(fff::IntPoint(20, 40), fff::IntPoint(40, 80), fff::Color::Red);
	//r.DrawLine_V4(fff::IntPoint(20, 60), fff::IntPoint(80, 40), fff::Color::Blue);
	//r.DrawLine_V4(fff::IntPoint(80, 40), fff::IntPoint(20, 60), fff::Color::Red);
	//r.DrawLine_V4(fff::IntPoint(20, 40), fff::IntPoint(40, 80), fff::Color::Red);
	r.DrawLine_V5(fff::IntPoint(20, 60), fff::IntPoint(80, 40), fff::Color::Blue);
	r.DrawLine_V5(fff::IntPoint(80, 40), fff::IntPoint(20, 60), fff::Color::Red);
	r.DrawLine_V5(fff::IntPoint(20, 40), fff::IntPoint(40, 80), fff::Color::Red);
	r.DrawLine_V5(fff::IntPoint(50, 50), fff::IntPoint(50, 80), fff::Color::Red);
	r.DrawLine_V5(fff::IntPoint(50, 50), fff::IntPoint(80, 50), fff::Color::Green);
    r.Serialize("C:\\Users\\travm\\Repos\\travmygit\\fffrenderer\\output\\output1.png");

    return 0;
}