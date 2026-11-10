#include <iostream>

#include "ValueGen/Random.hpp"
#include "ValueType/Vector/F3.hpp"
#include "ValueType/EulerAngle3D.hpp"
#include "ValueType/Matrix/3x3.hpp"

#include "ValueType/_Show.hpp"
#include "UnitToString.hpp"

__attribute__((unused)) static Angle LoopAngle(Angle angle)
{
	while (angle.ToDegrees() > +180) { angle -= Angle::Degrees(360); }
	while (angle.ToDegrees() < -180) { angle += Angle::Degrees(360); }
	return angle;
}
__attribute__((unused)) static EulerAngle3D LoopAngle(EulerAngle3D angle)
{
	angle.Z0 = LoopAngle(angle.Z0);
	angle.X1 = LoopAngle(angle.X1);
	angle.Y2 = LoopAngle(angle.Y2);
	return angle;
}

__attribute__((unused)) static void PrintAngle(const Angle & angle)
{
	std::cout << ToStringF32(angle.ToDegrees(), 3, 3);
}
__attribute__((unused)) static void PrintAngle(const EulerAngle3D & angle)
{
	PrintAngle(angle.Z0); std::cout << ' ';
	PrintAngle(angle.X1); std::cout << ' ';
	PrintAngle(angle.Y2); std::cout << ' ';
	std::cout << '\n';
}

struct SAxiss
{
	VectorF3	axisX;
	VectorF3	axisY;
	VectorF3	axisZ;

	SAxiss()
		: axisX(1, 0, 0)
		, axisY(0, 1, 0)
		, axisZ(0, 0, 1)
	{ }

	void forward(const EulerAngle3D & e)
	{
		axisX = e.forward(axisX);
		axisY = e.forward(axisY);
		axisZ = e.forward(axisZ);
	}
	void reverse(const EulerAngle3D & e)
	{
		axisX = e.reverse(axisX);
		axisY = e.reverse(axisY);
		axisZ = e.reverse(axisZ);
	}

	Angle TrySin(unsigned int idx1, unsigned int idx0) const
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
	Angle TryCos(unsigned int idx1, unsigned int idx0) const
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
	Angle TryTan(float val, unsigned int idx1, unsigned int idx0) const
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
	Angle TryTan(unsigned int idx3, unsigned int idx2, unsigned int idx1, unsigned int idx0) const
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

	Angle Find(unsigned int idx) const
	{
		for (unsigned int idx1 = 0; idx1 < 3; idx1++)
		{
			for (unsigned int idx0 = 0; idx0 < 3; idx0++)
			{
				if (idx == 0)
				{
					return +TrySin(idx1, idx0);
				}
				idx--;
				if (idx == 0)
				{
					return -TrySin(idx1, idx0);
				}
				idx--;
			}
		}

		for (unsigned int idx1 = 0; idx1 < 3; idx1++)
		{
			for (unsigned int idx0 = 0; idx0 < 3; idx0++)
			{
				if (idx == 0)
				{
					return +TryCos(idx1, idx0);
				}
				idx--;
				if (idx == 0)
				{
					return -TryCos(idx1, idx0);
				}
				idx--;
			}
		}

		for (unsigned int idx3 = 0; idx3 < 3; idx3++)
		{
			for (unsigned int idx2 = 0; idx2 < 3; idx2++)
			{
				for (unsigned int idx1 = 0; idx1 < 3; idx1++)
				{
					for (unsigned int idx0 = 0; idx0 < 3; idx0++)
					{
						if (idx == 0)
						{
							return +TryTan(idx3, idx2, idx1, idx0);
						}
						idx--;
						if (idx == 0)
						{
							return -TryTan(idx3, idx2, idx1, idx0);
						}
						idx--;
					}
				}
			}
		}

		return Angle();
	}
	void Print(unsigned int idx) const
	{
		const char * axis_str = "XYZ";

		for (unsigned int idx1 = 0; idx1 < 3; idx1++)
		{
			for (unsigned int idx0 = 0; idx0 < 3; idx0++)
			{
				if (idx == 0)
				{
					std::cout << "+sin(  " << axis_str[idx1] << '.' << axis_str[idx0] << "  )";
					return;
				}
				idx--;
				if (idx == 0)
				{
					std::cout << "-sin(  " << axis_str[idx1] << '.' << axis_str[idx0] << "  )";
					return;
				}
				idx--;
			}
		}

		for (unsigned int idx1 = 0; idx1 < 3; idx1++)
		{
			for (unsigned int idx0 = 0; idx0 < 3; idx0++)
			{
				if (idx == 0)
				{
					std::cout << "+cos(  " << axis_str[idx1] << '.' << axis_str[idx0] << "  )";
					return;
				}
				idx--;
				if (idx == 0)
				{
					std::cout << "-cos(  " << axis_str[idx1] << '.' << axis_str[idx0] << "  )";
					return;
				}
				idx--;
			}
		}

		for (unsigned int idx3 = 0; idx3 < 3; idx3++)
		{
			for (unsigned int idx2 = 0; idx2 < 3; idx2++)
			{
				for (unsigned int idx1 = 0; idx1 < 3; idx1++)
				{
					for (unsigned int idx0 = 0; idx0 < 3; idx0++)
					{
						if (idx == 0)
						{
							std::cout << "+tan(" << axis_str[idx3] << '.' << axis_str[idx2] << ' ' << axis_str[idx1] << '.' << axis_str[idx0] << ")";
							return;
						}
						idx--;
						if (idx == 0)
						{
							std::cout << "-tan(" << axis_str[idx3] << '.' << axis_str[idx2] << ' ' << axis_str[idx1] << '.' << axis_str[idx0] << ")";
							return;
						}
						idx--;
					}
				}
			}
		}

		std::cout << "none(  " << idx << "  )";
	}
};


