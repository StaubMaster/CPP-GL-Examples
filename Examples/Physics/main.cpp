
#include <iostream>
#include <sstream>
#include <exception>

#include "OpenGL.hpp"
#include "Debug.hpp"

#include "DataInclude.hpp"
#include "DataShow.hpp"
#include "ValueType/Intersect.hpp"

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

#include "Arrow2D/Manager.hpp"
#include "Arrow2D/Main/Data.hpp"
#include "Arrow2D/Inst/Data.hpp"

#include "WireFrame2D/WireFrame2D.hpp"
#include "WireFrame2D/Main/Buffer.hpp"
#include "WireFrame2D/Shader.hpp"

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
	Arrow2DInit();
}
~MainContext()
{ }



Physics2D::Shader	Physics2D_Shader;

Container::Array<Physics2D::MainInstance>	Physics2D_MainInstances;
Container::Binary<Physics2D::Object>		Physics2D_Objects;

unsigned int FindHoveringObjectIndex(Point2D p)
{
	for (unsigned int i = 0; i < Physics2D_Objects.Count(); i++)
	{
		if (Physics2D_Objects[i].IsContaining(p))
		{
			return i;
		}
	}
	return 0xFFFFFFFF;
}

Arrow2D::Manager Arrow2D_Manager;
// Init: sets all the File stuff
void Arrow2DInit()
{
	Container::Array<Shader::Code> code({
		Shader::Code(ShaderDir.File("Arrow/2D.vert")),
		Shader::Code(ShaderDir.File("Arrow/2D.frag")),
	});
	Arrow2D_Manager.Shader.Change(code);

	Arrow2D_Manager.Buffer.Main.Pos.Change(0);
	Arrow2D_Manager.Buffer.Main.Tex.Change(1);
	Arrow2D_Manager.Buffer.Inst.Pos0.Change(2);
	Arrow2D_Manager.Buffer.Inst.Pos1.Change(3);
	Arrow2D_Manager.Buffer.Inst.Size.Change(4);
	Arrow2D_Manager.Buffer.Inst.Col.Change(5);
}
// sets GL Buffers
void Arrow2DMake()
{
	{
		AxisBox2D	Pos;
		AxisBox2D	Tex;

		Container::Binary<Arrow2D::Main::Data> data;

		Pos = AxisBox2D(Point2D(-3, -1), Point2D(-1, +1));
		Tex = AxisBox2D(Point2D(0 / 96.0f, 0), Point2D(32 / 96.0f, 1));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Min.Y), Point3D(Tex.Min.X, Tex.Min.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(Tex.Min.X, Tex.Max.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(Tex.Max.X, Tex.Min.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(Tex.Max.X, Tex.Min.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(Tex.Min.X, Tex.Max.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Max.Y), Point3D(Tex.Max.X, Tex.Max.Y, 0)));

		Pos = AxisBox2D(Point2D(-1, -1), Point2D(+1, +1));
		Tex = AxisBox2D(Point2D(32 / 96.0f, 0), Point2D(64 / 96.0f, 1));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Min.Y), Point3D(Tex.Min.X, Tex.Min.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(Tex.Min.X, Tex.Max.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(Tex.Max.X, Tex.Min.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(Tex.Max.X, Tex.Min.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(Tex.Min.X, Tex.Max.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Max.Y), Point3D(Tex.Max.X, Tex.Max.Y, 0)));

		Pos = AxisBox2D(Point2D(+1, -1), Point2D(+3, +1));
		Tex = AxisBox2D(Point2D(64 / 96.0f, 0), Point2D(96 / 96.0f, 1));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Min.Y), Point3D(Tex.Min.X, Tex.Min.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(Tex.Min.X, Tex.Max.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(Tex.Max.X, Tex.Min.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(Tex.Max.X, Tex.Min.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(Tex.Min.X, Tex.Max.Y, 0)));
		data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Max.Y), Point3D(Tex.Max.X, Tex.Max.Y, 0)));

		Arrow2D_Manager.Buffer.Main.Change(data);
		/*std::cout << "Main: " << data.Count() << '\n';
		for (unsigned int i = 0; i < data.Count(); i++)
		{
			std::cout << data[i].Pos << ' ' << data[i].Tex << '\n';
		}*/
	}

	{
		Arrow2D_Manager.Texture.Bind();
		Container::Binary<FileInfo> files;
		//files.Insert(ImageDir.File("Arrow/L0_32x32.png"));
		//files.Insert(ImageDir.File("Arrow/M0_32x32.png"));
		//files.Insert(ImageDir.File("Arrow/R1_32x32.png"));
		files.Insert(ImageDir.File("Arrow/96x32.png"));
		Arrow2D_Manager.Texture.Assign(96, 32, files);
	}
}

