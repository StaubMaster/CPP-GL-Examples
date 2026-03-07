
#include <iostream>
#include <sstream>
#include <exception>
#include <string>

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



#include "Physics2D/Shaders/PolyGon.hpp"
#include "PolyGon/Graphics/Data.hpp"
#include "Inst/Physics2D/Data.hpp"

#include "PolyGon/PolyGon.hpp"
#include "PolyGon/Data.hpp"



#include "Physics2D/Collision.hpp"
#include "Physics2D/Manager.hpp"
#include "Physics2D/InstanceManager.hpp"
#include "Physics2D/Object.hpp"

#include "Arrow2D/Manager.hpp"
#include "Arrow2D/Shader.hpp"
#include "Arrow2D/Main/Data.hpp"
#include "Arrow2D/Inst/Data.hpp"

#include "WireFrame2D/WireFrame2D.hpp"
#include "WireFrame2D/Manager.hpp"

#include "Graphics/MultiformsInclude.hpp"
#include "Graphics/Multiform/Trans2D.hpp"
#include "Graphics/Multiform/Float.hpp"

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

Multiform::DisplaySize			Multiform_DisplaySize;
Multiform::Trans2D				Multiform_View;
Multiform::Float				Multiform_Scale;

MainContext()
	: ImageDir("../../media/Images")
	, ShaderDir("../../media/Shaders")
	, PolyHedraDir("../../media/YMT")
	, TextDir("../../media/Text")
	, window()
	, view(View2D::Default())
	, Paused(true)
	, Multiform_DisplaySize("DisplaySize")
	, Multiform_View("View")
	, Multiform_Scale("Scale")
{
	Physics2D_Manager.InitExternal(ShaderDir);

	Container::Array<Shader::Base *> shaders({
		&Physics2D_Manager.Shader_PolyGon,
		&Physics2D_Manager.Shader_WireFrame,
		&Physics2D_Manager.Shader_Arrow,
	});
	Multiform_DisplaySize.FindUniforms(shaders);
	Multiform_View.FindUniforms(shaders);
	Multiform_Scale.FindUniforms(shaders);

	Object_Selected = Undex::Invalid();
	Object_Hovering = Undex::Invalid();
}
~MainContext()
{
	Physics2D_Manager.Dispose();
}

Physics2D::Manager	Physics2D_Manager;

Undex	Object_Selected;
Undex	Object_Hovering;



struct SDrag
{
bool Is = false;
Undex Object;
Point2D Pos0;
Point2D Pos1;
EntryContainer::Entry<Arrow2D::Inst::Data> Arrow;
/* Drag
	currently changes Linear Velocity when Drag is done
	just apply Force/Impulse while Drag is active
*/
void Begin(Point2D pos0, Physics2D::Manager & manager)
{
	if (!Is)
	{
		Object = manager.FindObjectIndex(pos0);
		if (Object.IsValid())
		{
			Pos0 = manager.Objects[Object.Value].RelativePositionOf(pos0);
			Arrow.Allocate(manager.Instances_Arrow, 1);
			(*Arrow).Col = ColorF4(1, 1, 1);
			(*Arrow).Size = 20.0f;
			Is = true;
		}
	}
}
void Move(Point2D pos1)
{
	if (Is)
	{
		Pos1 = pos1;
		(*Arrow).Pos1 = Pos1;
	}
}
void End()
{
	if (Is)
	{
		/*if (Object_Selected.IsValid())
		{
			Point2D rel = Pos1 - Physics2D_Manager.Objects[Object.Value].AbsolutePositionOf(Pos0);
			Physics2D_Manager.Objects[Object_Selected.Value].Data.Vel.Pos += rel;
		}*/
		Is = false;
		Arrow.Dispose();
	}
}
void Update(const View2D & view, const Window & window, Physics2D::Manager & manager)
{
	if (!Is) { return; }
	Pos1 = view * window.Size.Convert(window.MouseManager.CursorPosition());
	(*Arrow).Pos0 = manager.Objects[Object.Value].AbsolutePositionOf(Pos0);
	(*Arrow).Pos1 = Pos1;

	Point2D rel = Pos1 - manager.Objects[Object.Value].AbsolutePositionOf(Pos0);
	manager.Objects[Object.Value].Data.Vel.Pos += rel * 0.1f;
}
};
SDrag Drag;



