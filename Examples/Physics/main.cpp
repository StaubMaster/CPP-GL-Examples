
#include <iostream>
#include <sstream>
#include <exception>

#include "OpenGL.hpp"
#include "Debug.hpp"

#include "DataInclude.hpp"
#include "DataShow.hpp"

#include "Window.hpp"
#include "Function/Object.hpp"
#include "UserParameter/KeyBoardInclude.hpp"
#include "UserParameter/MouseInclude.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"
#include "Image.hpp"



#include "Graphics/Shader/Code.hpp"
#include "Miscellaneous/Container/Array.hpp"
#include "Miscellaneous/Container/Binary.hpp"
#include "Miscellaneous/EntryContainer/Binary.hpp"



#include "PolyGon/Physics2D/BufferArray.hpp"
#include "PolyGon/Physics2D/Shader.hpp"
#include "PolyGon/Main/Data.hpp"
#include "Inst/Physics2D/Data.hpp"

#include "PolyGon/PolyGon.hpp"
#include "PolyGon/Data.hpp"



#include "Physics2D/Collision.hpp"
#include "Physics2D/MainInstance.hpp"
#include "Physics2D/Object.hpp"



#include <math.h>



struct MainContext
{
DirectoryInfo ImageDir;
DirectoryInfo ShaderDir;
DirectoryInfo PolyHedraDir;
DirectoryInfo TextDir;

Window	window;
View2D	view;

MainContext()
	: ImageDir("../../media/Images")
	, ShaderDir("../../media/Shaders")
	, PolyHedraDir("../../media/YMT")
	, TextDir("../../media/Text")
	, window()
	, view(View2D::Default())
{
	{
		Container::Array<Shader::Code> code({
			Shader::Code(ShaderDir.File("Physics/2D.vert")),
			Shader::Code(ShaderDir.File("Physics/2D.frag")),
		});
		Physics2D_Shader.Change(code);
	}
}
~MainContext()
{ }



Physics2D::Shader	Physics2D_Shader;

Container::Array<Physics2D::MainInstance>	Physics2D_MainInstances;
Container::Binary<Physics2D::Object>		Physics2D_Objects;



void Make()
{
	Physics2D_MainInstances.Allocate(3, 3);



	unsigned int wall = 0;
	Physics2D_MainInstances[wall].BufferArray.Create();
	{
		PolyGon & poly_gon = *(Physics2D_MainInstances[wall].PolyGon);
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(-10, 0), ColorF4(1, 1, 1)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(+10, 0), ColorF4(1, 1, 1)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(-10, -1), ColorF4(0, 0, 0)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(+10, -1), ColorF4(0, 0, 0)));
		poly_gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(0), PolyGon::SideCorner(1), PolyGon::SideCorner(2)));
		poly_gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(2), PolyGon::SideCorner(1), PolyGon::SideCorner(3)));
	}
	Physics2D_MainInstances[wall].UpdateMain();

	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[wall], Trans2D(Point2D(0, -10), Angle2D(Angle::Degrees(  0))), Trans2D(Point2D(0, 0), Angle2D()), true));
	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[wall], Trans2D(Point2D(-10, 0), Angle2D(Angle::Degrees( 90))), Trans2D(Point2D(0, 0), Angle2D()), true));
	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[wall], Trans2D(Point2D(0, +10), Angle2D(Angle::Degrees(180))), Trans2D(Point2D(0, 0), Angle2D()), true));
	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[wall], Trans2D(Point2D(+10, 0), Angle2D(Angle::Degrees(270))), Trans2D(Point2D(0, 0), Angle2D()), true));



	unsigned int obj0 = 1;
	Physics2D_MainInstances[obj0].BufferArray.Create();
	{
		PolyGon & poly_gon = *(Physics2D_MainInstances[obj0].PolyGon);
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(+1, -1), ColorF4(1, 0, 0)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(-1, -1), ColorF4(0, 1, 0)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D( 0, +1), ColorF4(0, 0, 1)));
		poly_gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(0), PolyGon::SideCorner(1), PolyGon::SideCorner(2)));
	}
	Physics2D_MainInstances[obj0].UpdateMain();

//	Stuck in Wall. Bounces back "into" Wall every time it would get out.
//	No Force pushing it out.
//	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D(-10, 0), Angle2D(Angle::Degrees(0))), Trans2D(Point2D(-1, 0), Angle2D()), false));

	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D( 0,  0), Angle2D(Angle::Degrees(0))), Trans2D(Point2D( 0, 0), Angle2D()), false));

	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D(+3, -1), Angle2D(Angle::Degrees(40))), Trans2D(Point2D(-1, 0), Angle2D()), false));
	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D(-3, -1), Angle2D(Angle::Degrees(80))), Trans2D(Point2D(+1, 0), Angle2D()), false));
	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D(+3, +1), Angle2D(Angle::Degrees(190))), Trans2D(Point2D(-1, 0), Angle2D()), false));
	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D(-3, +1), Angle2D(Angle::Degrees(140))), Trans2D(Point2D(+1, 0), Angle2D()), false));
}