float ShowDot(Container::Binary<Arrow2D::Inst::Data> & arrow_data,
	Point2D pos, Point2D dir0, Point2D dir1,
	ColorF4 col)
{
	float dot = Point2D::dot(dir0, dir1);
	Point2D p;

	p = pos + (dir0.normalize() * (dot / dir0.length()));
	arrow_data.Insert(Arrow2D::Inst::Data(pos + dir0, p, 10, col));
	arrow_data.Insert(Arrow2D::Inst::Data(pos + dir1, p, 10, col));

	p = pos + (dir1.normalize() * (dot / dir1.length()));
	arrow_data.Insert(Arrow2D::Inst::Data(pos + dir0, p, 10, col));
	arrow_data.Insert(Arrow2D::Inst::Data(pos + dir1, p, 10, col));

	return dot;
}
void Test(Container::Binary<Arrow2D::Inst::Data> & arrow_data)
{
//	Point2D pos = Point2D(0, 0);
//	Point2D dir0 = AbsolutePositionOfWindowPixel(window.MouseManager.CursorPixelPosition().Absolute);
//	Point2D dir1 = Point2D(1.0f, 0.0f);
//	arrow_data.Insert(Arrow2D::Inst::Data(pos, pos + dir0, 20, ColorF4(0, 0, 0)));
//	arrow_data.Insert(Arrow2D::Inst::Data(pos, pos + dir1, 20, ColorF4(0, 0, 0)));
//	ShowDot(arrow_data, pos, dir0, dir1, ColorF4(0, 1, 0));
//	{
//		float cross = dir0.cross(dir1);
//		Point2D pos0 = pos + (dir0 * cross);
//		Point2D pos1 = pos + (dir1 * cross);
//		arrow_data.Insert(Arrow2D::Inst::Data(pos, pos0, 20, ColorF4(1, 0, 0)));
//		arrow_data.Insert(Arrow2D::Inst::Data(pos, pos1, 20, ColorF4(1, 0, 0)));
//		arrow_data.Insert(Arrow2D::Inst::Data(pos0, pos1, 20, ColorF4(1, 0, 0)));
//	}

	Ray2D ray(Point2D(0, 0), AbsolutePositionOfWindowPixel(window.MouseManager.CursorPixelPosition().Absolute));
	arrow_data.Insert(Arrow2D::Inst::Data(ray.Pos, ray.Pos + ray.Dir, 20, ColorF4(0, 0, 0)));

	Line2D line(Point2D(-0.5f, +0.5f), Point2D(+0.5f, +0.5f));
	arrow_data.Insert(Arrow2D::Inst::Data(line, 20, ColorF4(0, 0, 0)));

	Point2D perp(-ray.Dir.Y, +ray.Dir.X);
	arrow_data.Insert(Arrow2D::Inst::Data(ray.Pos, ray.Pos + perp, 10, ColorF4(1, 1, 1)));

	Point2D diff = line.Pos1 - line.Pos0;
	Point2D rel0 = ray.Pos - line.Pos0;
	arrow_data.Insert(Arrow2D::Inst::Data(ray.Pos, line.Pos0, 10, ColorF4(1, 1, 1)));

	float dot = diff.dot(perp);
	if (dot == 0.0f)
	{
		// Parallel
	}

	float ray_t = diff.cross(rel0) / dot;
	float line_t = rel0.dot(perp) / dot;

	ColorF4 col;
	if (ray_t > 0.0f && (line_t >= 0.0f && line_t <= 1.0f))
	{ col = ColorF4(0, 1, 0); }
	else
	{ col = ColorF4(1, 0, 0); }
	arrow_data.Insert(Arrow2D::Inst::Data(ray.ToLine(ray_t), 10, col));
	arrow_data.Insert(Arrow2D::Inst::Data(line.Pos0, line.Pos0 + (diff * line_t), 10, col));

//	ColorF4 col;
//	float dot;
//	Point2D pos;

	//dot = Point2D::dot(perp, diff);
	//if (dot != 0.0f)
//	{
//		dot = ShowDot(arrow_data, ray.Pos, ray.Dir, -rel0, ColorF4(1, 0, 0));
//		(void)dot;
//
//		dot = ShowDot(arrow_data, line.Pos0, diff, rel0, ColorF4(0, 1, 0));
//
//		//col = ColorF4(0, 1, 0);
//		//dot = Point2D::dot(diff, perp) / dot;
//
//		//pos = line.Pos0 + (diff.normalize() * (dot / diff.length()));
//		//arrow_data.Insert(Arrow2D::Inst::Data(ray.Pos, pos, 10, col));
//		//arrow_data.Insert(Arrow2D::Inst::Data(line.Pos1, pos, 10, col));
//	}
}