void Make()
{
	Physics2D_Manager.MainInstances.Allocate(3, 3);



	unsigned int wall = 0;
	Physics2D_Manager.MainInstances[wall].Buffer_PolyGon.Create();
	{
		float thickness = 0.1f;
		PolyGon & poly_gon = *(Physics2D_Manager.MainInstances[wall].PolyGon);
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(-1, 0), ColorF4(1, 1, 1)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(+1, 0), ColorF4(1, 1, 1)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(-1 - thickness, -thickness), ColorF4(0, 0, 0)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(+1 + thickness, -thickness), ColorF4(0, 0, 0)));
		poly_gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(0), PolyGon::SideCorner(1), PolyGon::SideCorner(2)));
		poly_gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(2), PolyGon::SideCorner(1), PolyGon::SideCorner(3)));
	}

	Physics2D_Manager.Objects.Insert(Physics2D::Object(Physics2D_Manager.MainInstances[wall], Trans2D(Point2D( 0, -1), Angle2D(Angle::Degrees(  0))), true));
	Physics2D_Manager.Objects.Insert(Physics2D::Object(Physics2D_Manager.MainInstances[wall], Trans2D(Point2D(+1,  0), Angle2D(Angle::Degrees( 90))), true));
	Physics2D_Manager.Objects.Insert(Physics2D::Object(Physics2D_Manager.MainInstances[wall], Trans2D(Point2D( 0, +1), Angle2D(Angle::Degrees(180))), true));
	Physics2D_Manager.Objects.Insert(Physics2D::Object(Physics2D_Manager.MainInstances[wall], Trans2D(Point2D(-1,  0), Angle2D(Angle::Degrees(270))), true));



	unsigned int obj0 = 1;
	Physics2D_Manager.MainInstances[obj0].Buffer_PolyGon.Create();
	{
		PolyGon & poly_gon = *(Physics2D_Manager.MainInstances[obj0].PolyGon);
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(+0.1f, -0.1f), ColorF4(1, 0, 0)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(-0.1f, -0.1f), ColorF4(0, 1, 0)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D( 0.0f, +0.1f), ColorF4(0, 0, 1)));
		poly_gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(0), PolyGon::SideCorner(1), PolyGon::SideCorner(2)));
	}

//	Physics2D_Manager.Objects.Insert(Physics2D::Object(Physics2D_Manager.MainInstances[obj0], Trans2D(Point2D(+0.3f, -0.1f), Angle2D(Angle::Degrees(160))), Trans2D(Point2D(0.0f, 0.1f), Angle2D(Angle::Degrees(45))), false));

//	Physics2D_Manager.Objects.Insert(Physics2D::Object(Physics2D_Manager.MainInstances[obj0], Trans2D(Point2D(0.0f, 0.0f), Angle2D(Angle::Degrees(0))), Trans2D(Point2D(0.0f, 0.0f), Angle2D()), false));

//	Physics2D_Manager.Objects.Insert(Physics2D::Object(Physics2D_Manager.MainInstances[obj0], Trans2D(Point2D(+0.3f, -0.1f), Angle2D(Angle::Degrees(160))), Trans2D(Point2D(-0.1f, 0.0f), Angle2D()), false));
//	Physics2D_Manager.Objects.Insert(Physics2D::Object(Physics2D_Manager.MainInstances[obj0], Trans2D(Point2D(-0.3f, -0.1f), Angle2D(Angle::Degrees( 80))), Trans2D(Point2D(+0.1f, 0.0f), Angle2D()), false));
//	Physics2D_Manager.Objects.Insert(Physics2D::Object(Physics2D_Manager.MainInstances[obj0], Trans2D(Point2D(+0.3f, +0.1f), Angle2D(Angle::Degrees(190))), Trans2D(Point2D(-0.1f, 0.0f), Angle2D()), false));
//	Physics2D_Manager.Objects.Insert(Physics2D::Object(Physics2D_Manager.MainInstances[obj0], Trans2D(Point2D(-0.3f, +0.1f), Angle2D(Angle::Degrees(140))), Trans2D(Point2D(+0.1f, 0.0f), Angle2D()), false));

//	Stuck in Wall. Bounces back "into" Wall every time it would get out.
//	No Force pushing it out.
//	Physics2D_Manager.Objects.Insert(Physics2D::Object(Physics2D_Manager.MainInstances[obj0], Trans2D(Point2D(-1.0f, 0.0f), Angle2D(Angle::Degrees(0))), Trans2D(Point2D(-1, 0), Angle2D()), false));



	unsigned int obj1 = 2;
	Physics2D_Manager.MainInstances[obj1].Buffer_PolyGon.Create();
	{
		PolyGon & poly_gon = *(Physics2D_Manager.MainInstances[obj1].PolyGon);
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(+0.025f, -0.400f), ColorF4(1, 0, 0)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(-0.025f, -0.400f), ColorF4(0, 1, 0)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D( 0.000f, +0.400f), ColorF4(0, 0, 1)));
		poly_gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(0), PolyGon::SideCorner(1), PolyGon::SideCorner(2)));
	}

