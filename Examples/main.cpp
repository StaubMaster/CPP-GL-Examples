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
#include "General/UnitToString.hpp"

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

	Angle Find(unsigned int idx)
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
	void Print(unsigned int idx)
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
					std::cout << "+sin(  " << axis_str[idx1] << '.' << axis_str[idx0] << "  )";
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

	void Find(Angle rot)
	{
		for (unsigned int i = 0; i < 198; i++)
		{
			Angle r = Find(i);
			if (rot.ToRadians() != 0.0f)
			{
				float diff = abs(LoopAngle(r - rot).ToDegrees());
				if (diff < 0.001f)
				{
					std::cout << '[' << ToStringU32(i, 3) << ']';
					Print(i);
					std::cout << '\n';
				}
			}
		}
	}
};

__attribute__((unused)) static void forward_1_Z0_Combinations(EulerAngle3D rot0, EulerAngle3D rot1)
{
	rot0.X1 = Angle();
	rot1.X1 = Angle();

	rot0.Y2 = Angle();
	rot1.Y2 = Angle();

	SAxiss axiss;
	axiss.axisX = rot1.forward(rot0.forward(VectorF3(1, 0, 0)));
	axiss.axisY = rot1.forward(rot0.forward(VectorF3(0, 1, 0)));
	axiss.axisZ = rot1.forward(rot0.forward(VectorF3(0, 0, 1)));

	Angle sum = LoopAngle(rot0.Z0 + rot1.Z0);
	std::cout << "Z0: " << ToStringF32(sum.ToDegrees(), 3, 3) << '\n';
	axiss.Find(sum);
	std::cout << '\n';
}
__attribute__((unused)) static void forward_1_X1_Combinations(EulerAngle3D rot0, EulerAngle3D rot1)
{
	rot0.Z0 = Angle();
	rot1.Z0 = Angle();

	rot0.Y2 = Angle();
	rot1.Y2 = Angle();

	SAxiss axiss;
	axiss.axisX = rot1.forward(rot0.forward(VectorF3(1, 0, 0)));
	axiss.axisY = rot1.forward(rot0.forward(VectorF3(0, 1, 0)));
	axiss.axisZ = rot1.forward(rot0.forward(VectorF3(0, 0, 1)));

	Angle sum = LoopAngle(rot0.X1 + rot1.X1);
	std::cout << "X1: " << ToStringF32(sum.ToDegrees(), 3, 3) << '\n';
	axiss.Find(sum);
	std::cout << '\n';
}
__attribute__((unused)) static void forward_1_Y2_Combinations(EulerAngle3D rot0, EulerAngle3D rot1)
{
	rot0.Z0 = Angle();
	rot1.Z0 = Angle();

	rot0.X1 = Angle();
	rot1.X1 = Angle();

	SAxiss axiss;
	axiss.axisX = rot1.forward(rot0.forward(VectorF3(1, 0, 0)));
	axiss.axisY = rot1.forward(rot0.forward(VectorF3(0, 1, 0)));
	axiss.axisZ = rot1.forward(rot0.forward(VectorF3(0, 0, 1)));

	Angle sum = LoopAngle(rot0.Y2 + rot1.Y2);
	std::cout << "Y2: " << ToStringF32(sum.ToDegrees(), 3, 3) << '\n';
	axiss.Find(sum);
	std::cout << '\n';
}

__attribute__((unused)) static unsigned int valid_Z0_num = 6;
__attribute__((unused)) static unsigned int valid_X1_num = 6;
__attribute__((unused)) static unsigned int valid_Y2_num = 8;

__attribute__((unused)) static unsigned int valid_Z0[] = {
 19,
 27,
 54,
 62,
 91,
 99,
};
__attribute__((unused)) static unsigned int valid_X1[] = {
 26,
 34,
134,
142,
171,
179,
};
__attribute__((unused)) static unsigned int valid_Y2[] = {
 19,
 35,
 73,
 89,
109,
125,
144,
160,
};

