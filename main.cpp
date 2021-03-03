#include <iostream>
#include "maths.h"
#include "graphics.h"
#include "rasterizer.h"


int main()
{
	fff::Rasterizer r(100, 100);
	r.DrawLine(fff::IntPoint(10, 60), fff::IntPoint(20, 80), fff::Color::Blue);
	r.DrawLine(fff::IntPoint(20, 80), fff::IntPoint(80, 40), fff::Color::Blue);
    r.Serialize("output2.png");

    return 0;
}