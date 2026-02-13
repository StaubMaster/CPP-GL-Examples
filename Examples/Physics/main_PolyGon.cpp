
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



#include "Physics2D/BufferArray.hpp"
#include "Physics2D/Shader.hpp"
#include "Physics2D/Main/Data.hpp"
#include "Physics2D/Inst/Data.hpp"

#include "PolyGon.hpp"



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

/*
make general PolyGons instead of just Objects
allow them to Spin
figure out General Collision

Collision should just be the old system
*/



struct Physics2D_Main
{
	PolyGon *	Gon;
	Physics2D::BufferArray	BufferArray;
	EntryContainer::Binary<Physics2D::Inst::Data>	* Instances;

	Physics2D_Main()
		: Gon(new PolyGon())
		, BufferArray()
		, Instances(new EntryContainer::Binary<Physics2D::Inst::Data>())
	{ }
	void Dispose()
	{
		delete Instances;
		delete Gon;
	}

	void UpdateMain()
	{
		Container::Pointer<Physics2D::Main::Data> data = Gon -> ToPhysics2D();
		BufferArray.Bind();
		BufferArray.Main.Change(data);
		data.Delete();
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
};
Container::Array<Physics2D_Main> Object_Buffers;



struct PhysicsObject2D
{
	Physics2D_Main *		Buffer;
	EntryContainer::Entry<Physics2D::Inst::Data>	Instance;
	bool	IsStatic;
	float	Mass;
	float	Bounciness;

	~PhysicsObject2D()
	{ }
	PhysicsObject2D()
		: Buffer(nullptr)
		, Instance()
		, IsStatic(true)
		, Mass(1.0f)
		, Bounciness(0.5f)
	{ }
	PhysicsObject2D(Physics2D_Main & buffer, bool is_static)
		: Buffer(&buffer)
		, Instance(*buffer.Instances, 1)
		, IsStatic(is_static)
		, Mass(1.0f)
		, Bounciness(0.5f)
	{ }
	PhysicsObject2D(Physics2D_Main & buffer, Trans2D now, bool is_static)
		: Buffer(&buffer)
		, Instance(*buffer.Instances, 1)
		, IsStatic(is_static)
		, Mass(1.0f)
		, Bounciness(0.5f)
	{
		(*Instance).Now = now;
	}
	PhysicsObject2D(Physics2D_Main & buffer, Trans2D now, Trans2D vel, bool is_static)
		: Buffer(&buffer)
		, Instance(*buffer.Instances, 1)
		, IsStatic(is_static)
		, Mass(1.0f)
		, Bounciness(0.5f)
	{
		(*Instance).Now = now;
		(*Instance).Vel = vel;
	}
};
Container::Binary<PhysicsObject2D>	Objects;



void Make()
{
	Object_Buffers.Allocate(1, 1);

	Object_Buffers[0].BufferArray.Create();
	{
		PolyGon & gon = *(Object_Buffers[0].Gon);
		gon.Corners.Insert(PolyGon::Corner(Point2D(-1, -1), ColorF4(1, 0, 0)));
		gon.Corners.Insert(PolyGon::Corner(Point2D(-1, +1), ColorF4(0, 1, 0)));
		gon.Corners.Insert(PolyGon::Corner(Point2D(+2, -1), ColorF4(0, 0, 1)));
		gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(0), PolyGon::SideCorner(1), PolyGon::SideCorner(2)));
	}
	Object_Buffers[0].UpdateMain();
	Objects.Insert(PhysicsObject2D(Object_Buffers[0], Trans2D(Point2D(-2, -0.5f), Angle2D()), Trans2D(Point2D(+1, 0), Angle2D()), false));
	Objects.Insert(PhysicsObject2D(Object_Buffers[0], Trans2D(Point2D(+2, +0.5f), Angle2D()), Trans2D(Point2D(-1, 0), Angle2D()), false));
}



void Init()
{
	Physics2D_Shader.Create();

	Make();
}
void Free()
{
	Physics2D_Shader.Delete();
	Objects.Clear();
	for (unsigned int i = 0; i < Object_Buffers.Count(); i++)
	{
		Object_Buffers[i].BufferArray.Delete();
		Object_Buffers[i].Dispose();
	}
}

bool Intersekt(
	const PolyGon & gon0, const Trans2D & trans0,
	const PolyGon & gon1, const Trans2D & trans1,
	Point2D normal, float & diff)
{
	AxisBox1D box0;
	for (unsigned int i = 0; i < gon0.Corners.Count(); i++)
	{
		Point2D	pos = gon0.Corners[i].Pos;
		pos = pos + trans0.Pos;
		box0.Consider(Point2D::dot(normal, pos));
	}

	AxisBox1D box1;
	for (unsigned int i = 0; i < gon1.Corners.Count(); i++)
	{
		Point2D	pos = gon1.Corners[i].Pos;
		pos = pos + trans1.Pos;
		box1.Consider(Point2D::dot(normal, pos));
	}

	if (box0.Intersekt(box1))
	{
		float diff0 = box0.Max - box1.Min;
		float diff1 = box0.Min - box1.Max;
		if (fabs(diff0) < fabs(diff1)) { diff = diff0; } else { diff = diff1; }
		return true;
	}
	return false;
}

