#include <iostream>
#include <sstream>
#include <exception>

#include "OpenGL.hpp"
#include "Debug.hpp"

#include "DirectoryInfo.hpp"

#include "Window.hpp"
#include "General/ContextBase.hpp"



#include "Selector/new.hpp"

#include "General/ValueGen/Random.hpp"
#include "ValueType/Vector/F3.hpp"
#include "ValueType/EulerAngle3D.hpp"
#include "ValueType/Matrix3x3.hpp"

#include "ValueType/_Show.hpp"

struct SAxiss
{
	VectorF3	axisX;
	VectorF3	axisY;
	VectorF3	axisZ;

	Angle TrySin(unsigned int idx1, unsigned int idx0)
	{
		switch (idx1)
		{
			case 0: switch (idx0)
			{
				case 0: return Angle::aSin(axisX.X);
				case 1: return Angle::aSin(axisX.Y);
				case 2: return Angle::aSin(axisX.Z);
				default: return Angle();
			}
			case 1: switch (idx0)
			{
				case 0: return Angle::aSin(axisY.X);
				case 1: return Angle::aSin(axisY.Y);
				case 2: return Angle::aSin(axisY.Z);
				default: return Angle();
			}
			case 2: switch (idx0)
			{
				case 0: return Angle::aSin(axisZ.X);
				case 1: return Angle::aSin(axisZ.Y);
				case 2: return Angle::aSin(axisZ.Z);
				default: return Angle();
			}
			default: return Angle();
		}
	}
	Angle TryCos(unsigned int idx1, unsigned int idx0)
	{
		switch (idx1)
		{
			case 0: switch (idx0)
			{
				case 0: return Angle::aCos(axisX.X);
				case 1: return Angle::aCos(axisX.Y);
				case 2: return Angle::aCos(axisX.Z);
				default: return Angle();
			}
			case 1: switch (idx0)
			{
				case 0: return Angle::aCos(axisY.X);
				case 1: return Angle::aCos(axisY.Y);
				case 2: return Angle::aCos(axisY.Z);
				default: return Angle();
			}
			case 2: switch (idx0)
			{
				case 0: return Angle::aCos(axisZ.X);
				case 1: return Angle::aCos(axisZ.Y);
				case 2: return Angle::aCos(axisZ.Z);
				default: return Angle();
			}
			default: return Angle();
		}
	}
	Angle TryTan(float val, unsigned int idx1, unsigned int idx0)
	{
		switch (idx1)
		{
			case 0: switch (idx0)
			{
				case 0: return Angle::aTan2(val, axisX.X);
				case 1: return Angle::aTan2(val, axisX.Y);
				case 2: return Angle::aTan2(val, axisX.Z);
				default: return Angle();
			}
			case 1: switch (idx0)
			{
				case 0: return Angle::aTan2(val, axisY.X);
				case 1: return Angle::aTan2(val, axisY.Y);
				case 2: return Angle::aTan2(val, axisY.Z);
				default: return Angle();
			}
			case 2: switch (idx0)
			{
				case 0: return Angle::aTan2(val, axisZ.X);
				case 1: return Angle::aTan2(val, axisZ.Y);
				case 2: return Angle::aTan2(val, axisZ.Z);
				default: return Angle();
			}
			default: return Angle();
		}
	}
	Angle TryTan(unsigned int idx3, unsigned int idx2, unsigned int idx1, unsigned int idx0)
	{
		switch (idx3)
		{
			case 0: switch (idx2)
			{
				case 0: return TryTan(axisX.X, idx1, idx0);
				case 1: return TryTan(axisX.Y, idx1, idx0);
				case 2: return TryTan(axisX.Z, idx1, idx0);
				default: return Angle();
			}
			case 1: switch (idx2)
			{
				case 0: return TryTan(axisY.X, idx1, idx0);
				case 1: return TryTan(axisY.Y, idx1, idx0);
				case 2: return TryTan(axisY.Z, idx1, idx0);
				default: return Angle();
			}
			case 2: switch (idx2)
			{
				case 0: return TryTan(axisZ.X, idx1, idx0);
				case 1: return TryTan(axisZ.Y, idx1, idx0);
				case 2: return TryTan(axisZ.Z, idx1, idx0);
				default: return Angle();
			}
			default: return Angle();
		}
	}
};

