
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
		float thickness = 0.1f;
		PolyGon & poly_gon = *(Physics2D_MainInstances[wall].PolyGon);
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(-1, 0), ColorF4(1, 1, 1)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(+1, 0), ColorF4(1, 1, 1)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(-1 - thickness, -thickness), ColorF4(0, 0, 0)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(+1 + thickness, -thickness), ColorF4(0, 0, 0)));
		poly_gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(0), PolyGon::SideCorner(1), PolyGon::SideCorner(2)));
		poly_gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(2), PolyGon::SideCorner(1), PolyGon::SideCorner(3)));
	}
	Physics2D_MainInstances[wall].UpdateMain();

	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[wall], Trans2D(Point2D( 0, -1), Angle2D(Angle::Degrees(  0))), Trans2D(Point2D(0, 0), Angle2D()), true));
	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[wall], Trans2D(Point2D(-1,  0), Angle2D(Angle::Degrees( 90))), Trans2D(Point2D(0, 0), Angle2D()), true));
	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[wall], Trans2D(Point2D( 0, +1), Angle2D(Angle::Degrees(180))), Trans2D(Point2D(0, 0), Angle2D()), true));
	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[wall], Trans2D(Point2D(+1,  0), Angle2D(Angle::Degrees(270))), Trans2D(Point2D(0, 0), Angle2D()), true));



	unsigned int obj0 = 1;
	Physics2D_MainInstances[obj0].BufferArray.Create();
	{
		PolyGon & poly_gon = *(Physics2D_MainInstances[obj0].PolyGon);
		//poly_gon.Corners.Insert(PolyGon::Corner(Point2D(+1, -1), ColorF4(1, 0, 0)));
		//poly_gon.Corners.Insert(PolyGon::Corner(Point2D(-1, -1), ColorF4(0, 1, 0)));
		//poly_gon.Corners.Insert(PolyGon::Corner(Point2D( 0, +1), ColorF4(0, 0, 1)));

		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(+0.025f, -0.400f), ColorF4(1, 0, 0)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(-0.025f, -0.400f), ColorF4(0, 1, 0)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D( 0.000f, +0.400f), ColorF4(0, 0, 1)));

		poly_gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(0), PolyGon::SideCorner(1), PolyGon::SideCorner(2)));
	}
	Physics2D_MainInstances[obj0].UpdateMain();

//	Stuck in Wall. Bounces back "into" Wall every time it would get out.
//	No Force pushing it out.
//	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D(-1.0f, 0.0f), Angle2D(Angle::Degrees(0))), Trans2D(Point2D(-1, 0), Angle2D()), false));

	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D(-0.3f, 0.000f), Angle2D(Angle::Degrees(90))), Trans2D(Point2D(0, 0), Angle2D()), false));

	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D(+0.3f, 0.025f), Angle2D(Angle::Degrees(180))), Trans2D(Point2D(0, 0), Angle2D(Angle::Degrees(-45))), false));

//	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D(+0.3f, -0.1f), Angle2D(Angle::Degrees(160))), Trans2D(Point2D(-0.1f, 0.0f), Angle2D()), false));
//	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D(-0.3f, -0.1f), Angle2D(Angle::Degrees( 80))), Trans2D(Point2D(+0.1f, 0.0f), Angle2D()), false));
//	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D(+0.3f, +0.1f), Angle2D(Angle::Degrees(190))), Trans2D(Point2D(-0.1f, 0.0f), Angle2D()), false));
//	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D(-0.3f, +0.1f), Angle2D(Angle::Degrees(140))), Trans2D(Point2D(+0.1f, 0.0f), Angle2D()), false));
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

	// Currently only handles one Contact. Should handle all Contacts
	Physics2D::PolyGonContactData contact_data = Physics2D::PolyGonContactData::Check(obj0, obj1);
	if (!contact_data.Valid) { return; }

	Point2D normal = contact_data.Normal.normalize();

	//Point2D Contact0 = obj0.PolyGon() -> Corners[contact_data.Contact0Udx].Pos;
	//Point2D Contact1 = obj1.PolyGon() -> Corners[contact_data.Contact1Udx].Pos;
	Point2D Contact0 = obj0.TransCorner(contact_data.Contact0Udx);
	Point2D Contact1 = obj1.TransCorner(contact_data.Contact1Udx);

	Point2D RelativeContact0 = Contact0 - obj0.Now().Pos;
	Point2D RelativeContact1 = Contact1 - obj1.Now().Pos;

	float ContactDistance0 = RelativeContact0.length();
	float ContactDistance1 = RelativeContact1.length();
	(void)ContactDistance0;
	(void)ContactDistance1;



	float MassInverse0 = 0;
	float MassInverse1 = 0;
	if (!obj0.IsStatic) { MassInverse0 = 1 / obj0.Mass; }
	if (!obj1.IsStatic) { MassInverse1 = 1 / obj1.Mass; }
	float MassInverseSum = MassInverse0 + MassInverse1;



	Point3D normal_3D(normal.X, normal.Y, 0);
	Point3D RelativeContact0_3D(RelativeContact0.X, RelativeContact0.Y, 0);
	Point3D RelativeContact1_3D(RelativeContact1.X, RelativeContact1.Y, 0);

	Point3D ContactNormal0_3D = Point3D::cross(RelativeContact0_3D, normal_3D);
	Point3D ContactNormal1_3D = Point3D::cross(RelativeContact1_3D, normal_3D);
	Point3D ContactPerpendicular0_3D = Point3D::cross(ContactNormal0_3D, RelativeContact0_3D);
	Point3D ContactPerpendicular1_3D = Point3D::cross(ContactNormal1_3D, RelativeContact1_3D);
	Point3D ContactPerpendicularSum_3D = ContactPerpendicular0_3D + ContactPerpendicular1_3D;

	float InertiaFactorSum = Point2D::dot(Point2D(ContactPerpendicularSum_3D.X, ContactPerpendicularSum_3D.Y), normal);



	std::cout << '\n';
	std::cout << "normal_3D: " << normal_3D << ' ' << normal_3D.length() << '\n';
	std::cout << "RelativeContact0_3D: " << RelativeContact0_3D << ' ' << RelativeContact0_3D.length() << '\n';
	std::cout << "RelativeContact1_3D: " << RelativeContact1_3D << ' ' << RelativeContact1_3D.length() << '\n';
	std::cout << "ContactPerpendicular0_3D: " << ContactPerpendicular0_3D << ' ' << ContactPerpendicular0_3D.length() << '\n';
	std::cout << "ContactPerpendicular1_3D: " << ContactPerpendicular1_3D << ' ' << ContactPerpendicular1_3D.length() << '\n';
	std::cout << "ContactPerpendicularSum_3D: " << ContactPerpendicularSum_3D << ' ' << ContactPerpendicularSum_3D.length() << '\n';
	std::cout << '\n';



	float e = 1.0f;
	Point2D vel_rel = obj1.Vel().Pos - obj0.Vel().Pos;
	float NormalVelFactor = Point2D::dot(vel_rel, normal);

	std::cout << "normal           : " << normal << '\n';
	std::cout << "vel_rel          : " << vel_rel << '\n';
	std::cout << "NormalVelFactor  : " << NormalVelFactor << '\n';
	std::cout << "MassInverseSum   : " << MassInverseSum << '\n';
	std::cout << "InertiaFactorSum : " << InertiaFactorSum << '\n';

	float ImpulseFactor = (-(1.0f + e) * NormalVelFactor) / (MassInverseSum + InertiaFactorSum);