bool Intersekt(
	const PolyGon & gon0, const Trans2D & trans0,
	const PolyGon & gon1, const Trans2D & trans1,
	Point2D & normal)
{
	normal = Point2D();
	float diff = +INFINITY;
	bool none = true;

	Point2D n;
	float d;

	for (unsigned int i = 0; i < gon0.Sides.Count(); i++)
	{
		Point2D pos0 = gon0.Corners[gon0.Sides[i].Corner0.Udx].Pos;
		Point2D pos1 = gon0.Corners[gon0.Sides[i].Corner1.Udx].Pos;
		Point2D pos2 = gon0.Corners[gon0.Sides[i].Corner2.Udx].Pos;

		n = (pos1 - pos0).perpendicular0();
		if (!Intersekt(gon0, trans0, gon1, trans1, n, d)) { return false; }
		if (none || fabs(d) < fabs(diff)) { none = false; diff = d; normal = n; }
		
		n = (pos2 - pos1).perpendicular0();
		if (!Intersekt(gon0, trans0, gon1, trans1, n, d)) { return false; }
		if (none || fabs(d) < fabs(diff)) { none = false; diff = d; normal = n; }
		
		n = (pos0 - pos2).perpendicular0();
		if (!Intersekt(gon0, trans0, gon1, trans1, n, d)) { return false; }
		if (none || fabs(d) < fabs(diff)) { none = false; diff = d; normal = n; }
	}

	return !none;
}

void Bounce01(PhysicsObject2D & phys_obj_0, PhysicsObject2D & phys_obj_1)
{
	if (phys_obj_0.IsStatic && phys_obj_1.IsStatic) { return; }

	Point2D normal;
	if (!Intersekt(
		*(phys_obj_0.Buffer -> Gon), (*phys_obj_0.Instance).Now,
		*(phys_obj_1.Buffer -> Gon), (*phys_obj_1.Instance).Now,
		normal
	)) { return; }

	Trans2D & vel0 = (*phys_obj_0.Instance).Vel;
	Trans2D & vel1 = (*phys_obj_1.Instance).Vel;

	{
		normal = normal.normalize();
		float e = 0.5f;

		Point2D vel_rel = vel1.Pos - vel0.Pos;
		float NormalVelFactor = Point2D::dot(vel_rel, normal);

		float MassInverse0 = 0;
		float MassInverse1 = 0;
		if (!phys_obj_0.IsStatic) { MassInverse0 = 1 / phys_obj_0.Mass; }
		if (!phys_obj_1.IsStatic) { MassInverse1 = 1 / phys_obj_1.Mass; }
		float MassInverseSum = MassInverse0 + MassInverse1;

		float impulseFactor = (-(1.0f + e) * NormalVelFactor) / MassInverseSum;

		Point2D impulse = normal * impulseFactor;
		if (!phys_obj_0.IsStatic) { vel0.Pos = (vel0.Pos - (impulse / phys_obj_0.Mass)); }
		if (!phys_obj_1.IsStatic) { vel1.Pos = (vel1.Pos + (impulse / phys_obj_1.Mass)); }
	}

	if (phys_obj_0.IsStatic) { vel0.Pos = Point2D(); }
	if (phys_obj_1.IsStatic) { vel1.Pos = Point2D(); }
}
void Update(float timeDelta)
{
	for (unsigned int i0 = 0; i0 < Objects.Count(); i0++)
	{
		for (unsigned int i1 = i0 + 1; i1 < Objects.Count(); i1++)
		{
			Bounce01(Objects[i0], Objects[i1]);
		}
	}

	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		if (!Objects[i].IsStatic)
		{
			(*Objects[i].Instance).Now.Pos = (*Objects[i].Instance).Now.Pos + ((*Objects[i].Instance).Vel.Pos * timeDelta);
		}
	}
	//(void)timeDelta;
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

	for (unsigned int i = 0; i < Object_Buffers.Count(); i++)
	{
		Object_Buffers[i].UpdateInst();
	}



	GL::Disable(GL::Capability::DepthTest);
	GL::Disable(GL::Capability::CullFace);

	Physics2D_Shader.Bind();
	for (unsigned int i = 0; i < Object_Buffers.Count(); i++)
	{
		Object_Buffers[i].Draw();
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