void Init()
{
	Physics2D_Shader.Create();

	Make();
}
void Free()
{
	Physics2D_Shader.Delete();
	Physics2D_Objects.Clear();
	for (unsigned int i = 0; i < Physics2D_MainInstances.Count(); i++)
	{
		Physics2D_MainInstances[i].BufferArray.Delete();
		Physics2D_MainInstances[i].Dispose();
	}
}



void Bounce(Physics2D::Object & obj0, Physics2D::Object & obj1)
{
	if (obj0.IsStatic && obj1.IsStatic) { return; }

	Physics2D::PolyGonContactData contact_data = Physics2D::PolyGonContactData::Check(obj0, obj1);
	if (!contact_data.Valid) { return; }

	Point2D Contact0 = obj0.PolyGon() -> Corners[contact_data.Contact0Udx].Pos;
	Point2D Contact1 = obj1.PolyGon() -> Corners[contact_data.Contact1Udx].Pos;

		Point2D normal = contact_data.Normal.normalize();
		float e = 1.0f;

		Point2D vel_rel = obj1.Vel().Pos - obj0.Vel().Pos;
		float NormalVelFactor = Point2D::dot(vel_rel, normal);

		float MassInverse0 = 0;
		float MassInverse1 = 0;
		if (!obj0.IsStatic) { MassInverse0 = 1 / obj0.Mass; }
		if (!obj1.IsStatic) { MassInverse1 = 1 / obj1.Mass; }
		float MassInverseSum = MassInverse0 + MassInverse1;

		Matrix2x2 InertiaTensor0 = Matrix2x2::Default();
		Matrix2x2 InertiaTensor1 = Matrix2x2::Default();
		Matrix2x2 InertiaTensorInverse0 = InertiaTensor0.Inverse();
		Matrix2x2 InertiaTensorInverse1 = InertiaTensor1.Inverse();
		/*	What is Inertia Tensor ?
				Wikipedia has info about 3D, but not 2D
		*/

		/*	how does Angular Velocity work in general ?
			others 3D:
				a Vector that points in the rotation axis
				with the Length being how fast it spins
			my 3D:
				euler angles
			even with euler angles, at any given instance,
			an object spins along a single plane
			but 2D first
		*/

		/*
			w = (RelCon.perp() / RelCon.len())
		*/

		Point2D RelativeContact0 = Contact0 - obj0.Now().Pos;
		Point2D RelativeContact1 = Contact1 - obj1.Now().Pos;
		Point2D RelativeContactPerp0 = RelativeContact0.perpendicular0();
		Point2D RelativeContactPerp1 = RelativeContact1.perpendicular0();

		//	Wiki Says (paraphrased)
		//	n   : normal
		//	In  : Inertia Tensor n
		//	rn  : Relative Contact n
		//	IFn : Inertia Factor n
		//	IF  : Inertia Factor
		//	IFn = (1 / In) * (rn x n) x rn		3D
		//	IFn = (1 / In) * (rn.perp())		2D (not use if this is correct)
		//	IF = (IF0 + IF1) dot n

		//Point2D InertiaFactor0 = InertiaTensorInverse0 * RelativeContactPerp0;
		//Point2D InertiaFactor1 = InertiaTensorInverse1 * RelativeContactPerp1;
		//float InertiaFactorSum = Point2D::dot(InertiaFactor0 + InertiaFactor1, normal);
		//(void)InertiaFactorSum;
		//std::cout << "InertiaFactor0 " << InertiaFactor0 << '\n';
		//std::cout << "InertiaFactor1 " << InertiaFactor1 << '\n';
		//std::cout << "InertiaFactorSum " << InertiaFactorSum << '\n';

		//float ImpulseFactor = (-(1.0f + e) * NormalVelFactor) / (MassInverseSum + InertiaFactorSum);
		float ImpulseFactor = (-(1.0f + e) * NormalVelFactor) / (MassInverseSum);
		Point2D Impulse = normal * ImpulseFactor;

		if (!obj0.IsStatic) { obj0.Vel().Pos -= (Impulse / obj0.Mass); }
		if (!obj1.IsStatic) { obj1.Vel().Pos += (Impulse / obj1.Mass); }

		//if (!obj0.IsStatic) { vel0.Rot -= (InertiaFactor0 * ImpulseFactor); }
		//if (!obj1.IsStatic) { vel1.Rot += (InertiaFactor1 * ImpulseFactor); }

	if (obj0.IsStatic) { obj0.Vel().Pos = Point2D(); }
	if (obj1.IsStatic) { obj1.Vel().Pos = Point2D(); }
}