void Arrow2DFrame()
{
	{
		Container::Binary<Arrow2D::Inst::Data> data;

		//{
		//	Point2D Cursor = AbsolutePositionOfWindowPixel(window.MouseManager.CursorPixelPosition().Absolute);
		//	data.Insert(Arrow2D::Inst::Data(Point2D(), Cursor, 20, ColorF4(1.0f, 1.0f, 1.0f)));
		//	data.Insert(Arrow2D::Inst::Data(Point2D(0, 1), Point2D(1, 1), 20, ColorF4(0.5f, 0.5f, 0.5f)));
		//}

		Point2D now;
		Point2D vel;
		for (unsigned int i = 0; i < Physics2D_Objects.Count(); i++)
		{
			now = Physics2D_Objects[i].Now().Pos;
			vel = Physics2D_Objects[i].Vel().Pos;
			data.Insert(Arrow2D::Inst::Data(now, now + vel, 10, ColorF4(0.5f, 0.5f, 1.0f)));
			for (unsigned int j = 0; j < Physics2D_Objects[i].CornerCount(); j++)
			{
				Point2D p = Physics2D_Objects[i].CornerFromIndex(j);
				Point2D now = Physics2D_Objects[i].AbsolutePositionOf(p);
				Point2D vel = Physics2D_Objects[i].AbsoluteVelocityOf(p);
				data.Insert(Arrow2D::Inst::Data(now, now + vel, 10, ColorF4(0.5f, 1.0f, 0.5f)));
				vel -= Physics2D_Objects[i].Vel().Pos;
				data.Insert(Arrow2D::Inst::Data(now, now + vel, 10, ColorF4(1.0f, 0.5f, 0.5f)));
			}
		}

		Arrow2D_Manager.Buffer.Inst.Change(data);
		/*std::cout << "Inst: " << data.Count() << '\n';
		for (unsigned int i = 0; i < data.Count(); i++)
		{
			std::cout << data[i].Pos << ' ' << data[i].Dir << ' ' << data[i].Size << '\n';
		}*/
	}
	Arrow2D_Manager.Shader.Bind();
	Arrow2D_Manager.Shader.View.Put(view.Trans);
	Arrow2D_Manager.Shader.Scale.PutData(&view.Scale);

	Arrow2D_Manager.Texture.Bind();
	Arrow2D_Manager.Buffer.Draw();
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

//	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D(+0.3f, -0.1f), Angle2D(Angle::Degrees(160))), Trans2D(Point2D(0.0f, 0.1f), Angle2D(Angle::Degrees(45))), false));

	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D(0.0f, 0.0f), Angle2D(Angle::Degrees(0))), Trans2D(Point2D(0.0f, 0.0f), Angle2D()), false));

	Physics2D_Objects.Insert(Physics2D::Object(Physics2D_MainInstances[obj0], Trans2D(Point2D(+0.3f, -0.1f), Angle2D(Angle::Degrees(160))), Trans2D(Point2D(-0.1f, 0.0f), Angle2D()), false));
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

	Arrow2D_Manager.GraphicsCreate();

	Arrow2DMake();

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

	Arrow2D_Manager.GraphicsDelete();
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
	GL::Enable(GL::Capability::DebugOutput);	// GL 4.3

	Debug::Log << "Test ...." << Debug::Done;
	Wire2D::Shader	WireShader;
	{
		Container::Array<Shader::Code> code({
			Shader::Code(ShaderDir.File("Wire/2D.vert")),
			Shader::Code(ShaderDir.File("Wire/2D.frag")),
		});
		WireShader.Change(code);
	}

	BufferArray::Base		WireBuffer;
	WireBuffer.Buffers.Allocate(3);
	Wire2D::Main::Buffer	WireMainBuffer(WireBuffer);
	Wire2D::Elem::Buffer	WireElemBuffer(WireBuffer);
	Physics2D::Inst::Buffer	WireInstBuffer(WireBuffer);
	WireBuffer.Buffers.Insert(&WireMainBuffer);
	WireBuffer.Buffers.Insert(&WireElemBuffer);
	WireBuffer.Buffers.Insert(&WireInstBuffer);

	WireMainBuffer.Pos.Change(0);
	WireMainBuffer.Col.Change(1);

	WireInstBuffer.Now.Pos.Change(2);
	WireInstBuffer.Now.Rot.Change(3, 4);

	WireShader.Create();
	WireBuffer.Create();

	WireShader.Bind();
	WireShader.WindowSize.Put(window.Size);
	WireShader.View.Put(view.Trans);
	WireShader.Scale.PutData(&view.Scale);

	WireFrame2D wire;
	wire.Corners.Insert(WireFrame2D::Corner(Point2D(-0.25f, -0.25f), ColorF4(0, 0, 0)));
	wire.Corners.Insert(WireFrame2D::Corner(Point2D(+0.25f, -0.25f), ColorF4(1, 0, 0)));
	wire.Corners.Insert(WireFrame2D::Corner(Point2D(+0.25f, +0.25f), ColorF4(0, 1, 0)));
	wire.Corners.Insert(WireFrame2D::Corner(Point2D(-0.25f, +0.25f), ColorF4(0, 0, 1)));

	wire.Sides.Insert(WireFrame2D::Side(0, 1));
	wire.Sides.Insert(WireFrame2D::Side(1, 2));
	wire.Sides.Insert(WireFrame2D::Side(2, 3));
	wire.Sides.Insert(WireFrame2D::Side(3, 0));

	WireMainBuffer.Change(wire.Corners);

	{
		WireElemBuffer.Bind();
		GL::BufferData(GL::BufferTarget::ElementArrayBuffer, wire.Sides.VoidLimit(), wire.Sides.VoidData(), GL::BufferDataUsage::StaticDraw);
	}

	Container::Binary<Physics2D::Inst::Data> instances;
	instances.Insert(Physics2D::Inst::Data(Trans2D(Point2D(), Angle2D())));
	WireInstBuffer.Change(instances);

	WireShader.Bind();
	WireBuffer.Bind();
	GL::DrawElementsInstanced(GL::DrawMode::Lines, (wire.Sides.Count() * 2), GL::DrawIndexType::UnsignedInt, instances.Count());

	WireBuffer.Delete();
	WireShader.Delete();

	Debug::Log << "Test done" << Debug::Done;
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

	Arrow2DFrame();

	Test();
}
void Resize(const WindowBufferSize2D & WindowSize)
{
	Physics2D_Shader.Bind();
	Physics2D_Shader.WindowSize.Put(WindowSize);
	Arrow2D_Manager.Shader.Bind();
	Arrow2D_Manager.Shader.WindowSize.Put(WindowSize);
}