__attribute__((unused)) static void forward_2_Z0_X1_Combinations(EulerAngle3D rot0, EulerAngle3D rot1, VectorF3 pos)
{
	rot0.Y2 = Angle();
	rot1.Y2 = Angle();

	SAxiss axiss;
	axiss.axisX = rot1.forward(rot0.forward(VectorF3(1, 0, 0)));
	axiss.axisY = rot1.forward(rot0.forward(VectorF3(0, 1, 0)));
	axiss.axisZ = rot1.forward(rot0.forward(VectorF3(0, 0, 1)));

	std::cout << "Z0 X1 __\n";

	VectorF3 want = rot1.forward(rot0.forward(pos));
	std::cout << want << '\n';
	std::cout << '\n';

	for (unsigned int i_z0 = 0; i_z0 < valid_Z0_num; i_z0++)
	{
		for (unsigned int i_x1 = 0; i_x1 < valid_X1_num; i_x1++)
		{
			unsigned int i0 = valid_Z0[i_z0];
			unsigned int i1 = valid_X1[i_x1];

			EulerAngle3D rot(
				axiss.Find(i0),
				axiss.Find(i1),
				Angle()
			);

			VectorF3 have = rot.forward(pos);
			VectorF3 diff = (want - have).abs();

			std::cout << '[' << ToStringU32(i0, 3) << ']';
			axiss.Print(i0);
			std::cout << ' ';

			std::cout << '[' << ToStringU32(i1, 3) << ']';
			axiss.Print(i1);
			std::cout << ' ';

			if (diff.X < 0.001f && diff.Y < 0.001f && diff.Z < 0.001f)
			{ std::cout << " yes"; }
			else
			{ std::cout << " no"; }
			std::cout << '\n';
		}
	}

	std::cout << '\n';
}
__attribute__((unused)) static void forward_2_X1_Y2_Combinations(EulerAngle3D rot0, EulerAngle3D rot1, VectorF3 pos)
{
	rot0.Z0 = Angle();
	rot1.Z0 = Angle();

	SAxiss axiss;
	axiss.axisX = rot1.forward(rot0.forward(VectorF3(1, 0, 0)));
	axiss.axisY = rot1.forward(rot0.forward(VectorF3(0, 1, 0)));
	axiss.axisZ = rot1.forward(rot0.forward(VectorF3(0, 0, 1)));

	std::cout << "__ X1 Y2\n";

	VectorF3 want = rot1.forward(rot0.forward(pos));
	std::cout << want << '\n';
	std::cout << '\n';

	for (unsigned int i_x1 = 0; i_x1 < valid_X1_num; i_x1++)
	{
		for (unsigned int i_y2 = 0; i_y2 < valid_Y2_num; i_y2++)
		{
			unsigned int i0 = valid_X1[i_x1];
			unsigned int i1 = valid_Y2[i_y2];

			EulerAngle3D rot(
				Angle(),
				axiss.Find(i0),
				axiss.Find(i1)
			);

			VectorF3 have = rot.forward(pos);
			VectorF3 diff = (want - have).abs();

			std::cout << '[' << ToStringU32(i0, 3) << ']';
			axiss.Print(i0);
			std::cout << ' ';

			std::cout << '[' << ToStringU32(i1, 3) << ']';
			axiss.Print(i1);
			std::cout << ' ';

			if (diff.X < 0.001f && diff.Y < 0.001f && diff.Z < 0.001f)
			{ std::cout << " yes"; }
			else
			{ std::cout << " no"; }
			std::cout << '\n';
		}
	}

	std::cout << '\n';
}
__attribute__((unused)) static void forward_2_Y2_Z0_Combinations(EulerAngle3D rot0, EulerAngle3D rot1, VectorF3 pos)
{
	rot0.X1 = Angle();
	rot1.X1 = Angle();

	SAxiss axiss;
	axiss.axisX = rot1.forward(rot0.forward(VectorF3(1, 0, 0)));
	axiss.axisY = rot1.forward(rot0.forward(VectorF3(0, 1, 0)));
	axiss.axisZ = rot1.forward(rot0.forward(VectorF3(0, 0, 1)));

	std::cout << "Z0 __ Y2\n";

	VectorF3 want = rot1.forward(rot0.forward(pos));
	std::cout << want << '\n';
	std::cout << '\n';

	for (unsigned int i_y2 = 0; i_y2 < valid_Y2_num; i_y2++)
	{
		for (unsigned int i_z0 = 0; i_z0 < valid_Z0_num; i_z0++)
		{
			unsigned int i0 = valid_Y2[i_y2];
			unsigned int i1 = valid_Z0[i_z0];

			EulerAngle3D rot(
				axiss.Find(i1),
				Angle(),
				axiss.Find(i0)
			);

			VectorF3 have = rot.forward(pos);
			VectorF3 diff = (want - have).abs();

			std::cout << '[' << ToStringU32(i0, 3) << ']';
			axiss.Print(i0);
			std::cout << ' ';

			std::cout << '[' << ToStringU32(i1, 3) << ']';
			axiss.Print(i1);
			std::cout << ' ';

			if (diff.X < 0.001f && diff.Y < 0.001f && diff.Z < 0.001f)
			{ std::cout << " yes"; }
			else
			{ std::cout << " no"; }
			std::cout << '\n';
		}
	}

	std::cout << '\n';
}

