
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



Physics2D::Shader		Physics2D_Shader;

AxisBox2D	Box0;
AxisBox2D	Box1;

Physics2D::BufferArray	Physics2D_BufferArray_Box0;
Physics2D::BufferArray	Physics2D_BufferArray_Box1;

Container::Binary<Physics2D::Inst::Data>	Instances_Box0;
Container::Binary<Physics2D::Inst::Data>	Instances_Box1;



void Make()
{
	Box0 = AxisBox2D(Point2D(-1, -1), Point2D(+1, +1));
	{
		Container::Binary<Physics2D::Main::Data> data;
		data.Insert(Physics2D::Main::Data(Point2D(Box0.Min.X, Box0.Min.Y), ColorF4(1, 0, 0)));
		data.Insert(Physics2D::Main::Data(Point2D(Box0.Min.X, Box0.Max.Y), ColorF4(0, 1, 0)));
		data.Insert(Physics2D::Main::Data(Point2D(Box0.Max.X, Box0.Min.Y), ColorF4(0, 0, 1)));
		data.Insert(Physics2D::Main::Data(Point2D(Box0.Max.X, Box0.Min.Y), ColorF4(0, 0, 1)));
		data.Insert(Physics2D::Main::Data(Point2D(Box0.Min.X, Box0.Max.Y), ColorF4(0, 1, 0)));
		data.Insert(Physics2D::Main::Data(Point2D(Box0.Max.X, Box0.Max.Y), ColorF4(1, 0, 0)));
		Physics2D_BufferArray_Box0.Bind();
		Physics2D_BufferArray_Box0.Main.Change(data);
	}
	Instances_Box0.Insert(Physics2D::Inst::Data());
	Instances_Box0[0].Pos = Point2D(0, 0);
	Instances_Box0[0].Vel = Point2D(0, 0);

	Box1 = AxisBox2D(Point2D(-2, -1), Point2D(+2, +1));
	{
		Container::Binary<Physics2D::Main::Data> data;
		data.Insert(Physics2D::Main::Data(Point2D(Box1.Min.X, Box1.Min.Y), ColorF4(1, 0, 0)));
		data.Insert(Physics2D::Main::Data(Point2D(Box1.Min.X, Box1.Max.Y), ColorF4(0, 1, 0)));
		data.Insert(Physics2D::Main::Data(Point2D(Box1.Max.X, Box1.Min.Y), ColorF4(0, 0, 1)));
		data.Insert(Physics2D::Main::Data(Point2D(Box1.Max.X, Box1.Min.Y), ColorF4(0, 0, 1)));
		data.Insert(Physics2D::Main::Data(Point2D(Box1.Min.X, Box1.Max.Y), ColorF4(0, 1, 0)));
		data.Insert(Physics2D::Main::Data(Point2D(Box1.Max.X, Box1.Max.Y), ColorF4(1, 0, 0)));
		Physics2D_BufferArray_Box1.Bind();
		Physics2D_BufferArray_Box1.Main.Change(data);
	}
	Instances_Box1.Insert(Physics2D::Inst::Data());
	Instances_Box1[0].Pos = Point2D(2, 3);
	Instances_Box1[0].Vel = Point2D(0, -0.5f);
	Instances_Box1.Insert(Physics2D::Inst::Data());
	Instances_Box1[1].Pos = Point2D(5, 1);
	Instances_Box1[1].Vel = Point2D(-0.5f, 0);
}



void Init()
{
	Physics2D_Shader.Create();
	Physics2D_BufferArray_Box0.Create();
	Physics2D_BufferArray_Box1.Create();

	Make();
}
void Free()
{
	Physics2D_BufferArray_Box1.Delete();
	Physics2D_BufferArray_Box0.Delete();
	Physics2D_Shader.Delete();
}