/* ( 1 | 0 | 0 )
axisX ( -0.99952 | -0.030986 | 0 )
axisY ( 0.030986 | -0.99952 | 0 )
axisZ ( 0 | 0 | 1 )

178.224 000.000 000.000 
sin(  X.X  ) = 088.224; sin(  X.Y  ) = 001.775; sin(  X.Z  ) = 000.000; sin(  Y.X  ) = 001.775; sin(  Y.Y  ) = 088.224; sin(  Y.Z  ) = 000.000; sin(  Z.X  ) = 000.000; sin(  Z.Y  ) = 000.000; sin(  Z.Z  ) = 090.000; 
cos(  X.X  ) = 178.224; cos(  X.Y  ) = 091.775; cos(  X.Z  ) = 090.000; cos(  Y.X  ) = 088.224; cos(  Y.Y  ) = 178.224; cos(  Y.Z  ) = 090.000; cos(  Z.X  ) = 090.000; cos(  Z.Y  ) = 090.000; cos(  Z.Z  ) = 000.000; 
tan(X.X X.X) = 135.000; tan(X.X X.Y) = 091.775; tan(X.X X.Z) = 090.000; tan(X.X Y.X) = 088.224; tan(X.X Y.Y) = 135.000; tan(X.X Y.Z) = 090.000; tan(X.X Z.X) = 090.000; tan(X.X Z.Y) = 090.000; tan(X.X Z.Z) = 044.986; 
tan(X.Y X.X) = 178.224; tan(X.Y X.Y) = 135.000; tan(X.Y X.Z) = 090.000; tan(X.Y Y.X) = 045.000; tan(X.Y Y.Y) = 178.224; tan(X.Y Y.Z) = 090.000; tan(X.Y Z.X) = 090.000; tan(X.Y Z.Y) = 090.000; tan(X.Y Z.Z) = 001.774; 
tan(X.Z X.X) = 180.000; tan(X.Z X.Y) = 180.000; tan(X.Z X.Z) = 000.000; tan(X.Z Y.X) = 000.000; tan(X.Z Y.Y) = 180.000; tan(X.Z Y.Z) = 000.000; tan(X.Z Z.X) = 000.000; tan(X.Z Z.Y) = 000.000; tan(X.Z Z.Z) = 000.000; 
tan(Y.X X.X) = 178.224; tan(Y.X X.Y) = 135.000; tan(Y.X X.Z) = 090.000; tan(Y.X Y.X) = 045.000; tan(Y.X Y.Y) = 178.224; tan(Y.X Y.Z) = 090.000; tan(Y.X Z.X) = 090.000; tan(Y.X Z.Y) = 090.000; tan(Y.X Z.Z) = 001.774; 
tan(Y.Y X.X) = 135.000; tan(Y.Y X.Y) = 091.775; tan(Y.Y X.Z) = 090.000; tan(Y.Y Y.X) = 088.224; tan(Y.Y Y.Y) = 135.000; tan(Y.Y Y.Z) = 090.000; tan(Y.Y Z.X) = 090.000; tan(Y.Y Z.Y) = 090.000; tan(Y.Y Z.Z) = 044.986; 
tan(Y.Z X.X) = 180.000; tan(Y.Z X.Y) = 180.000; tan(Y.Z X.Z) = 000.000; tan(Y.Z Y.X) = 000.000; tan(Y.Z Y.Y) = 180.000; tan(Y.Z Y.Z) = 000.000; tan(Y.Z Z.X) = 000.000; tan(Y.Z Z.Y) = 000.000; tan(Y.Z Z.Z) = 000.000; 
tan(Z.X X.X) = 180.000; tan(Z.X X.Y) = 180.000; tan(Z.X X.Z) = 000.000; tan(Z.X Y.X) = 000.000; tan(Z.X Y.Y) = 180.000; tan(Z.X Y.Z) = 000.000; tan(Z.X Z.X) = 000.000; tan(Z.X Z.Y) = 000.000; tan(Z.X Z.Z) = 000.000; 
tan(Z.Y X.X) = 180.000; tan(Z.Y X.Y) = 180.000; tan(Z.Y X.Z) = 000.000; tan(Z.Y Y.X) = 000.000; tan(Z.Y Y.Y) = 180.000; tan(Z.Y Y.Z) = 000.000; tan(Z.Y Z.X) = 000.000; tan(Z.Y Z.Y) = 000.000; tan(Z.Y Z.Z) = 000.000; 
tan(Z.Z X.X) = 134.986; tan(Z.Z X.Y) = 091.774; tan(Z.Z X.Z) = 090.000; tan(Z.Z Y.X) = 088.225; tan(Z.Z Y.Y) = 134.986; tan(Z.Z Y.Z) = 090.000; tan(Z.Z Z.X) = 090.000; tan(Z.Z Z.Y) = 090.000; tan(Z.Z Z.Z) = 045.000; 

Candidates: 178.224
cos(  X.X  ) = 178.224; cos(  Y.Y  ) = 178.224;
tan(X.Y X.X) = 178.224; tan(X.Y Y.Y) = 178.224;
tan(Y.X X.X) = 178.224; tan(Y.X Y.Y) = 178.224;
*/