//	Physics2D_Manager.Objects.Insert(Physics2D::Object(Physics2D_Manager.MainInstances[obj1], Trans2D(Point2D(-0.3f, 0.000f), Angle2D(Angle::Degrees(90))), Trans2D(Point2D(0, 0), Angle2D()), false));
//	Physics2D_Manager.Objects.Insert(Physics2D::Object(Physics2D_Manager.MainInstances[obj1], Trans2D(Point2D(+0.3f, 0.025f), Angle2D(Angle::Degrees(180))), Trans2D(Point2D(0, 0), Angle2D(Angle::Degrees(-45))), false));



	for (unsigned int i = 0; i < Physics2D_Manager.MainInstances.Count(); i++)
	{
		Physics2D_Manager.MainInstances[i].Manager = &Physics2D_Manager;
		Physics2D_Manager.MainInstances[i].InitExternal();
		Physics2D_Manager.MainInstances[i].GraphicsCreate();
		Physics2D_Manager.MainInstances[i].InitInternal();
		Physics2D_Manager.MainInstances[i].UpdateMain();
	}
}



void Init()
{
	Physics2D_Manager.GraphicsCreate();

	Physics2D_Manager.InitInternal(ImageDir);
	Physics2D_Manager.Arrow_Main_Default();

	Make();

	GL::Disable(GL::Capability::DepthTest);
	GL::Disable(GL::Capability::CullFace);
}
void Free()
{
	Physics2D_Manager.Objects.Clear();
	for (unsigned int i = 0; i < Physics2D_Manager.MainInstances.Count(); i++)
	{
		Physics2D_Manager.MainInstances[i].GraphicsDelete();
		Physics2D_Manager.MainInstances[i].Dispose();
	}

	Physics2D_Manager.GraphicsDelete();
}



void UpdateView(float timeDelta)
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

		if (window.KeyBoardManager.Keys[UserParameter::KeyBoard::Keys::Q.Flags].IsDown()) { trans.Rot.Ang += Angle::Degrees(45); }
		if (window.KeyBoardManager.Keys[UserParameter::KeyBoard::Keys::E.Flags].IsDown()) { trans.Rot.Ang -= Angle::Degrees(45); }

		//if (window.KeyBoardManager.Keys[GLFW_KEY_LEFT_CONTROL].IsDown()) { move2D *= 30; }
		//trans.Rot = Angle2D(Angle::Radians(move3D.Y * 0.5f));
		view.Change(trans, timeDelta);
	}
	Multiform_View.ChangeData(view.Trans);
	Multiform_Scale.ChangeData(view.Scale);
}

void ScreenShot()
{
/*
	FrameBufferTest.Bind();

	GL::BindTexture(GL::TextureTarget::Texture2D, FrameBufferTest.Textures[!FrameBufferTest.TextureToUse]);
	GL::TexImage2D(GL::TextureTarget::Texture2D, 0, GL::TextureInternalFormat::Rgba, window.Size.Buffer.Full.X, window.Size.Buffer.Full.Y, 0, GL::TextureFormat::Rgba, GL::TextureType::UnsignedByte, nullptr);

	GL::TexParameteri(GL::TextureTarget::Texture2D, GL::TextureParameterName::TextureMagFilter, GL_NEAREST);
	GL::TexParameteri(GL::TextureTarget::Texture2D, GL::TextureParameterName::TextureMinFilter, GL_NEAREST);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, FrameBufferTest.Textures[!FrameBufferTest.TextureToUse], 0);
	unsigned int DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "something went wrong.\n";
	}
	else
	{
		FrameBufferTest.Bind();
		glViewport(0, 0, window.Size.Buffer.Full.X, window.Size.Buffer.Full.Y);
		GL::ClearColor(window.DefaultColor.R, window.DefaultColor.G, window.DefaultColor.B, window.DefaultColor.A);
		GL::Clear(GL::ClearMask::ColorBufferBit);
		Draw();

		FrameBufferTest.ToImage(ImageDir, window.Size.Buffer.Full.X, window.Size.Buffer.Full.Y);
	}

	FrameBufferTest.UnBind();
*/

	Image img(window.Size.Buffer.Full.X, window.Size.Buffer.Full.Y);

	GL::ReadPixels(0, 0, img.W(), img.H(), GL::PixelDataFormat::Rgba, GL::PixelDataType::UnsignedInt8888Rev, img.Data());

	std::string file_name = "ScreenShots/" + Debug::TimeStampFileName() + ".bmp";
	std::cout << "ScreenShot: " << file_name << ' ' << img.W() << 'x' << img.H() << '\n';

	BitMap::Save(ImageDir.File(file_name.c_str()), img);
	img.Dispose();
}

