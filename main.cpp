#include <iostream>
#include <Eigen/Dense>
#include "maths.h"
#include "graphics.h"
#include "rasterizer.h"


int main()
{
	fff::Rasterizer r(100, 100);
	fff::IntPoint V1(20, 80);
	fff::IntPoint V2(40, 20);
	fff::IntPoint V3(80, 40);
	r.DrawTriangle(V1, V2, V3, fff::Color::Blue);
    r.Serialize("output2.png");

	
	Eigen::MatrixXd m(2, 2);
	m(0, 0) = 3;
	m(1, 0) = 2.5;
	m(0, 1) = -1;
	m(1, 1) = m(1, 0) + m(0, 1);
	std::cout << m << std::endl;

    return 0;
}