
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



#include "Collision2D.hpp"



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
	Object_Buffers.Allocate(3, 3);



	unsigned int wall = 0;
	Object_Buffers[wall].BufferArray.Create();
	{
		PolyGon & gon = *(Object_Buffers[wall].Gon);
		gon.Corners.Insert(PolyGon::Corner(Point2D(-10, 0), ColorF4(1, 1, 1)));
		gon.Corners.Insert(PolyGon::Corner(Point2D(+10, 0), ColorF4(1, 1, 1)));
		gon.Corners.Insert(PolyGon::Corner(Point2D(-10, -1), ColorF4(0, 0, 0)));
		gon.Corners.Insert(PolyGon::Corner(Point2D(+10, -1), ColorF4(0, 0, 0)));
		gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(0), PolyGon::SideCorner(1), PolyGon::SideCorner(2)));
		gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(2), PolyGon::SideCorner(1), PolyGon::SideCorner(3)));
	}
	Object_Buffers[wall].UpdateMain();

	Objects.Insert(PhysicsObject2D(Object_Buffers[wall], Trans2D(Point2D(0, -10), Angle2D(Angle::Degrees(  0))), Trans2D(Point2D(0, 0), Angle2D()), true));
	Objects.Insert(PhysicsObject2D(Object_Buffers[wall], Trans2D(Point2D(-10, 0), Angle2D(Angle::Degrees( 90))), Trans2D(Point2D(0, 0), Angle2D()), true));
	Objects.Insert(PhysicsObject2D(Object_Buffers[wall], Trans2D(Point2D(0, +10), Angle2D(Angle::Degrees(180))), Trans2D(Point2D(0, 0), Angle2D()), true));
	Objects.Insert(PhysicsObject2D(Object_Buffers[wall], Trans2D(Point2D(+10, 0), Angle2D(Angle::Degrees(270))), Trans2D(Point2D(0, 0), Angle2D()), true));



	unsigned int obj0 = 1;
	Object_Buffers[obj0].BufferArray.Create();
	{
		PolyGon & gon = *(Object_Buffers[obj0].Gon);
		gon.Corners.Insert(PolyGon::Corner(Point2D(+1, -1), ColorF4(1, 0, 0)));
		gon.Corners.Insert(PolyGon::Corner(Point2D(-1, -1), ColorF4(0, 1, 0)));
		gon.Corners.Insert(PolyGon::Corner(Point2D( 0, +1), ColorF4(0, 0, 1)));
		gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(0), PolyGon::SideCorner(1), PolyGon::SideCorner(2)));
	}
	Object_Buffers[obj0].UpdateMain();

//	Stuck in Wall. Bounces back "into" Wall every time it would get out.
//	No Force pushing it out.
//	Objects.Insert(PhysicsObject2D(Object_Buffers[obj0], Trans2D(Point2D(-10, 0), Angle2D(Angle::Degrees(0))), Trans2D(Point2D(-1, 0), Angle2D()), false));

	Objects.Insert(PhysicsObject2D(Object_Buffers[obj0], Trans2D(Point2D( 0,  0), Angle2D(Angle::Degrees(0))), Trans2D(Point2D( 0, 0), Angle2D()), false));

	Objects.Insert(PhysicsObject2D(Object_Buffers[obj0], Trans2D(Point2D(+3, -1), Angle2D(Angle::Degrees(40))), Trans2D(Point2D(-1, 0), Angle2D()), false));
	Objects.Insert(PhysicsObject2D(Object_Buffers[obj0], Trans2D(Point2D(-3, -1), Angle2D(Angle::Degrees(80))), Trans2D(Point2D(+1, 0), Angle2D()), false));
	Objects.Insert(PhysicsObject2D(Object_Buffers[obj0], Trans2D(Point2D(+3, +1), Angle2D(Angle::Degrees(190))), Trans2D(Point2D(-1, 0), Angle2D()), false));
	Objects.Insert(PhysicsObject2D(Object_Buffers[obj0], Trans2D(Point2D(-3, +1), Angle2D(Angle::Degrees(140))), Trans2D(Point2D(+1, 0), Angle2D()), false));
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