/* ( 0 | 1 | 0 )
axisX ( 1 | -0 | 0 )
axisY ( 0 | -0.773632 | 0.633635 )
axisZ ( 0 | -0.633635 | -0.773632 )

180.000 039.318 180.000 
sin(  X.X  ) = 090.000; sin(  X.Y  ) = 000.000; sin(  X.Z  ) = 000.000; sin(  Y.X  ) = 000.000; sin(  Y.Y  ) = 050.681; sin(  Y.Z  ) = 039.318; sin(  Z.X  ) = 000.000; sin(  Z.Y  ) = 039.318; sin(  Z.Z  ) = 050.681; 
cos(  X.X  ) = 000.000; cos(  X.Y  ) = 090.000; cos(  X.Z  ) = 090.000; cos(  Y.X  ) = 090.000; cos(  Y.Y  ) = 140.681; cos(  Y.Z  ) = 050.681; cos(  Z.X  ) = 090.000; cos(  Z.Y  ) = 129.318; cos(  Z.Z  ) = 140.681; 
tan(X.X X.X) = 045.000; tan(X.X X.Y) = 090.000; tan(X.X X.Z) = 090.000; tan(X.X Y.X) = 090.000; tan(X.X Y.Y) = 127.726; tan(X.X Y.Z) = 057.640; tan(X.X Z.X) = 090.000; tan(X.X Z.Y) = 122.359; tan(X.X Z.Z) = 127.726; 
tan(X.Y X.X) = 000.000; tan(X.Y X.Y) = 180.000; tan(X.Y X.Z) = 000.000; tan(X.Y Y.X) = 000.000; tan(X.Y Y.Y) = 180.000; tan(X.Y Y.Z) = 000.000; tan(X.Y Z.X) = 000.000; tan(X.Y Z.Y) = 180.000; tan(X.Y Z.Z) = 180.000; 
tan(X.Z X.X) = 000.000; tan(X.Z X.Y) = 180.000; tan(X.Z X.Z) = 000.000; tan(X.Z Y.X) = 000.000; tan(X.Z Y.Y) = 180.000; tan(X.Z Y.Z) = 000.000; tan(X.Z Z.X) = 000.000; tan(X.Z Z.Y) = 180.000; tan(X.Z Z.Z) = 180.000; 
tan(Y.X X.X) = 000.000; tan(Y.X X.Y) = 180.000; tan(Y.X X.Z) = 000.000; tan(Y.X Y.X) = 000.000; tan(Y.X Y.Y) = 180.000; tan(Y.X Y.Z) = 000.000; tan(Y.X Z.X) = 000.000; tan(Y.X Z.Y) = 180.000; tan(Y.X Z.Z) = 180.000; 
tan(Y.Y X.X) = 037.726; tan(Y.Y X.Y) = 090.000; tan(Y.Y X.Z) = 090.000; tan(Y.Y Y.X) = 090.000; tan(Y.Y Y.Y) = 135.000; tan(Y.Y Y.Z) = 050.681; tan(Y.Y Z.X) = 090.000; tan(Y.Y Z.Y) = 129.318; tan(Y.Y Z.Z) = 135.000; 
tan(Y.Z X.X) = 032.359; tan(Y.Z X.Y) = 090.000; tan(Y.Z X.Z) = 090.000; tan(Y.Z Y.X) = 090.000; tan(Y.Z Y.Y) = 140.681; tan(Y.Z Y.Z) = 045.000; tan(Y.Z Z.X) = 090.000; tan(Y.Z Z.Y) = 135.000; tan(Y.Z Z.Z) = 140.681; 
tan(Z.X X.X) = 000.000; tan(Z.X X.Y) = 180.000; tan(Z.X X.Z) = 000.000; tan(Z.X Y.X) = 000.000; tan(Z.X Y.Y) = 180.000; tan(Z.X Y.Z) = 000.000; tan(Z.X Z.X) = 000.000; tan(Z.X Z.Y) = 180.000; tan(Z.X Z.Z) = 180.000; 
tan(Z.Y X.X) = 032.359; tan(Z.Y X.Y) = 090.000; tan(Z.Y X.Z) = 090.000; tan(Z.Y Y.X) = 090.000; tan(Z.Y Y.Y) = 140.681; tan(Z.Y Y.Z) = 045.000; tan(Z.Y Z.X) = 090.000; tan(Z.Y Z.Y) = 135.000; tan(Z.Y Z.Z) = 140.681; 
tan(Z.Z X.X) = 037.726; tan(Z.Z X.Y) = 090.000; tan(Z.Z X.Z) = 090.000; tan(Z.Z Y.X) = 090.000; tan(Z.Z Y.Y) = 135.000; tan(Z.Z Y.Z) = 050.681; tan(Z.Z Z.X) = 090.000; tan(Z.Z Z.Y) = 129.318; tan(Z.Z Z.Z) = 135.000; 

Candidates: 039.318
sin(  Y.Z  ) = 039.318; sin(  Z.Y  ) = 039.318;
*/

