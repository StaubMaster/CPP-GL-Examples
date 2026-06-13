#include <iostream>
#include <sstream>
#include <exception>
#include <string>

#include "OpenGL.hpp"
#include "Debug.hpp"



#include "DirectoryInfo.hpp"

#include "Window.hpp"

#include "ValueType/View3D.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Data.hpp"
#include "PolyHedra/Generate.hpp"
#include "PolyHedra/Manager.hpp"
#include "PolyHedra/Object.hpp"



struct Context
{
::Window &		Window;
DirectoryInfo	MediaDirectory;

View3D		View;
float		ViewDistance;
Matrix4x4	ViewMatrix;

::PolyHedraManager	PolyHedraManager;

::PolyHedra * GridX;
::PolyHedra * GridY;
::PolyHedra * GridZ;

PolyHedraObject GridXObj;
PolyHedraObject GridYObj;
PolyHedraObject GridZObj;

Container::Array<FileInfo>			PolyHedraFile;
Container::Array<::PolyHedra*>		PolyHedra;
Container::Array<PolyHedraObject>	PolyHedraObj;

~Context()
{ }
Context(::Window & window)
	: Window(window)
	, MediaDirectory("../../media/")
	, PolyHedraManager()
{ }

void Make()
{
	Window.DefaultColor = ColorF4(0.0f, 0.0f, 0.0f);
	View = View3D::Default();
	View.Trans.Rotation = EulerAngle3D::Degrees(0, 45, 180 + 45);
	//View.Depth.Factors.ChangeNear(0.01);
	//View.Depth.Factors.ChangeFar(10.0f);
	//View.Depth.Range.ChangeMax(1.0f);
	//View.Depth.Range.ChangeMin(0.0f);
	ViewDistance = 2.0f;

	PolyHedraManager.MakeCurrent();

	PolyHedraManager.ShaderLayoutFullDefault.Depth.Put(View.Depth);
	PolyHedraManager.ShaderLayoutFullDefault.FOV.Put(View.FOV);

	PolyHedraManager.ShaderLayoutWireDefault.Depth.Put(View.Depth);
	PolyHedraManager.ShaderLayoutWireDefault.FOV.Put(View.FOV);

	{
		int n = 10;
		GridX = new ::PolyHedra();
		GridY = new ::PolyHedra();
		GridZ = new ::PolyHedra();

		unsigned int idx0;
		unsigned int idx1;
		for (int i = -n; i <= +n; i++)
		{
			{
				idx0 = GridX -> Corners.Count(); GridX -> Insert_Corn(PolyHedra::Corner(VectorF3(0, -n, i)));
				idx1 = GridX -> Corners.Count(); GridX -> Insert_Corn(PolyHedra::Corner(VectorF3(0, +n, i)));
				GridX -> Edges.Insert(PolyHedra::Edge(idx0, idx1));

				idx0 = GridX -> Corners.Count(); GridX -> Insert_Corn(PolyHedra::Corner(VectorF3(0, i, -n)));
				idx1 = GridX -> Corners.Count(); GridX -> Insert_Corn(PolyHedra::Corner(VectorF3(0, i, +n)));
				GridX -> Edges.Insert(PolyHedra::Edge(idx0, idx1));

				idx0 = GridX -> Corners.Count(); GridX -> Insert_Corn(PolyHedra::Corner(VectorF3(0, -n, i) * 0.1f));
				idx1 = GridX -> Corners.Count(); GridX -> Insert_Corn(PolyHedra::Corner(VectorF3(0, +n, i) * 0.1f));
				GridX -> Edges.Insert(PolyHedra::Edge(idx0, idx1));

				idx0 = GridX -> Corners.Count(); GridX -> Insert_Corn(PolyHedra::Corner(VectorF3(0, i, -n) * 0.1f));
				idx1 = GridX -> Corners.Count(); GridX -> Insert_Corn(PolyHedra::Corner(VectorF3(0, i, +n) * 0.1f));
				GridX -> Edges.Insert(PolyHedra::Edge(idx0, idx1));
			}
			{
				idx0 = GridY -> Corners.Count(); GridY -> Insert_Corn(PolyHedra::Corner(VectorF3(i, 0, -n)));
				idx1 = GridY -> Corners.Count(); GridY -> Insert_Corn(PolyHedra::Corner(VectorF3(i, 0, +n)));
				GridY -> Edges.Insert(PolyHedra::Edge(idx0, idx1));

				idx0 = GridY -> Corners.Count(); GridY -> Insert_Corn(PolyHedra::Corner(VectorF3(-n, 0, i)));
				idx1 = GridY -> Corners.Count(); GridY -> Insert_Corn(PolyHedra::Corner(VectorF3(+n, 0, i)));
				GridY -> Edges.Insert(PolyHedra::Edge(idx0, idx1));
	
				idx0 = GridY -> Corners.Count(); GridY -> Insert_Corn(PolyHedra::Corner(VectorF3(i, 0, -n) * 0.1f));
				idx1 = GridY -> Corners.Count(); GridY -> Insert_Corn(PolyHedra::Corner(VectorF3(i, 0, +n) * 0.1f));
				GridY -> Edges.Insert(PolyHedra::Edge(idx0, idx1));

				idx0 = GridY -> Corners.Count(); GridY -> Insert_Corn(PolyHedra::Corner(VectorF3(-n, 0, i) * 0.1f));
				idx1 = GridY -> Corners.Count(); GridY -> Insert_Corn(PolyHedra::Corner(VectorF3(+n, 0, i) * 0.1f));
				GridY -> Edges.Insert(PolyHedra::Edge(idx0, idx1));
			}
			{
				idx0 = GridZ -> Corners.Count(); GridZ -> Insert_Corn(PolyHedra::Corner(VectorF3(i, -n, 0)));
				idx1 = GridZ -> Corners.Count(); GridZ -> Insert_Corn(PolyHedra::Corner(VectorF3(i, +n, 0)));
				GridZ -> Edges.Insert(PolyHedra::Edge(idx0, idx1));

				idx0 = GridZ -> Corners.Count(); GridZ -> Insert_Corn(PolyHedra::Corner(VectorF3(-n, i, 0)));
				idx1 = GridZ -> Corners.Count(); GridZ -> Insert_Corn(PolyHedra::Corner(VectorF3(+n, i, 0)));
				GridZ -> Edges.Insert(PolyHedra::Edge(idx0, idx1));

				idx0 = GridZ -> Corners.Count(); GridZ -> Insert_Corn(PolyHedra::Corner(VectorF3(i, -n, 0) * 0.1f));
				idx1 = GridZ -> Corners.Count(); GridZ -> Insert_Corn(PolyHedra::Corner(VectorF3(i, +n, 0) * 0.1f));
				GridZ -> Edges.Insert(PolyHedra::Edge(idx0, idx1));

				idx0 = GridZ -> Corners.Count(); GridZ -> Insert_Corn(PolyHedra::Corner(VectorF3(-n, i, 0) * 0.1f));
				idx1 = GridZ -> Corners.Count(); GridZ -> Insert_Corn(PolyHedra::Corner(VectorF3(+n, i, 0) * 0.1f));
				GridZ -> Edges.Insert(PolyHedra::Edge(idx0, idx1));
			}
		}

		GridXObj.Create(GridX);
		GridYObj.Create(GridY);
		GridZObj.Create(GridZ);
		//GridXObj.ShowWire();
		GridYObj.ShowWire();
		//GridZObj.ShowWire();
	}

	if (PolyHedraFile.Length() != 0)
	{
		PolyHedra = Container::Array<::PolyHedra*>(PolyHedraFile.Length());
		PolyHedraObj = Container::Array<PolyHedraObject>(PolyHedraFile.Length());
		for (unsigned int i = 0; i < PolyHedraFile.Length(); i++)
		{
			if (PolyHedraFile[i].Exists())
			{
				PolyHedra[i] = ::PolyHedra::Load(PolyHedraFile[i]);
			}
			else
			{
				PolyHedra[i] = ::PolyHedra::Generate::HexaHedron();
			}
			PolyHedraObj[i].Create(PolyHedra[i]);
		}
	}
	else
	{
		PolyHedra = Container::Array<::PolyHedra*>(1);
		PolyHedraObj = Container::Array<PolyHedraObject>(1);
		PolyHedra[0] = ::PolyHedra::Generate::HexaHedron();
		PolyHedraObj[0].Create(PolyHedra[0]);
	}
}

void Init()
{
	PolyHedraManager.ChangeMedia(MediaDirectory);

	PolyHedraManager.GraphicsCreate();

	Make();
}
void Free()
{
	PolyHedraManager.GraphicsDelete();

	delete GridX;
	delete GridY;
	delete GridZ;

	for (unsigned int i = 0; i < PolyHedra.Length(); i++)
	{
		delete PolyHedra[i];
	}
}

void User(FrameTime frame_time)
{
	if (Window.KeyBoardManager[Keys::Tab].State == State::Press) { Window.MouseManager.CursorModeToggle(); }
	if (Window.MouseManager.CursorModeIsLocked())
	{
		Trans3D trans = Window.MoveSpinFromKeysCursor();
		if (Window.KeyBoardManager[Keys::LeftControl].State == State::Down) { trans.Position *= 10; }
		trans.Position *= 2;
		trans.Rotation *= View.FOV.ToRadians() * 0.05f;
		View.ChangeFlatX(trans, frame_time.Delta);
	}

	{
		Trans3D trans = View.Trans;
		trans.Position -= trans.Rotation.forward(VectorF3(0, 0, ViewDistance));
		ViewMatrix = Matrix4x4::TransformReverse(trans);
	}
}
void Draw()
{
	{
		PolyHedraManager.ShaderLayoutFullDefault.View.Put(ViewMatrix);
		PolyHedraManager.ShaderLayoutWireDefault.View.Put(ViewMatrix);
	}

	PolyHedraManager.MakeInstances();
	PolyHedraManager.DrawFull();
	PolyHedraManager.DrawWire();
}

void Frame(FrameTime frame_time)
{
	User(frame_time);

	Draw();
}

void Resize(DisplaySize display_size)
{
	PolyHedraManager.ShaderLayoutFullDefault.DisplaySize.Put(display_size);
	PolyHedraManager.ShaderLayoutWireDefault.DisplaySize.Put(display_size);
}
void CursorScroll(ScrollArgs args)
{
	if (args.Y < 0.0f)
	{
		ViewDistance += 0.1f;
		if (ViewDistance > 64.0f) { ViewDistance = 64.0f; }
	}
	if (args.Y > 0.0f)
	{
		ViewDistance -= 0.1f;
		if (ViewDistance < 0.0f) { ViewDistance = 0.0f; }
	}
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
			Window window;
			window.Create();
			{
				Context * context = new Context(window);
				if (argc >= 1)
				{
					unsigned int n = argc - 1;
					context -> PolyHedraFile = Container::Array<FileInfo>(n);
					for (unsigned int i = 0; i < n; i++)
					{
						context -> PolyHedraFile[i] = argv[i + 1];
					}
				}
				window.CallBack_Frame.Assign(context, &Context::Frame);
				window.CallBack_Resize.Assign(context, &Context::Resize);
				window.CallBack_Init.Assign(context, &Context::Init);
				window.CallBack_Free.Assign(context, &Context::Free);
				window.MouseManager.Callback_ScrollEvent.Assign(context, &Context::CursorScroll);
				window.RunLoop();
				delete context;
			}
			window.Delete();
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