void Bounce(PhysicsObject2D & phys_obj_0, PhysicsObject2D & phys_obj_1)
{
	if (phys_obj_0.IsStatic && phys_obj_1.IsStatic) { return; }

	Trans2D & now0 = (*phys_obj_0.Instance).Now;
	Trans2D & now1 = (*phys_obj_1.Instance).Now;

	Collision2D::PolyGonContactData contact_data = Collision2D::PolyGonContactData::Check(
		Collision2D::TransPolyGon(phys_obj_0.Buffer -> Gon, now0),
		Collision2D::TransPolyGon(phys_obj_1.Buffer -> Gon, now1)
	);
	if (!contact_data.Valid) { return; }

	Point2D Contact0 = phys_obj_0.Buffer -> Gon -> Corners[contact_data.Contact0Udx].Pos;
	Point2D Contact1 = phys_obj_1.Buffer -> Gon -> Corners[contact_data.Contact1Udx].Pos;

	Trans2D & vel0 = (*phys_obj_0.Instance).Vel;
	Trans2D & vel1 = (*phys_obj_1.Instance).Vel;

	{
		Point2D normal = contact_data.Normal.normalize();
		float e = 1.0f;

		Point2D vel_rel = vel1.Pos - vel0.Pos;
		float NormalVelFactor = Point2D::dot(vel_rel, normal);

		float MassInverse0 = 0;
		float MassInverse1 = 0;
		if (!phys_obj_0.IsStatic) { MassInverse0 = 1 / phys_obj_0.Mass; }
		if (!phys_obj_1.IsStatic) { MassInverse1 = 1 / phys_obj_1.Mass; }
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

		Point2D RelativeContact0 = Contact0 - now0.Pos;
		Point2D RelativeContact1 = Contact1 - now1.Pos;
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

		if (!phys_obj_0.IsStatic) { vel0.Pos = (vel0.Pos - (Impulse / phys_obj_0.Mass)); }
		if (!phys_obj_1.IsStatic) { vel1.Pos = (vel1.Pos + (Impulse / phys_obj_1.Mass)); }

		//if (!phys_obj_0.IsStatic) { vel0.Rot = (vel0.Rot - (InertiaFactor0 * ImpulseFactor)); }
		//if (!phys_obj_1.IsStatic) { vel1.Rot = (vel1.Rot - (InertiaFactor1 * ImpulseFactor)); }
	}

	if (phys_obj_0.IsStatic) { vel0.Pos = Point2D(); }
	if (phys_obj_1.IsStatic) { vel1.Pos = Point2D(); }
}

void UpdateGravity(float timeDelta)
{
	Point2D	Gravity = view.Trans.Rot.rotateBack(Point2D(0, -1)) * (3.0f * timeDelta);
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		if (!Objects[i].IsStatic)
		{
			(*Objects[i].Instance).Vel.Pos = (*Objects[i].Instance).Vel.Pos + Gravity;
		}
	}
}
void UpdateCollision()
{
	for (unsigned int i0 = 0; i0 < Objects.Count(); i0++)
	{
		for (unsigned int i1 = i0 + 1; i1 < Objects.Count(); i1++)
		{
			Bounce(Objects[i0], Objects[i1]);
		}
	}
}
void UpdateOrientation(float timeDelta)
{
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		if (!Objects[i].IsStatic)
		{
			(*Objects[i].Instance).Now.Pos = (*Objects[i].Instance).Now.Pos + ((*Objects[i].Instance).Vel.Pos * timeDelta);
			(*Objects[i].Instance).Now.Rot = (*Objects[i].Instance).Now.Rot + ((*Objects[i].Instance).Vel.Rot * timeDelta);
		}
	}
}
void Update(float timeDelta)
{
	UpdateGravity(timeDelta);
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
