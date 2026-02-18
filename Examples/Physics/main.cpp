
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

#include "Arrow2D/Main/Data.hpp"
#include "Arrow2D/Inst/Data.hpp"
#include "Arrow2D/Buffer.hpp"
#include "Arrow2D/Shader.hpp"

#include "Graphics/Texture/Array2D.hpp"

#include <math.h>



struct MainContext
{
DirectoryInfo ImageDir;
DirectoryInfo ShaderDir;
DirectoryInfo PolyHedraDir;
DirectoryInfo TextDir;

Window	window;
View2D	view;

bool Paused;

MainContext()
	: ImageDir("../../media/Images")
	, ShaderDir("../../media/Shaders")
	, PolyHedraDir("../../media/YMT")
	, TextDir("../../media/Text")
	, window()
	, view(View2D::Default())
	, Paused(true)
{
	{
		Container::Array<Shader::Code> code({
			Shader::Code(ShaderDir.File("Physics/2D.vert")),
			Shader::Code(ShaderDir.File("Physics/2D.frag")),
		});
		Physics2D_Shader.Change(code);
	}
	{
		Container::Array<Shader::Code> code({
			Shader::Code(ShaderDir.File("Arrow2D/View.vert")),
			Shader::Code(ShaderDir.File("Arrow2D/Shader.frag")),
		});
		Arrow2D_Shader.Change(code);
	}
}
~MainContext()
{ }



Physics2D::Shader	Physics2D_Shader;

Container::Array<Physics2D::MainInstance>	Physics2D_MainInstances;
Container::Binary<Physics2D::Object>		Physics2D_Objects;

Arrow2D::Shader	Arrow2D_Shader;
Arrow2D::Buffer	Arrow2D_Buffer;
Texture::Array2D Arrow2D_Texture;

/* Arrows
	Textures:
		Beginning
		Middle
		Ending
	Point2D Pos
	Point2D Dir (not normal)
	Size (width of Texture)

Len = |Dir|
		Pos								Pos + Dir
		|------------------Len------------------|
		# - - - # - - - - - - - - - - - # - - - #
	|	|		|						|		|
Size|	|		|						|		|
	|	|		|						|		|
		# - - - # - - - - - - - - - - - # - - - #
		|-Size--|						|--Size-|
				|--(Len - (Size * 2))---|
*/
void ArrowTest()
{
	Arrow2D_Buffer.Bind();

	{
		Container::Binary<FileInfo> files;
		files.Insert(ImageDir.File("Arrow/L0_32x32.png"));
		files.Insert(ImageDir.File("Arrow/M0_32x32.png"));
		files.Insert(ImageDir.File("Arrow/R1_32x32.png"));
		Arrow2D_Texture.Assign(32, 32, files);
	}

	{
		AxisBox2D	Pos;
		float		Tex;

		Container::Binary<Arrow2D::Main::Data> data;

		Pos = AxisBox2D(Point2D(-4, -1), Point2D(-2, +1));
		Tex = 0;
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Min.Y), Point3D(0, 0, Tex)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(0, 1, Tex)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(1, 0, Tex)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(1, 0, Tex)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(0, 1, Tex)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Max.Y), Point3D(1, 1, Tex)));

		Pos = AxisBox2D(Point2D(-1, -1), Point2D(+1, +1));
		Tex = 1;
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Min.Y), Point3D(0, 0, Tex)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(0, 1, Tex)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(1, 0, Tex)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(1, 0, Tex)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(0, 1, Tex)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Max.Y), Point3D(1, 1, Tex)));

		Pos = AxisBox2D(Point2D(+2, -1), Point2D(+4, +1));
		Tex = 2;
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Min.Y), Point3D(0, 0, Tex)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(0, 1, Tex)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(1, 0, Tex)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(1, 0, Tex)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(0, 1, Tex)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Max.Y), Point3D(1, 1, Tex)));

		Arrow2D_Buffer.Main.Change(data);
		/*std::cout << "Main: " << data.Count() << '\n';
		for (unsigned int i = 0; i < data.Count(); i++)
		{
			std::cout << data[i].Pos << ' ' << data[i].Tex << '\n';
		}*/
	}

	{
		Container::Binary<Arrow2D::Inst::Data> data;

		//	  0 x   0	-1.00 , -1.00
		//	 80 x  60	-0.75 , -0.75
		//	160 x 120	-0.50 , -0.50
		//	240 x 180	-0.25 , -0.25
		//	320 x 240	 0.00 ,  0.00
		//	400 x 300	+0.25 , +0.25
		//	480 x 360	+0.50 , +0.50
		//	560 x 420	+0.75 , +0.75
		//	640 x 480	+1.00 , +1.00

		//Point2D Cursor = AbsolutePositionToWindowPixel(window.MouseManager.CursorPixelPosition().Absolute);
		//data.Insert(Arrow2D::Inst::Data(Point2D(), Cursor, 20));
		//data.Insert(Arrow2D::Inst::Data(Point2D(0, 1), Point2D(1, 1), 20));

		Point2D now;
		Point2D vel;
		for (unsigned int i = 0; i < Physics2D_Objects.Count(); i++)
		{
			now = Physics2D_Objects[i].Now().Pos;
			vel = Physics2D_Objects[i].Vel().Pos;
			data.Insert(Arrow2D::Inst::Data(now, now + vel, 10));
			for (unsigned int j = 0; j < Physics2D_Objects[i].CornerCount(); j++)
			{
				Point2D p = Physics2D_Objects[i].CornerFromIndex(j);
				Point2D now = Physics2D_Objects[i].AbsolutePositionOf(p);
				Point2D vel = Physics2D_Objects[i].AbsoluteVelocityOf(p);
				data.Insert(Arrow2D::Inst::Data(now, now + vel, 10));
			}
		}

		Arrow2D_Buffer.Inst.Change(data);
		/*std::cout << "Inst: " << data.Count() << '\n';
		for (unsigned int i = 0; i < data.Count(); i++)
		{
			std::cout << data[i].Pos << ' ' << data[i].Dir << ' ' << data[i].Size << '\n';
		}*/
	}
	Arrow2D_Shader.Bind();
	Arrow2D_Shader.View.Put(view.Trans);
	Arrow2D_Shader.Scale.PutData(&view.Scale);

	Arrow2D_Texture.Bind();
	Arrow2D_Buffer.Draw();
}



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
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(+0.1f, -0.1f), ColorF4(1, 0, 0)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(-0.1f, -0.1f), ColorF4(0, 1, 0)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D( 0.0f, +0.1f), ColorF4(0, 0, 1)));
		poly_gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(0), PolyGon::SideCorner(1), PolyGon::SideCorner(2)));
	}
	Physics2D_MainInstances[obj0].UpdateMain();

	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D(0.0f, 0.0f), Angle2D(Angle::Degrees(0))), Trans2D(Point2D(0.0f, 0.0f), Angle2D()), false));

	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D(+0.3f, -0.1f), Angle2D(Angle::Degrees(160))), Trans2D(Point2D(0.0f, 0.0f), Angle2D(Angle::Degrees(45))), false));