Point2D AbsolutePositionOfWindowPixel(Point2D pos)
{
	Point2D HalfSize = window.Size.WindowSize / 2;	// Calculate in Window ?
	Point2D CursorPos = pos - HalfSize;
	CursorPos.Y = -CursorPos.Y;
	CursorPos = (CursorPos / window.Size.Ratio) / HalfSize;
	return (CursorPos * view.Scale) + view.Trans.Pos;
}

void MouseScroll(UserParameter::Mouse::Scroll params)
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
void MouseClick(UserParameter::Mouse::Click params)
{
	(void)params;
}
void MouseDrag(UserParameter::Mouse::Drag params)
{
	(void)params;
}

void KeyBoardKey(UserParameter::KeyBoard::Key params)
{
	if (params.Action.IsPress())
	{
		if (params.Code.Flags == GLFW_KEY_DELETE)
		{
			Point2D cursor = AbsolutePositionOfWindowPixel(window.MouseManager.CursorPixelPosition().Absolute);
			unsigned int idx = FindHoveringObjectIndex(cursor);
			if (idx != 0xFFFFFFFF)
			{
				Physics2D_Objects.Remove(idx);
			}
		}
	}
}



int Main()
{
	window.InitCallBack.Change<MainContext>(this, &MainContext::Init);
	window.FreeCallBack.Change<MainContext>(this, &MainContext::Free);
	window.FrameCallBack.Change<MainContext>(this, &MainContext::Frame);
	window.ResizeCallBack.Change<MainContext>(this, &MainContext::Resize);

	window.MouseManager.CallbackScroll.Change(this, &MainContext::MouseScroll);
	window.MouseManager.CallbackClick.Change(this, &MainContext::MouseClick);
	window.MouseManager.CallbackDrag.Change(this, &MainContext::MouseDrag);

	window.KeyBoardManager.KeyCallBack.Change(this, &MainContext::KeyBoardKey);

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