//	FIGURE OUT BOX VS BOX INTERSECTION, THEN PUT IT INTO THE AXIXBOX STRUCTS
static bool Intersekt(AxisBox2D box0, AxisBox2D box1)
{
/*
: A : B : C :
: D : E : F :

:	#-0-#			:	#---0---#		:	#-----0-----#	:
:			#-1-#	:		#---1---#	:		#-1-#		:

:			#-0-#	:		#---0---#	:		#-0-#		:
:	#-1-#			:	#---1---#		:	#-----1-----#	:

				: A : B : C : D : E : F :
Min0 <=> Min1	: < : < : < : > : > : > :
Max0 <=> Min1	: < : > : > : > : > : > :
Min0 <=> Max1	: < : < : < : > : < : < :
Max0 <=> Max1	: < : < : < : > : > : > :
				: A : B : C : D : E : F :
Max0  >  Min1 | Min0  <  Max1
*/
	return (
		((box0.Max.X > box1.Min.X) & (box0.Min.X < box1.Max.X)) &
		((box0.Max.Y > box1.Min.Y) & (box0.Min.Y < box1.Max.Y))
	);
}
void Update(float timeDelta)
{
	AxisBox2D box0 = Box0;
	box0.Min += Instances_Box0[0].Pos;
	box0.Max += Instances_Box0[0].Pos;
	

	for (unsigned int i = 0; i < Instances_Box1.Count(); i++)
	{
	AxisBox2D box1 = Box1;
	box1.Min += Instances_Box1[i].Pos;
	box1.Max += Instances_Box1[i].Pos;

	if (Intersekt(box0, box1))
	{
/*
	#-----------#
	|			|
	|		#---|-------#	#
	|		|	|		|	|
	#-------|---#		|	#
			|			|
			#-----------#

			#---#			Overlap

	#-------------------#
	|					|
	|	#-----------#	|	#
	|	|			|	|	|
	#---|-----------|---#	#
		|			|
		#-----------#

		#-----------#		Overlap
	#---#			#---#	Overlap ?
	I think it should be
	#---------------#
		#---------------#
	allways Min to Max and Max to Min
	allways the smaller one (for Boxes)
	
	so just calculate all combinations of
	Min to Max and Max to Min
	then look for the smallest one

*/
		Point2D Diff;
		{
			Point2D Diff0 = box0.Max - box1.Min;
			Point2D Diff1 = box1.Max - box0.Min;
			if (fabs(Diff0.X) < fabs(Diff1.X)) { Diff.X = Diff0.X; } else { Diff.X = Diff1.X; }
			if (fabs(Diff0.Y) < fabs(Diff1.Y)) { Diff.Y = Diff0.Y; } else { Diff.Y = Diff1.Y; }
		}

		Point2D vel;
		if (Instances_Box1[0].Vel.X > 0) { vel.X = +Instances_Box1[0].Vel.X; }
		if (Instances_Box1[0].Vel.X < 0) { vel.X = -Instances_Box1[0].Vel.X; }
		if (Instances_Box1[0].Vel.Y > 0) { vel.Y = +Instances_Box1[0].Vel.Y; }
		if (Instances_Box1[0].Vel.Y < 0) { vel.Y = -Instances_Box1[0].Vel.Y; }

/*
	Reflect Vel around Normal Vector
	(only when going againsts the normal ?)
	simplify for now ? yes.
	just figure out what side is the closest
	(thats what Diff does)
	then reflect Vel around that
*/
		//float diff;
		if (fabs(Diff.X) < fabs(Diff.Y))
		{
			if (Diff.X > 0)
			{
				//diff = +Diff.X;
				if (Instances_Box1[i].Vel.X < 0) { Instances_Box1[i].Vel.X = +fabs(Instances_Box1[i].Vel.X); }
			}
			if (Diff.X < 0)
			{
				//diff = -Diff.X;
				if (Instances_Box1[i].Vel.X > 0) { Instances_Box1[i].Vel.X = -fabs(Instances_Box1[i].Vel.X); }
			}
		}
		if (fabs(Diff.Y) < fabs(Diff.X))
		{
			if (Diff.Y > 0)
			{
				//diff = +Diff.Y;
				if (Instances_Box1[i].Vel.Y < 0) { Instances_Box1[i].Vel.Y = +fabs(Instances_Box1[i].Vel.Y); }
			}
			if (Diff.Y < 0)
			{
				//diff = -Diff.Y;
				if (Instances_Box1[i].Vel.Y > 0) { Instances_Box1[i].Vel.Y = -fabs(Instances_Box1[i].Vel.Y); }
			}
		}
	}
	}

	for (unsigned int i = 0; i < Instances_Box1.Count(); i++)
	{
		Instances_Box1[i].Pos += Instances_Box1[i].Vel * timeDelta;
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

	Physics2D_BufferArray_Box0.Bind();
	Physics2D_BufferArray_Box0.Inst.Change(Instances_Box0);

	Physics2D_BufferArray_Box1.Bind();
	Physics2D_BufferArray_Box1.Inst.Change(Instances_Box1);



	GL::Disable(GL::Capability::DepthTest);
	GL::Disable(GL::Capability::CullFace);

	Physics2D_Shader.Bind();
	Physics2D_BufferArray_Box0.Draw();
	Physics2D_BufferArray_Box1.Draw();
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