void Draw()
{
	Physics2D_Manager.Draw();
}

void Frame(double timeDelta)
{
	UpdateView(timeDelta);

	{
		if (window.KeyBoardManager.Keys[UserParameter::KeyBoard::Keys::P.Flags].IsPress()) { Paused = !Paused; }
		if (Paused)
		{
			if (window.KeyBoardManager.Keys[UserParameter::KeyBoard::Keys::P.Flags].IsDown())
			{
				Physics2D_Manager.Update(1 / 60.0f);
			}
			else if (window.KeyBoardManager.Keys[UserParameter::KeyBoard::Keys::I.Flags].IsPress())
			{
				Physics2D_Manager.Update(1 / 60.0f);
			}
		}
		else
		{
			Physics2D_Manager.Update(timeDelta);
		}

		Physics2D_Manager.UpdateGraphics();
	}

	{
		Point2D cursor = view * window.Size.Convert(window.MouseManager.CursorPosition());
		Object_Hovering = Physics2D_Manager.FindObjectIndex(cursor);
	}

	Drag.Update(view, window, Physics2D_Manager);



	Draw();

	if (window.KeyBoardManager.Keys[UserParameter::KeyBoard::Keys::F12.Flags].IsPress())
	{
		ScreenShot();
	}
}

void Resize(const DisplaySize & Size)
{
	Multiform_DisplaySize.ChangeData(Size);
}

void MouseScroll(UserParameter::Mouse::Scroll params)
{
	// put this stuff into view ?
	// make a function for view to spin around cursor / point ?

	Point2D cursor_rel = window.Size.Convert(window.MouseManager.CursorPosition());
	Point2D cursor_abs = view * cursor_rel;

	if (params.Y < 0.0f) { while (params.Y < 0.0f) { view.Scale *= 2; params.Y++; } }
	if (params.Y > 0.0f) { while (params.Y > 0.0f) { view.Scale /= 2; params.Y--; } }
	
	#define ZOOM_MIN 1.0 / (1 << 6)
	#define ZOOM_MAX 1.0 * (1 << 6)

	if (view.Scale <= ZOOM_MIN) { view.Scale = ZOOM_MIN; }
	if (view.Scale >= ZOOM_MAX) { view.Scale = ZOOM_MAX; }

	view.Trans.Pos = cursor_abs - (view.Trans.Rot * (cursor_rel * view.Scale));
}
void MouseClick(UserParameter::Mouse::Click params)
{
	if (params.Action.IsPress())
	{
		if (params.Code == UserParameter::Mouse::Button::MouseL)
		{
			if (Object_Selected.IsValid())
			{
				Physics2D_Manager.Objects[Object_Selected.Value].Hide_WireFrame();
				Physics2D_Manager.Objects[Object_Selected.Value].Hide_WireFrameBox();
				Physics2D_Manager.Objects[Object_Selected.Value].Hide_Arrows();
			}

			Object_Selected = Object_Hovering;

			if (Object_Selected.IsValid())
			{
				Physics2D_Manager.Objects[Object_Selected.Value].Show_WireFrame();
				Physics2D_Manager.Objects[Object_Selected.Value].Show_WireFrameBox();
				Physics2D_Manager.Objects[Object_Selected.Value].Show_Arrows();
			}
		}
	}
	if (params.Action.IsRelease())
	{
		Drag.End();
	}
}
void MouseDrag(UserParameter::Mouse::Drag params)
{
	Drag.Begin(view * window.Size.Convert(params.Origin), Physics2D_Manager);
	Drag.Move(view * window.Size.Convert(params.Position));
}

void KeyBoardKey(UserParameter::KeyBoard::Key params)
{
	if (params.Action.IsPress())
	{
		if (params.Code == UserParameter::KeyBoard::Keys::Insert)
		{
			Physics2D_Manager.Objects.Insert(Physics2D::Object(Physics2D_Manager.MainInstances[1], Trans2D(view * window.Size.Convert(window.MouseManager.CursorPosition()), Angle2D()), false));
		}
		if (params.Code == UserParameter::KeyBoard::Keys::Delete)
		{
			if (Object_Selected.IsValid())
			{
				Physics2D_Manager.Objects.Remove(Object_Selected.Value);
				Object_Selected = Undex::Invalid();
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
