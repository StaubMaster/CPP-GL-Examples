
#include <iostream>
#include <sstream>
#include <exception>

#include "OpenGL.hpp"
#include "Debug.hpp"

#include "DataInclude.hpp"
#include "DataShow.hpp"

#include "Window.hpp"
#include "ValueType/View.hpp"
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



#include "Physics2D/BufferArray.hpp"
#include "Physics2D/Shader.hpp"
#include "Physics2D/Main/Data.hpp"
#include "Physics2D/Inst/Data.hpp"



#include <math.h>



struct MainContext
{
DirectoryInfo ImageDir;
DirectoryInfo ShaderDir;
DirectoryInfo PolyHedraDir;
DirectoryInfo TextDir;

Window	window;
Point2D	ViewPos;
float	ViewScale;

MainContext()
	: ImageDir("../../media/Images")
	, ShaderDir("../../media/Shaders")
	, PolyHedraDir("../../media/YMT")
	, TextDir("../../media/Text")
	, window()
//	, view()
	, ViewPos()
	, ViewScale(10.0f)
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



struct PhysicsBox2D_Main
{
	AxisBox2D	Box;
	Physics2D::BufferArray	BufferArray;
	EntryContainer::Binary<Physics2D::Inst::Data>	* Instances;

	PhysicsBox2D_Main()
		: Box()
		, BufferArray()
		, Instances(new EntryContainer::Binary<Physics2D::Inst::Data>())
	{ }
	void Dispose()
	{
		delete Instances;
	}

	void UpdateMain()
	{
		Container::Binary<Physics2D::Main::Data> data;
		data.Insert(Physics2D::Main::Data(Point2D(Box.Min.X, Box.Min.Y), ColorF4(1, 0, 0)));
		data.Insert(Physics2D::Main::Data(Point2D(Box.Min.X, Box.Max.Y), ColorF4(0, 1, 0)));
		data.Insert(Physics2D::Main::Data(Point2D(Box.Max.X, Box.Min.Y), ColorF4(0, 0, 1)));
		data.Insert(Physics2D::Main::Data(Point2D(Box.Max.X, Box.Min.Y), ColorF4(0, 0, 1)));
		data.Insert(Physics2D::Main::Data(Point2D(Box.Min.X, Box.Max.Y), ColorF4(0, 1, 0)));
		data.Insert(Physics2D::Main::Data(Point2D(Box.Max.X, Box.Max.Y), ColorF4(1, 0, 0)));
		BufferArray.Bind();
		BufferArray.Main.Change(data);
	}
	void UpdateInst()
	{
		BufferArray.Bind();
		BufferArray.Inst.Change(*Instances);
	}
	void Draw()
	{
		BufferArray.Draw();
	}

	AxisBox2D	CalculateInstance(Physics2D::Inst::Data data)
	{
		return AxisBox2D(
			Box.Min + data.Pos,
			Box.Max + data.Pos
		);
	}
};
//Container::Binary<PhysicsBox2D_Main> Box_Buffers;
Container::Array<PhysicsBox2D_Main> Box_Buffers;



struct PhysicsBox2D
{
	PhysicsBox2D_Main *	Buffer;
	EntryContainer::Entry<Physics2D::Inst::Data>	Instance;
	bool	IsStatic;

	~PhysicsBox2D()
	{ }
	PhysicsBox2D()
		: Buffer(nullptr)
		, Instance()
		, IsStatic(true)
	{ }
	PhysicsBox2D(PhysicsBox2D_Main & buffer, bool is_static)
		: Buffer(&buffer)
		, Instance(*buffer.Instances, 1)
		, IsStatic(is_static)
	{ }
	PhysicsBox2D(PhysicsBox2D_Main & buffer, Point2D pos, bool is_static)
		: Buffer(&buffer)
		, Instance(*buffer.Instances, 1)
		, IsStatic(is_static)
	{
		(*Instance).Pos = pos;
	}
	PhysicsBox2D(PhysicsBox2D_Main & buffer, Point2D pos, Point2D vel, bool is_static)
		: Buffer(&buffer)
		, Instance(*buffer.Instances, 1)
		, IsStatic(is_static)
	{
		(*Instance).Pos = pos;
		(*Instance).Vel = vel;
	}
	