__attribute__((unused)) static EulerAngle3D RandomEulerAngle3D()
{
	return EulerAngle3D::Radians(
		Random::Float01Ex() * Angle::Pi,
		Random::Float01Ex() * Angle::Pi,
		Random::Float01Ex() * Angle::Pi
	);
}
__attribute__((unused)) static VectorF3 RandomVectorF3()
{
	return VectorF3(
		(Random::Float01Ex() * 2) - 1,
		(Random::Float01Ex() * 2) - 1,
		(Random::Float01Ex() * 2) - 1
	);
}

__attribute__((unused)) static void FindEulerAngleCombination(const SAxiss & axiss, const VectorF3 & comp, const VectorF3 & pos)
{
	unsigned int best_diff_z0 = 0xFFFFFFFF;
	unsigned int best_diff_x1 = 0xFFFFFFFF;
	unsigned int best_diff_y2 = 0xFFFFFFFF;
	float best_diff_sum = 1.0f / 0.0f;

	EulerAngle3D rot;
	for (unsigned int idx_z0 = 0; idx_z0 < 198; idx_z0++)
	{
		rot.Z0 = axiss.Find(idx_z0);
		for (unsigned int idx_x1 = 0; idx_x1 < 198; idx_x1++)
		{
			rot.X1 = axiss.Find(idx_x1);
			for (unsigned int idx_y2 = 0; idx_y2 < 198; idx_y2++)
			{
				rot.Y2 = axiss.Find(idx_y2);
				VectorF3 have = rot.reverse(pos);
				VectorF3 diff = (have - comp).abs();
				float diff_sum = diff.X + diff.Y + diff.Z;
				if (diff.X < 0.001f && diff.Y < 0.001f && diff.Z < 0.001f)
				{
					//std::cout << '[' << ToStringU32(idx_z0, 3) << ']'; axiss.Print(idx_z0); std::cout << ' ';
					//std::cout << '[' << ToStringU32(idx_x1, 3) << ']'; axiss.Print(idx_x1); std::cout << ' ';
					//std::cout << '[' << ToStringU32(idx_y2, 3) << ']'; axiss.Print(idx_y2); std::cout << ' ';
					//std::cout << ToStringF32(diff_sum, 10);
					//std::cout << '\n';
					if (diff_sum < best_diff_sum)
					{
						best_diff_z0 = idx_z0;
						best_diff_x1 = idx_x1;
						best_diff_y2 = idx_y2;
						best_diff_sum = diff_sum;
					}
				}
			}
		}
	}
	//std::cout << '\n';

	std::cout << '[' << ToStringU32(best_diff_z0, 3) << ']'; axiss.Print(best_diff_z0); std::cout << ' ';
	std::cout << '[' << ToStringU32(best_diff_x1, 3) << ']'; axiss.Print(best_diff_x1); std::cout << ' ';
	std::cout << '[' << ToStringU32(best_diff_y2, 3) << ']'; axiss.Print(best_diff_y2); std::cout << ' ';
	std::cout << ToStringF32(best_diff_sum, 10);
	std::cout << '\n';
	//std::cout << '\n';
}
__attribute__((unused)) static void FindEulerAngle(const EulerAngle3D & rot, const VectorF3 & pos)
{
	//VectorF3 comp = rot.reverse(pos);
	VectorF3 comp = rot.forward(pos);

	SAxiss axiss;
	//axiss.forward(rot);
	axiss.reverse(rot);

	FindEulerAngleCombination(axiss, comp, pos);
}
__attribute__((unused)) static void FindEulerAngle(const EulerAngle3D & rot0, const EulerAngle3D & rot1, const VectorF3 & pos)
{
	VectorF3 comp = rot1.reverse(rot0.reverse(pos));

	SAxiss axiss;
	axiss.reverse(rot0);
	axiss.reverse(rot1);

	FindEulerAngleCombination(axiss, comp, pos);
}

__attribute__((unused)) static void TryEulerAngle()
{
	VectorF3 pos = RandomVectorF3();
	EulerAngle3D rot0 = RandomEulerAngle3D();
	EulerAngle3D rot1 = RandomEulerAngle3D();

	EulerAngle3D rot = rot0.reverse(rot1);

	std::cout << rot1.reverse(rot0.reverse(pos)) << '\n';
	std::cout << rot.reverse(pos) << '\n';
	std::cout << '\n';
}

int main()
{
	for (unsigned int i = 0; i < 10; i++)
	{
		FindEulerAngle(RandomEulerAngle3D(), RandomVectorF3());
		//FindEulerAngle(RandomEulerAngle3D(), RandomEulerAngle3D(), RandomVectorF3());
	}

	/*for (unsigned int i = 0; i < 10; i++)
	{
		TryEulerAngle();
	}*/

	return 0;
}