void UpdateGravity(float timeDelta)
{
	Point2D	Gravity = view.Trans.Rot.rotateBack(Point2D(0, -1)) * (3.0f * timeDelta);
	for (unsigned int i = 0; i < Physics2D_Objects.Count(); i++)
	{
		if (!Physics2D_Objects[i].IsStatic)
		{
			Physics2D_Objects[i].Vel().Pos += Gravity;
		}
	}
}
void UpdateCollision()
{
	for (unsigned int i0 = 0; i0 < Physics2D_Objects.Count(); i0++)
	{
		for (unsigned int i1 = i0 + 1; i1 < Physics2D_Objects.Count(); i1++)
		{
			Bounce(Physics2D_Objects[i0], Physics2D_Objects[i1]);
		}
	}
}
void UpdateOrientation(float timeDelta)
{
	for (unsigned int i = 0; i < Physics2D_Objects.Count(); i++)
	{
		if (!Physics2D_Objects[i].IsStatic)
		{
			Physics2D_Objects[i].Now().Pos += (Physics2D_Objects[i].Vel().Pos * timeDelta);
			Physics2D_Objects[i].Now().Rot += (Physics2D_Objects[i].Vel().Rot * timeDelta);
		}
	}
}
void Update(float timeDelta)
{
	//UpdateGravity(timeDelta);
	UpdateCollision();
	UpdateOrientation(timeDelta);
}

void Frame(double timeDelta)
{
	//if (window.KeyBoardManager.Keys[GLFW_KEY_TAB].IsPress()) { window.MouseManager.CursorModeToggle(); }
	/*if (window.MouseManager.CursorModeIsLocked())
	{
		Trans3D trans = window.MoveSpinFromKeysCursor();
		if (window.KeyBoardManager.Keys[GLFW_KEY_LEFT_CONTROL].IsDown()) { trans.Pos *= 30; }
		trans.Pos *= 2;
		trans.Rot.X *= view.FOV.ToDegrees() * 0.005f;
		trans.Rot.Y *= view.FOV.ToDegrees() * 0.005f;
		trans.Rot.Z *= view.FOV.ToDegrees() * 0.005f;
		view.TransformFlatX(trans, timeDelta);
	}*/
	{
		Trans2D trans;
		Point3D move3D = window.MoveFromKeys();
		trans.Pos = Point2D(move3D.X, move3D.Z) * 2.0f;
		//if (window.KeyBoardManager.Keys[GLFW_KEY_LEFT_CONTROL].IsDown()) { move2D *= 30; }
		trans.Rot = Angle2D(Angle::Radians(move3D.Y * 0.5f));
		view.Transform(trans, timeDelta);
	}

	Update(timeDelta);

	Physics2D_Shader.Bind();
	Physics2D_Shader.View.Put(view.Trans);
	Physics2D_Shader.Scale.PutData(&view.Scale);

	for (unsigned int i = 0; i < Physics2D_MainInstances.Count(); i++)
	{
		Physics2D_MainInstances[i].UpdateInst();
	}



	GL::Disable(GL::Capability::DepthTest);
	GL::Disable(GL::Capability::CullFace);

	Physics2D_Shader.Bind();
	for (unsigned int i = 0; i < Physics2D_MainInstances.Count(); i++)
	{
		Physics2D_MainInstances[i].Draw();
	}
}
void Resize(const WindowBufferSize2D & WindowSize)
{
	Physics2D_Shader.Bind();
	Physics2D_Shader.WindowSize.Put(WindowSize);
}

void CursorScroll(UserParameter::Mouse::Scroll params)
{
	view.Scale -= params.Y * 1.0f;
	if (view.Scale <= 0)   { view.Scale = 1.0f; }
	if (view.Scale >= 100) { view.Scale = 100.0f; }
}



int Main()
{
	window.InitCallBack.Change<MainContext>(this, &MainContext::Init);
	window.FreeCallBack.Change<MainContext>(this, &MainContext::Free);
	window.FrameCallBack.Change<MainContext>(this, &MainContext::Frame);
	window.ResizeCallBack.Change<MainContext>(this, &MainContext::Resize);

	window.MouseManager.CallbackScroll.Change(this, &MainContext::CursorScroll);

	window.Create();
	Debug::Log << "<<<< Run Window" << Debug::Done;
	window.Run();
	Debug::Log << ">>>> Run Window" << Debug::Done;
	window.Delete();

	return 0;
}
};



int main(int argc, char * argv[])
{
	std::cout << "int main() ...\n";
	int ret = -1;
	Debug::NewFileInDir(DirectoryInfo("./logs/"));
	if (argc > 0)	{ Debug::Log << argv[0] << Debug::Done; }
	else			{ Debug::Log << "NoName" << Debug::Done; }
	if (glfwInit() == 0) { std::cout << "GLFW Init Failed\n"; return -1; }
	{
		try
		{
			MainContext context;
			ret = context.Main();
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