/* ( 0 | 0 | 1 )
axisX ( -0.0553256 | 0 | 0.998468 )
axisY ( 0 | 1 | -0 )
axisZ ( -0.998468 | 0 | -0.0553256 )

000.000 000.000 093.171 
sin(  X.X  ) = 003.171; sin(  X.Y  ) = 000.000; sin(  X.Z  ) = 086.828; sin(  Y.X  ) = 000.000; sin(  Y.Y  ) = 090.000; sin(  Y.Z  ) = 000.000; sin(  Z.X  ) = 086.828; sin(  Z.Y  ) = 000.000; sin(  Z.Z  ) = 003.171; 
cos(  X.X  ) = 093.171; cos(  X.Y  ) = 090.000; cos(  X.Z  ) = 003.171; cos(  Y.X  ) = 090.000; cos(  Y.Y  ) = 000.000; cos(  Y.Z  ) = 090.000; cos(  Z.X  ) = 176.828; cos(  Z.Y  ) = 090.000; cos(  Z.Z  ) = 093.171; 
tan(X.X X.X) = 135.000; tan(X.X X.Y) = 090.000; tan(X.X X.Z) = 003.171; tan(X.X Y.X) = 090.000; tan(X.X Y.Y) = 003.166; tan(X.X Y.Z) = 090.000; tan(X.X Z.X) = 176.828; tan(X.X Z.Y) = 090.000; tan(X.X Z.Z) = 135.000; 
tan(X.Y X.X) = 180.000; tan(X.Y X.Y) = 000.000; tan(X.Y X.Z) = 000.000; tan(X.Y Y.X) = 000.000; tan(X.Y Y.Y) = 000.000; tan(X.Y Y.Z) = 180.000; tan(X.Y Z.X) = 180.000; tan(X.Y Z.Y) = 000.000; tan(X.Y Z.Z) = 180.000; 
tan(X.Z X.X) = 093.171; tan(X.Z X.Y) = 090.000; tan(X.Z X.Z) = 045.000; tan(X.Z Y.X) = 090.000; tan(X.Z Y.Y) = 044.956; tan(X.Z Y.Z) = 090.000; tan(X.Z Z.X) = 135.000; tan(X.Z Z.Y) = 090.000; tan(X.Z Z.Z) = 093.171; 
tan(Y.X X.X) = 180.000; tan(Y.X X.Y) = 000.000; tan(Y.X X.Z) = 000.000; tan(Y.X Y.X) = 000.000; tan(Y.X Y.Y) = 000.000; tan(Y.X Y.Z) = 180.000; tan(Y.X Z.X) = 180.000; tan(Y.X Z.Y) = 000.000; tan(Y.X Z.Z) = 180.000; 
tan(Y.Y X.X) = 093.166; tan(Y.Y X.Y) = 090.000; tan(Y.Y X.Z) = 045.043; tan(Y.Y Y.X) = 090.000; tan(Y.Y Y.Y) = 045.000; tan(Y.Y Y.Z) = 090.000; tan(Y.Y Z.X) = 134.956; tan(Y.Y Z.Y) = 090.000; tan(Y.Y Z.Z) = 093.166; 
tan(Y.Z X.X) = 180.000; tan(Y.Z X.Y) = 000.000; tan(Y.Z X.Z) = 000.000; tan(Y.Z Y.X) = 000.000; tan(Y.Z Y.Y) = 000.000; tan(Y.Z Y.Z) = 180.000; tan(Y.Z Z.X) = 180.000; tan(Y.Z Z.Y) = 000.000; tan(Y.Z Z.Z) = 180.000; 
tan(Z.X X.X) = 093.171; tan(Z.X X.Y) = 090.000; tan(Z.X X.Z) = 045.000; tan(Z.X Y.X) = 090.000; tan(Z.X Y.Y) = 044.956; tan(Z.X Y.Z) = 090.000; tan(Z.X Z.X) = 135.000; tan(Z.X Z.Y) = 090.000; tan(Z.X Z.Z) = 093.171; 
tan(Z.Y X.X) = 180.000; tan(Z.Y X.Y) = 000.000; tan(Z.Y X.Z) = 000.000; tan(Z.Y Y.X) = 000.000; tan(Z.Y Y.Y) = 000.000; tan(Z.Y Y.Z) = 180.000; tan(Z.Y Z.X) = 180.000; tan(Z.Y Z.Y) = 000.000; tan(Z.Y Z.Z) = 180.000; 
tan(Z.Z X.X) = 135.000; tan(Z.Z X.Y) = 090.000; tan(Z.Z X.Z) = 003.171; tan(Z.Z Y.X) = 090.000; tan(Z.Z Y.Y) = 003.166; tan(Z.Z Y.Z) = 090.000; tan(Z.Z Z.X) = 176.828; tan(Z.Z Z.Y) = 090.000; tan(Z.Z Z.Z) = 135.000; 

Candidates: 093.171
cos(  X.X  ) = 093.171; cos(  Z.Z  ) = 093.171;
tan(X.Z X.X) = 093.171; tan(X.Z Z.Z) = 093.171;
tan(Z.X X.X) = 093.171; tan(Z.X Z.Z) = 093.171;
*/