//	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D(+0.3f, -0.1f), Angle2D(Angle::Degrees(160))), Trans2D(Point2D(-0.1f, 0.0f), Angle2D()), false));
//	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D(-0.3f, -0.1f), Angle2D(Angle::Degrees( 80))), Trans2D(Point2D(+0.1f, 0.0f), Angle2D()), false));
//	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D(+0.3f, +0.1f), Angle2D(Angle::Degrees(190))), Trans2D(Point2D(-0.1f, 0.0f), Angle2D()), false));
//	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D(-0.3f, +0.1f), Angle2D(Angle::Degrees(140))), Trans2D(Point2D(+0.1f, 0.0f), Angle2D()), false));

//	Stuck in Wall. Bounces back "into" Wall every time it would get out.
//	No Force pushing it out.
//	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D(-1.0f, 0.0f), Angle2D(Angle::Degrees(0))), Trans2D(Point2D(-1, 0), Angle2D()), false));



	unsigned int obj1 = 2;
	Physics2D_MainInstances[obj1].BufferArray.Create();
	{
		PolyGon & poly_gon = *(Physics2D_MainInstances[obj1].PolyGon);
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(+0.025f, -0.400f), ColorF4(1, 0, 0)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(-0.025f, -0.400f), ColorF4(0, 1, 0)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D( 0.000f, +0.400f), ColorF4(0, 0, 1)));
		poly_gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(0), PolyGon::SideCorner(1), PolyGon::SideCorner(2)));
	}
	Physics2D_MainInstances[obj1].UpdateMain();

//	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj1], Trans2D(Point2D(-0.3f, 0.000f), Angle2D(Angle::Degrees(90))), Trans2D(Point2D(0, 0), Angle2D()), false));
//	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj1], Trans2D(Point2D(+0.3f, 0.025f), Angle2D(Angle::Degrees(180))), Trans2D(Point2D(0, 0), Angle2D(Angle::Degrees(-45))), false));
}



void Init()
{
	Physics2D_Shader.Create();
	
	Arrow2D_Shader.Create();
	Arrow2D_Buffer.Create();
	Arrow2D_Texture.Create();

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

	Arrow2D_Shader.Delete();
	Arrow2D_Buffer.Delete();
	Arrow2D_Texture.Delete();
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
			//Physics2D::CollideLinear(Physics2D_Objects[i0], Physics2D_Objects[i1]); // good
			//Physics2D::CollideRotate(Physics2D_Objects[i0], Physics2D_Objects[i1]); // wack
			Physics2D::Collide(Physics2D_Objects[i0], Physics2D_Objects[i1]);
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
		//trans.Rot = Angle2D(Angle::Radians(move3D.Y * 0.5f));
		view.Transform(trans, timeDelta);
	}

	if (window.KeyBoardManager.Keys[GLFW_KEY_P].IsPress())
	{ Paused = !Paused; }

	if (Paused)
	{
		if (window.KeyBoardManager.Keys[GLFW_KEY_O].IsDown())
		{ Update(1 / 60.0f); }
		if (window.KeyBoardManager.Keys[GLFW_KEY_I].IsPress())
		{ Update(1 / 60.0f); }
	}
	else
	{
		Update(timeDelta);
	}

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
	ArrowTest();
}
void Resize(const WindowBufferSize2D & WindowSize)
{
	Physics2D_Shader.Bind();
	Physics2D_Shader.WindowSize.Put(WindowSize);
	Arrow2D_Shader.Bind();
	Arrow2D_Shader.WindowSize.Put(WindowSize);
}

//	Make this better and Put into Window
//	Make similar Function for reverse Calculation
Point2D AbsolutePositionToWindowPixel(Point2D pos)
{
	Point2D HalfSize = window.Size.WindowSize / 2;	// Calculate in Window ?
	Point2D CursorPos = pos - HalfSize;
	CursorPos.Y = -CursorPos.Y;
	CursorPos = (CursorPos / window.Size.Ratio) / HalfSize;
	return (CursorPos * view.Scale) + view.Trans.Pos;
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
