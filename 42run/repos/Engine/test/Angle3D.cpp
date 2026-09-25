#include <iostream>
#include "DataShow.hpp"
#include "ValueType/Angle3D.hpp"
#include "ValueType/Vector/F3.hpp"

int main()
{
	std::cout << '\n';
	{
		{
			Angle3D	a(
				Angle::Radians(132),
				Angle::Radians(23),
				Angle::Radians(1)
			);
			VectorF3 p(13, 43, 54);
			VectorF3 p00 = a.rotateFore(p);
			VectorF3 p01 = a.rotateBack(p00);
			VectorF3 p10 = a.rotateBack(p);
			VectorF3 p11 = a.rotateFore(p10);
			std::cout << p << '\n';
			std::cout << p00 << '\n';
			std::cout << p01 << '\n';
			std::cout << p10 << '\n';
			std::cout << p11 << '\n';
		}
	}
	std::cout << '\n';
	return 0;
}