#include "General/UnitToString.hpp"
static EulerAngle3D forward(const EulerAngle3D & rot0, const EulerAngle3D & rot1)
{
	VectorF3 axisX = rot1.forward(rot0.forward(VectorF3(1, 0, 0)));
	VectorF3 axisY = rot1.forward(rot0.forward(VectorF3(0, 1, 0)));
	VectorF3 axisZ = rot1.forward(rot0.forward(VectorF3(0, 0, 1)));

	std::cout << "axisX " << axisX << '\n';
	std::cout << "axisY " << axisY << '\n';
	std::cout << "axisZ " << axisZ << '\n';
	std::cout << '\n';

	Angle angX = Angle::aTan2(axisX.Y, axisY.Y);
	Angle angY = Angle::aSin(axisY.Z);
	Angle angZ = Angle::aTan2(axisZ.X, axisZ.Z);
	std::cout << ToStringF32(angX.ToDegrees(), 3, 3) << ' ';
	std::cout << ToStringF32(angY.ToDegrees(), 3, 3) << ' ';
	std::cout << ToStringF32(angZ.ToDegrees(), 3, 3) << ' ';
	std::cout << '\n';

	{
		SAxiss axiss;
		axiss.axisX = axisX;
		axiss.axisY = axisY;
		axiss.axisZ = axisZ;
		const char * axis_str = "XYZXYZXYZ";

		for (unsigned int idx1 = 0; idx1 < 3; idx1++)
		{
			for (unsigned int idx0 = 0; idx0 < 3; idx0++)
			{
				Angle rot = axiss.TrySin(idx1, idx0);
				std::cout << "sin(  " << axis_str[idx1] << '.' << axis_str[idx0] << "  )";
				std::cout << " = " << ToStringF32(rot.ToDegrees(), 3, 3) << "; ";
			}
		}
		std::cout << '\n';
		for (unsigned int idx1 = 0; idx1 < 3; idx1++)
		{
			for (unsigned int idx0 = 0; idx0 < 3; idx0++)
			{
				Angle rot = axiss.TryCos(idx1, idx0);
				std::cout << "cos(  " << axis_str[idx1] << '.' << axis_str[idx0] << "  )";
				std::cout << " = " << ToStringF32(rot.ToDegrees(), 3, 3) << "; ";
			}
		}
		std::cout << '\n';
		for (unsigned int idx3 = 0; idx3 < 3; idx3++)
		{
			for (unsigned int idx2 = 0; idx2 < 3; idx2++)
			{
				for (unsigned int idx1 = 0; idx1 < 3; idx1++)
				{
					for (unsigned int idx0 = 0; idx0 < 3; idx0++)
					{
						Angle rot = axiss.TryTan(idx3, idx2, idx1, idx0);
						std::cout << "tan(" << axis_str[idx3] << '.' << axis_str[idx2] << ' ' << axis_str[idx1] << '.' << axis_str[idx0] << ")";
						std::cout << " = " << ToStringF32(rot.ToDegrees(), 3, 3) << "; ";
					}
				}
				std::cout << '\n';
			}
		}
		std::cout << '\n';
	}

	return EulerAngle3D(
		Angle::aTan2(axisX.Y, axisY.Y),
		Angle::aSin(axisY.Z),
		Angle::aTan2(axisZ.X, axisZ.Z)

		//Angle::aTan2(axisX.Z, axisZ.Z)
		//Angle::aSin(axisZ.Y)
		//Angle::aTan2(axisY.X, axisY.Y)
	);
}