static void FindEulerAngle()
{
	VectorF3 pos(
		(Random::Float01Ex() * 2) - 1,
		(Random::Float01Ex() * 2) - 1,
		(Random::Float01Ex() * 2) - 1
	);
	EulerAngle3D rot0 = EulerAngle3D::Radians(
		Random::Float01Ex() * PI,
		Random::Float01Ex() * PI,
		Random::Float01Ex() * PI
	);
	EulerAngle3D rot1 = EulerAngle3D::Radians(
		Random::Float01Ex() * PI,
		Random::Float01Ex() * PI,
		Random::Float01Ex() * PI
	);

	//forward_1_Z0_Combinations(rot0, rot1);
	//forward_1_X1_Combinations(rot0, rot1);
	//forward_1_Y2_Combinations(rot0, rot1);

	//forward_2_Z0_X1_Combinations(rot0, rot1, pos);
	//forward_2_X1_Y2_Combinations(rot0, rot1, pos);
	//forward_2_Y2_Z0_Combinations(rot0, rot1, pos);

	VectorF3 want = rot1.forward(rot0.forward(pos));
	std::cout << want << '\n';
	std::cout << '\n';

	SAxiss axiss;
	axiss.axisX = rot1.forward(rot0.forward(VectorF3(1, 0, 0)));
	axiss.axisY = rot1.forward(rot0.forward(VectorF3(0, 1, 0)));
	axiss.axisZ = rot1.forward(rot0.forward(VectorF3(0, 0, 1)));

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
				VectorF3 have = rot.forward(pos);
				VectorF3 diff = (have - want).abs();
				if (diff.X < 0.001f && diff.Y < 0.001f && diff.Z < 0.001f)
				{
					std::cout << '[' << ToStringU32(idx_z0, 3) << ']'; axiss.Print(idx_z0); std::cout << ' ';
					std::cout << '[' << ToStringU32(idx_x1, 3) << ']'; axiss.Print(idx_x1); std::cout << ' ';
					std::cout << '[' << ToStringU32(idx_y2, 3) << ']'; axiss.Print(idx_y2); std::cout << ' ';
					std::cout << have;
					std::cout << '\n';
				}
			}
		}
	}

	// [062]+tan(X.Y Y.Y) [015]+sin(  Z.Y  ) [160]+tan(Z.X Z.Z) ( 0.758018 | 0.123519 | -0.82883 )
}



int main(int argc, char * argv[])
{
	FindEulerAngle();
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
