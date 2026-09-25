#include <iostream>
#include "DataShow.hpp"

#include "ValueType/Vector/F2.hpp"
#include "ValueType/Vector/F3.hpp"
#include "ValueType/Vector/F4.hpp"

#include "ValueType/Angle.hpp"
#include "ValueType/Angle2D.hpp"
#include "ValueType/Angle3D.hpp"
#include "ValueType/EulerAngle3D.hpp"

#include "ValueType/Trans/2D.hpp"
#include "ValueType/Trans/3D.hpp"

#include "ValueType/Matrix/2x2.hpp"
#include "ValueType/Matrix/3x3.hpp"
#include "ValueType/Matrix/4x4.hpp"

#include <math.h>



void TestPointToX2D()
{
	Angle a0 = Angle::Degrees(65);
	VectorF2 axis(12, 0);

	VectorF2 p1 = a0.forward(axis);

	std::cout << a0.ToDegrees() << '\n';
	std::cout << Angle::PointToX(p1).ToDegrees() << '\n';
	std::cout << '\n';
}
void TestPointToY2D()
{
	Angle a0 = Angle::Degrees(65);
	VectorF2 axis(0, 12);

	VectorF2 p1 = a0.forward(axis);

	std::cout << a0.ToDegrees() << '\n';
	std::cout << Angle::PointToY(p1).ToDegrees() << '\n';
	std::cout << '\n';
}

void TestPointToX3D()
{
	EulerAngle3D a0 = EulerAngle3D::Degrees(65, 0, 81);
	VectorF3 axis(1, 0, 0);

	VectorF3 p1 = a0.forward(axis);
	EulerAngle3D a1 = EulerAngle3D::PointToX(p1);

	std::cout << "a1.Z0: " << a1.Z0.ToDegrees() << '\n';
	std::cout << "a1.X1: " << a1.X1.ToDegrees() << '\n';
	std::cout << "a1.Y2: " << a1.Y2.ToDegrees() << '\n';
	std::cout << '\n';

	std::cout << "a0.Z0: " << a0.Z0.ToDegrees() << '\n';
	std::cout << "a0.X1: " << a0.X1.ToDegrees() << '\n';
	std::cout << "a0.Y2: " << a0.Y2.ToDegrees() << '\n';
	std::cout << '\n';
}
void TestPointToY3D()
{
	EulerAngle3D a0 = EulerAngle3D::Degrees(65, 81, 0);
	VectorF3 axis(0, 1, 0);

	VectorF3 p1 = a0.forward(axis);
	EulerAngle3D a1 = EulerAngle3D::PointToY(p1);

	std::cout << "a1.Z0: " << a1.Z0.ToDegrees() << '\n';
	std::cout << "a1.X1: " << a1.X1.ToDegrees() << '\n';
	std::cout << "a1.Y2: " << a1.Y2.ToDegrees() << '\n';
	std::cout << '\n';

	std::cout << "a0.Z0: " << a0.Z0.ToDegrees() << '\n';
	std::cout << "a0.X1: " << a0.X1.ToDegrees() << '\n';
	std::cout << "a0.Y2: " << a0.Y2.ToDegrees() << '\n';
	std::cout << '\n';
}
void TestPointToZ3D()
{
	EulerAngle3D a0 = EulerAngle3D::Degrees(0, 65, 81);
	VectorF3 axis(0, 0, 1);

	VectorF3 p1 = a0.forward(axis);
	EulerAngle3D a1 = EulerAngle3D::PointToZ(p1);

	std::cout << "a1.Z0: " << a1.Z0.ToDegrees() << '\n';
	std::cout << "a1.X1: " << a1.X1.ToDegrees() << '\n';
	std::cout << "a1.Y2: " << a1.Y2.ToDegrees() << '\n';
	std::cout << '\n';

	std::cout << "a0.Z0: " << a0.Z0.ToDegrees() << '\n';
	std::cout << "a0.X1: " << a0.X1.ToDegrees() << '\n';
	std::cout << "a0.Y2: " << a0.Y2.ToDegrees() << '\n';
	std::cout << '\n';
}



int main()
{
//	std::cout << '\n'; TestPointToX2D();
//	std::cout << '\n'; TestPointToY2D();
//	std::cout << '\n'; TestPointToX3D();
//	std::cout << '\n'; TestPointToY3D();
//	std::cout << '\n'; TestPointToZ3D();
	return 0;
}