int main(int argc, char * argv[])
{
	VectorF3 pos(
		(Random::Float01Ex() * 2) - 1,
		(Random::Float01Ex() * 2) - 1,
		(Random::Float01Ex() * 2) - 1
	);
	//std::cout << pos << '\n';
	//std::cout << '\n';

	//VectorF3 mul(0, 0, 0); // .
	//VectorF3 mul(1, 0, 0); // .
	//VectorF3 mul(0, 1, 0); // .
	VectorF3 mul(0, 0, 1); // .
	//VectorF3 mul(1, 1, 0); // !
	//VectorF3 mul(1, 0, 1); // !
	//VectorF3 mul(0, 1, 1); // !
	//VectorF3 mul(1, 1, 1); // !

	std::cout << mul << '\n';

	EulerAngle3D rot0 = EulerAngle3D::Radians(
		Random::Float01Ex() * PI * mul.X,
		Random::Float01Ex() * PI * mul.Y,
		Random::Float01Ex() * PI * mul.Z
	);
	EulerAngle3D rot1 = EulerAngle3D::Radians(
		Random::Float01Ex() * PI * mul.X,
		Random::Float01Ex() * PI * mul.Y,
		Random::Float01Ex() * PI * mul.Z
	);

	//std::cout << rot0 << '\n';
	//std::cout << rot1 << '\n';
	//std::cout << '\n';

	Matrix3x3 mat0 = Matrix3x3::Rotation(rot0);
	Matrix3x3 mat1 = Matrix3x3::Rotation(rot1);

	Matrix3x3 mat = Matrix3x3::Identity();
	mat = mat * mat1;
	mat = mat * mat0;

	EulerAngle3D rot = forward(rot0, rot1);

	std::cout << (rot1.forward(rot0.forward(pos))) << '\n';
	std::cout << (pos * mat) << '\n';
	std::cout << (rot.forward(pos)) << '\n';

	return 0;



	std::cout << "int main() ...\n";
	int ret = -1;
	Debug::NewFileInDir(DirectoryInfo("./logs/"));
	if (argc > 0)	{ Debug::Log << argv[0] << Debug::Done; }
	else			{ Debug::Log << "NoName" << Debug::Done; }
	if (glfwInit() == 0) { std::cout << "GLFW Init Failed\n"; return -1; }
	{
		try
		{
			Window window;
			window.Create();
			ContextBase::WindowPointer = &window;
			ContextBase::Change(newSelectorContext);
			while (ContextBase::NewContext.Function != nullptr)
			{
				ContextBase * context = ContextBase::NewContext.Invoke();
				ContextBase::NewContext.Assign(nullptr);
				context -> Run();
				delete context;
			}
			window.Delete();
			ContextBase::WindowPointer = nullptr;
			ret = 0;
			std::cout << "MainContext done\n";
		}
		catch (std::exception & ex)
		{ Debug::Log << "Error: " << ex.what() << Debug::Done; }
		catch (...)
		{ Debug::Log << "Error: " << "Unknown" << Debug::Done; }
	}
	glfwTerminate();
	Debug::Log << "main() return " << ret << Debug::Done;
	return ret;
}
