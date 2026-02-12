
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
	, ViewScale(1.0)
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
Physics2D::BufferArray	Physics2D_BufferArray;

Container::Binary<Physics2D::Inst::Data>	Instances;



void Make()
{
	{
		Container::Binary<Physics2D::Main::Data> main_data;
		main_data.Insert(Physics2D::Main::Data(Point2D(-1, -1), ColorF4(1, 0, 0)));
		main_data.Insert(Physics2D::Main::Data(Point2D(-1, +1), ColorF4(0, 1, 0)));
		main_data.Insert(Physics2D::Main::Data(Point2D(+1, -1), ColorF4(0, 0, 1)));
		Physics2D_BufferArray.Bind();
		Physics2D_BufferArray.Main.Change(main_data);
	}
	Instances.Insert(Physics2D::Inst::Data());
}



void Init()
{
	Physics2D_Shader.Create();
	Physics2D_BufferArray.Create();

	Make();
}
void Free()
{
	Physics2D_BufferArray.Delete();
	Physics2D_Shader.Delete();
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
		ViewPos += move2D * timeDelta;
	}
	Physics2D_Shader.Bind();
	Physics2D_Shader.ViewPos.Put(ViewPos);
	Physics2D_Shader.ViewScale.PutData(&ViewScale);

	Instances[0].Pos = Point2D(0, 0);
	Physics2D_BufferArray.Bind();
	Physics2D_BufferArray.Inst.Change(Instances);

	GL::Disable(GL::Capability::DepthTest);
	GL::Disable(GL::Capability::CullFace);
	Physics2D_Shader.Bind();
	Physics2D_BufferArray.Draw();
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