//	float ImpulseFactor = (-(1.0f + e) * NormalVelFactor) / (MassInverseSum);
	std::cout << "ImpulseFactor " << ImpulseFactor << '\n';

	if (!obj0.IsStatic) { obj0.Vel().Pos -= normal * (ImpulseFactor / obj0.Mass); }
	if (!obj1.IsStatic) { obj1.Vel().Pos += normal * (ImpulseFactor / obj1.Mass); }

//	My Angle Spinning is "the wrong way". positive should be counter-clockwise, mine is clockwise
	if (!obj0.IsStatic) { obj0.Vel().Rot -= Angle::Radians((ContactNormal0_3D * ImpulseFactor).length()); }
	if (!obj1.IsStatic) { obj1.Vel().Rot += Angle::Radians((ContactNormal1_3D * ImpulseFactor).length()); }

	if (obj0.IsStatic) { obj0.Vel() = Trans2D(); }
	if (obj1.IsStatic) { obj1.Vel() = Trans2D(); }

	std::cout << '\n';
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


void Test()
{
/*
	Point3D	a(1.23, 5.48f, 9.28f);
	Point3D b(3.543f, 4.5f, 3.02f);
	Point3D c = Point3D::cross(a, b);
	Angle d = Angle::SaCos(Point3D::dot(a, b) / (a.length() * b.length()));
	std::cout << a << '\n';
	std::cout << b << '\n';
	std::cout << c << '\n';
	std::cout << a.length() << '\n';
	std::cout << b.length() << '\n';
	std::cout << c.length() << '\n';
	std::cout << d << '\n';
*/
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

	//Update(timeDelta);
	if (window.KeyBoardManager.Keys[GLFW_KEY_E].IsDown())
	{ Update(1 / 60.0f); }
	if (window.KeyBoardManager.Keys[GLFW_KEY_Q].IsPress())
	{ Update(1 / 60.0f); }

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

	Test();
}
void Resize(const WindowBufferSize2D & WindowSize)
{
	Physics2D_Shader.Bind();
	Physics2D_Shader.WindowSize.Put(WindowSize);
}

void CursorScroll(UserParameter::Mouse::Scroll params)
{
	Point2D HalfSize = window.Size.WindowSize / 2;

	Point2D CursorPos = window.MouseManager.CursorPixelPosition().Absolute - HalfSize;
	CursorPos.Y = -CursorPos.Y;
	CursorPos = (CursorPos / window.Size.Ratio) / HalfSize;

	Point2D ZoomPos = (CursorPos * view.Scale) + view.Trans.Pos;

	if (params.Y < 0.0f) { while (params.Y < 0.0f) { view.Scale *= 2; params.Y++; } }
	if (params.Y > 0.0f) { while (params.Y > 0.0f) { view.Scale /= 2; params.Y--; } }

	#define ZOOM_MIN 1.0 / (1 << 6)
	#define ZOOM_MAX 1.0 * (1 << 6)

	if (view.Scale <= ZOOM_MIN) { view.Scale = ZOOM_MIN; }
	if (view.Scale >= ZOOM_MAX) { view.Scale = ZOOM_MAX; }

	view.Trans.Pos = ZoomPos - (CursorPos * view.Scale);
}



int Main()
{
	window.InitCallBack.Change<MainContext>(this, &MainContext::Init);
	window.FreeCallBack.Change<MainContext>(this, &MainContext::Free);
	window.FrameCallBack.Change<MainContext>(this, &MainContext::Frame);
	window.ResizeCallBack.Change<MainContext>(this, &MainContext::Resize);

	window.MouseManager.CallbackScroll.Change(this, &MainContext::CursorScroll);

	view.Scale = 1.0f;

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