	AxisBox2D CalculateInstance()
	{
		if (Buffer == nullptr) { return AxisBox2D(); }
		return Buffer -> CalculateInstance(*Instance);
	}
};
Container::Binary<PhysicsBox2D>	Boxes;



void Make()
{
	Box_Buffers.Allocate(2, 2);

	Box_Buffers[0].BufferArray.Create();
	Box_Buffers[0].Box = AxisBox2D(Point2D(-1, -1), Point2D(+1, +1));
	Box_Buffers[0].UpdateMain();

//	Boxes.Insert(PhysicsBox2D(Box_Buffers[0], true));
	{
		float factor = 2.0f;
		for (int i = -7; i <= +7; i++)
		{
			Boxes.Insert(PhysicsBox2D(Box_Buffers[0], Point2D(i * factor, -8 * factor), true));
			Boxes.Insert(PhysicsBox2D(Box_Buffers[0], Point2D(i * factor, +8 * factor), true));
			Boxes.Insert(PhysicsBox2D(Box_Buffers[0], Point2D(-8 * factor, i * factor), true));
			Boxes.Insert(PhysicsBox2D(Box_Buffers[0], Point2D(+8 * factor, i * factor), true));
		}
		Boxes.Insert(PhysicsBox2D(Box_Buffers[0], Point2D(+6 * factor, 0), true));
	}

	Box_Buffers[1].BufferArray.Create();
	Box_Buffers[1].Box = AxisBox2D(Point2D(-2, -1), Point2D(+2, +1));
	Box_Buffers[1].UpdateMain();

	Boxes.Insert(PhysicsBox2D(Box_Buffers[1], Point2D(2, 3), Point2D(0, -1), false));
	Boxes.Insert(PhysicsBox2D(Box_Buffers[1], Point2D(1, -2), Point2D(0, 1), false));
//	Boxes.Insert(PhysicsBox2D(Box_Buffers[1], Point2D(5, 1), Point2D(-1, 0), false));
//	Boxes.Insert(PhysicsBox2D(Box_Buffers[1], Point2D(-7, 0.5), Point2D(1, 0), false));
//	Boxes.Insert(PhysicsBox2D(Box_Buffers[1], Point2D(1, -9), Point2D(0, 1), false));
//	Boxes.Insert(PhysicsBox2D(Box_Buffers[0], Point2D(7, 7), Point2D(1, 1), false));
//	Boxes.Insert(PhysicsBox2D(Box_Buffers[0], Point2D(6, -7), Point2D(2, 1), false));
//	Boxes.Insert(PhysicsBox2D(Box_Buffers[0], Point2D(-6, -6), Point2D(7, -5), false));
//	Boxes.Insert(PhysicsBox2D(Box_Buffers[0], Point2D(-9, -6), Point2D(7, -5), false));
//	Boxes.Insert(PhysicsBox2D(Box_Buffers[0], Point2D(-9, -9), Point2D(7, -5), false));
//	Boxes.Insert(PhysicsBox2D(Box_Buffers[0], Point2D(-6, -9), Point2D(7, -5), false));
}



void Init()
{
	Physics2D_Shader.Create();

	Make();
}
void Free()
{
	Boxes.Clear();
	Physics2D_Shader.Delete();
	for (unsigned int i = 0; i < Box_Buffers.Count(); i++)
	{
		Box_Buffers[i].BufferArray.Delete();
		Box_Buffers[i].Dispose();
	}
}

void Bounce01(PhysicsBox2D & phys_box0, PhysicsBox2D & phys_box1)
{
	if (phys_box0.IsStatic && phys_box1.IsStatic) { return; }

	AxisBox2D box0 = phys_box0.CalculateInstance();
	AxisBox2D box1 = phys_box1.CalculateInstance();
	if (!box0.Intersekt(box1)) { return; }

	Point2D & vel0 = (*phys_box0.Instance).Vel;
	Point2D & vel1 = (*phys_box1.Instance).Vel;

	Point2D normal;
	{
		Point2D diff;
		{
			Point2D diff0 = box0.Max - box1.Min;
			Point2D diff1 = box0.Min - box1.Max;
			if (fabs(diff0.X) < fabs(diff1.X)) { diff.X = diff0.X; } else { diff.X = diff1.X; }
			if (fabs(diff0.Y) < fabs(diff1.Y)) { diff.Y = diff0.Y; } else { diff.Y = diff1.Y; }
		}
		if (fabs(diff.X) < fabs(diff.Y)) { normal.X = diff.X; } else { normal.Y = diff.Y; }
	}

	//	Velocity Reflector
	/*{
		float dot = Point2D::dot(vel1, normal);
		if (dot < 0)
		{
			vel1 = vel1 - (normal * (2 * (dot / normal.length2())));
		}
	}*/

	//	Mass Impulse Thing
	{
		Point2D rel = vel1 - vel0;
		float relativeNormal = Point2D::dot(rel, normal);

		float Mass0 = 1.0f;
		float Mass1 = 1.0f;
		float combinedMassInverse = ((1 / Mass0) + (1 / Mass1));

		float e = 0.5f;	//	BounceFactor
		float magniture = ((1.0f + e) * relativeNormal) / combinedMassInverse;
		Point2D impulse = normal * magniture;

		vel0 = vel0 + (impulse / Mass0);
		vel1 = vel1 - (impulse / Mass1);
	}

	if (phys_box0.IsStatic) { vel0 = Point2D(); }
	if (phys_box1.IsStatic) { vel1 = Point2D(); }
}
void Update(float timeDelta)
{
	for (unsigned int i0 = 0; i0 < Boxes.Count(); i0++)
	{
		for (unsigned int i1 = 0; i1 < Boxes.Count(); i1++)
		{
			if (i0 != i1)
			{
				Bounce01(Boxes[i0], Boxes[i1]);
			}
		}
	}

	for (unsigned int i = 0; i < Boxes.Count(); i++)
	{
		if (!Boxes[i].IsStatic)
		{
			(*Boxes[i].Instance).Pos = (*Boxes[i].Instance).Pos + ((*Boxes[i].Instance).Vel * timeDelta);
		}
	}
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
		Point3D move3D = window.MoveFromKeys();
		Point2D move2D(move3D.X, move3D.Z);
		//if (window.KeyBoardManager.Keys[GLFW_KEY_LEFT_CONTROL].IsDown()) { move2D *= 30; }
		move2D *= 2.0f;
		ViewPos += move2D * timeDelta;
	}

	Update(timeDelta);

	Physics2D_Shader.Bind();
	Physics2D_Shader.ViewPos.Put(ViewPos);
	Physics2D_Shader.ViewScale.PutData(&ViewScale);

	for (unsigned int i = 0; i < Box_Buffers.Count(); i++)
	{
		Box_Buffers[i].UpdateInst();
	}



	GL::Disable(GL::Capability::DepthTest);
	GL::Disable(GL::Capability::CullFace);

	Physics2D_Shader.Bind();
	for (unsigned int i = 0; i < Box_Buffers.Count(); i++)
	{
		Box_Buffers[i].Draw();
	}
}
void Resize(const WindowBufferSize2D & WindowSize)
{
	Physics2D_Shader.Bind();
	Physics2D_Shader.WindowSize.Put(WindowSize);
}

void CursorScroll(UserParameter::Mouse::Scroll params)
{
	ViewScale -= params.Y * 1.0f;
	if (ViewScale <= 0) { ViewScale = 1.0f; }
	if (ViewScale >= 100) { ViewScale = 100.0f; }
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
