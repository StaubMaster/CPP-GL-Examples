
// C++
#include <iostream>
#include <sstream>
#include <exception>
#include <string>

// Stuff
#include "OpenGL.hpp"
#include "Debug.hpp"

// Data
#include "DataInclude.hpp"
#include "DataShow.hpp"
#include "ValueType/Intersect.hpp"

// Window and User
#include "Window.hpp"
#include "Function/Object.hpp"
#include "UserParameter/KeyBoardInclude.hpp"
#include "UserParameter/MouseInclude.hpp"

// File
#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"
#include "Image.hpp"


// Container
#include "Graphics/Shader/Code.hpp"
#include "Miscellaneous/Container/Array.hpp"
#include "Miscellaneous/Container/Binary.hpp"
#include "Miscellaneous/EntryContainer/Binary.hpp"



// PolyGon
#include "Physics2D/Shaders/PolyGon.hpp"
#include "PolyGon/Graphics/Data.hpp"
#include "Inst/Physics2D/Data.hpp"

#include "PolyGon/PolyGon.hpp"
#include "PolyGon/Data.hpp"

// Physics
#include "Physics2D/Collision.hpp"
#include "Physics2D/Manager.hpp"
#include "Physics2D/InstanceManager.hpp"
#include "Physics2D/Object.hpp"

// Arrow
#include "Arrow2D/Manager.hpp"
#include "Arrow2D/Shader.hpp"
#include "Arrow2D/Main/Data.hpp"
#include "Arrow2D/Inst/Data.hpp"
#include "Arrow2D/Object.hpp"

// WireFrame
#include "WireFrame2D/WireFrame2D.hpp"
#include "WireFrame2D/Manager.hpp"

// Multiform
#include "Graphics/MultiformsInclude.hpp"
#include "Graphics/Multiform/Trans2D.hpp"
#include "Graphics/Multiform/Float.hpp"

// BitMap
#include "FileFormat/BitMap/BitMap.hpp"

// Math
#include <math.h>

// Interaction
#include "SceneInteraction/Data.hpp"
#include "SceneInteraction/Base.hpp"

#include "SceneInteraction/Move.hpp"
#include "SceneInteraction/Spin.hpp"
#include "SceneInteraction/Force.hpp"

// Other
#include "Arrow2D/RankLengths.hpp"



struct MainContext
{
DirectoryInfo ImageDir;
DirectoryInfo ShaderDir;
DirectoryInfo PolyHedraDir;
DirectoryInfo TextDir;

Window	window;
View2D	view;

Multiform::DisplaySize			Multiform_DisplaySize;
Multiform::Trans2D				Multiform_View;
Multiform::Float				Multiform_Scale;

Physics2D::Manager	Physics2D_Manager;

::SceneInteractionData	SceneData;
::InteractionObjectMove	InteractionObjectMove;
::InteractionObjectSpin	InteractionObjectSpin;
::InteractionObjectApplyForce	InteractionObjectApplyForce;

MainContext()
	: ImageDir("../../media/Images")
	, ShaderDir("../../media/Shaders")
	, PolyHedraDir("../../media/YMT")
	, TextDir("../../media/Text")
	, window()
	, view(View2D::Default())
	, Multiform_DisplaySize("DisplaySize")
	, Multiform_View("View")
	, Multiform_Scale("Scale")
	, Physics2D_Manager()
	, SceneData(Physics2D_Manager)
{
	Physics2D_Manager.InitExternal(ShaderDir);

	Container::Array<Shader::Base *> shaders({
		&Physics2D_Manager.Shader_PolyGon,
		&Physics2D_Manager.Shader_WireFrame,
		&Physics2D_Manager.Arrow.Shader,
	});
	Multiform_DisplaySize.FindUniforms(shaders);
	Multiform_View.FindUniforms(shaders);
	Multiform_Scale.FindUniforms(shaders);

	SceneData.Selected = Undex::Invalid();
	SceneData.Hovering = Undex::Invalid();
}
~MainContext()
{
	Physics2D_Manager.Dispose();
}



struct ObjectForce
{
::Undex	Undex0;
Point2D	Point0;
Point2D	Point1;

ObjectForce()
	: Undex0(Undex::Invalid())
{ }

void Update(SceneInteractionData & SceneData)
{
	if (Undex0.IsValid())
	{
		Ray2D drag;
		drag.Pos = SceneData.Manager.Objects[Undex0.Value] -> AbsolutePositionOf(Point0);
		drag.Dir = Point1 - drag.Pos;

		Physics2D::ObjectForceData data = Physics2D::ApplyForce(SceneData.TimeDelta, *(SceneData.Manager.Objects[Undex0.Value]), drag, 10.0f, SceneData.IsSimulating);

		if (Arrows.Is())
		{
			Arrows[0] = Arrow2D::Inst::Data(ColorF4(0.0f, 0.0f, 0.0f), 16.0f, data.Contact);

			Arrows[1] = Arrow2D::Inst::Data(ColorF4(1.0f, 0.5f, 0.0f), 16.0f, data.Force);
			Arrows[2] = Arrow2D::Inst::Data(ColorF4(1.0f, 0.5f, 0.0f), 16.0f, data.ForcePos);
			Arrows[3] = Arrow2D::Inst::Data(ColorF4(1.0f, 0.5f, 0.0f), 16.0f, data.ForceRot);

			Arrows[4] = Arrow2D::Inst::Data(ColorF4(0.0f, 0.5f, 1.0f), 16.0f, data.ChangePos);
			Arrows[5] = Arrow2D::Inst::Data(ColorF4(0.0f, 0.5f, 1.0f), 16.0f, data.ChangeRot);
		}
	}
}

Arrow2D::Object	Arrows;
void Show()
{
	Arrows.Allocate(6);
}
void Hide()
{
	Arrows.Dispose();
}
};
MainContext::ObjectForce	ObjectForce;



/* PolyGon
	Lines that define the Edge of the PolyGon
	Triangles that are used for Drawing
*/
void Make()
{
//	Physics2D_Manager.Gravity = Point2D(0, -1.0f);
//	Physics2D_Manager.AirResistance = 0.1f;
//	Physics2D_Manager.GravityToY = 1.0f;

	InteractionObjectMove.Show();
	InteractionObjectSpin.Show();
	InteractionObjectApplyForce.Show();

	ObjectForce.Show();



	Physics2D_Manager.MainInstances.Allocate(4, 4);



	Physics2D::InstanceManager & wall = Physics2D_Manager.MainInstances[0];
	wall.Buffer_PolyGon.Create();
	{
		float thickness = 0.1f;
		PolyGon & poly_gon = *(wall.PolyGon);
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(-1, 0), ColorF4(1, 1, 1)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(+1, 0), ColorF4(1, 1, 1)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(-1 - thickness, -thickness), ColorF4(0, 0, 0)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(+1 + thickness, -thickness), ColorF4(0, 0, 0)));
		poly_gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(0), PolyGon::SideCorner(1), PolyGon::SideCorner(2)));
		poly_gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(2), PolyGon::SideCorner(1), PolyGon::SideCorner(3)));
	}
	wall.Manager = &Physics2D_Manager;

	wall.MakeCurrent();
	Physics2D::Object::Construct(Trans2D(Point2D( 0, -1), Angle2D(Angle::Degrees(  0))), true);
	Physics2D::Object::Construct(Trans2D(Point2D(+1,  0), Angle2D(Angle::Degrees( 90))), true);
	Physics2D::Object::Construct(Trans2D(Point2D( 0, +1), Angle2D(Angle::Degrees(180))), true);
	Physics2D::Object::Construct(Trans2D(Point2D(-1,  0), Angle2D(Angle::Degrees(270))), true);



	Physics2D::InstanceManager & obj0 = Physics2D_Manager.MainInstances[1];
	obj0.Buffer_PolyGon.Create();
	{
		PolyGon & poly_gon = *(obj0.PolyGon);
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(+0.1f, -0.1f), ColorF4(1, 0, 0)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(-0.1f, -0.1f), ColorF4(0, 1, 0)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D( 0.0f, +0.1f), ColorF4(0, 0, 1)));
		poly_gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(0), PolyGon::SideCorner(1), PolyGon::SideCorner(2)));
	}
	obj0.Manager = &Physics2D_Manager;

//	Physics2D_Manager.Objects.Insert(Physics2D::Object(obj0, Trans2D(Point2D(+0.3f, -0.1f), Angle2D(Angle::Degrees(160))), Trans2D(Point2D(0.0f, 0.1f), Angle2D(Angle::Degrees(45))), false));

//	Physics2D_Manager.Objects.Insert(Physics2D::Object(obj0, Trans2D(Point2D(0.0f, 0.0f), Angle2D(Angle::Degrees(0))), Trans2D(Point2D(0.0f, 0.0f), Angle2D()), false));

//	Physics2D_Manager.Objects.Insert(Physics2D::Object(obj0, Trans2D(Point2D(+0.3f, -0.1f), Angle2D(Angle::Degrees(160))), Trans2D(Point2D(-0.1f, 0.0f), Angle2D()), false));
//	Physics2D_Manager.Objects.Insert(Physics2D::Object(obj0, Trans2D(Point2D(-0.3f, -0.1f), Angle2D(Angle::Degrees( 80))), Trans2D(Point2D(+0.1f, 0.0f), Angle2D()), false));
//	Physics2D_Manager.Objects.Insert(Physics2D::Object(obj0, Trans2D(Point2D(+0.3f, +0.1f), Angle2D(Angle::Degrees(190))), Trans2D(Point2D(-0.1f, 0.0f), Angle2D()), false));
//	Physics2D_Manager.Objects.Insert(Physics2D::Object(obj0, Trans2D(Point2D(-0.3f, +0.1f), Angle2D(Angle::Degrees(140))), Trans2D(Point2D(+0.1f, 0.0f), Angle2D()), false));

//	Stuck in Wall. Bounces back "into" Wall every time it would get out.
//	No Force pushing it out.
//	Physics2D_Manager.Objects.Insert(Physics2D::Object(obj0, Trans2D(Point2D(-1.0f, 0.0f), Angle2D(Angle::Degrees(0))), Trans2D(Point2D(-1, 0), Angle2D()), false));



	Physics2D::InstanceManager & obj1 = Physics2D_Manager.MainInstances[2];
	obj1.Buffer_PolyGon.Create();
	{
		PolyGon & poly_gon = *(obj1.PolyGon);
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(-0.1f, -0.1f), ColorF4(0, 1, 0)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(-0.1f, +0.1f), ColorF4(1, 0, 0)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(+0.1f, -0.1f), ColorF4(0, 0, 1)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(+0.1f, +0.1f), ColorF4(0, 1, 0)));
		poly_gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(0), PolyGon::SideCorner(1), PolyGon::SideCorner(2)));
		poly_gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(2), PolyGon::SideCorner(1), PolyGon::SideCorner(3)));
	}
	obj1.Manager = &Physics2D_Manager;

//	Physics2D_Manager.Objects.Insert(Physics2D::Object(obj1, Trans2D(Point2D(-0.3f, 0.000f), Angle2D(Angle::Degrees(90))), Trans2D(Point2D(0, 0), Angle2D()), false));
//	Physics2D_Manager.Objects.Insert(Physics2D::Object(obj1, Trans2D(Point2D(+0.3f, 0.025f), Angle2D(Angle::Degrees(180))), Trans2D(Point2D(0, 0), Angle2D(Angle::Degrees(-45))), false));



	Physics2D::InstanceManager & obj2 = Physics2D_Manager.MainInstances[3];
	obj2.Buffer_PolyGon.Create();
	{
		PolyGon & poly_gon = *(obj2.PolyGon);
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(-1.0f, -0.1f), ColorF4(0, 1, 0)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(-1.0f, +0.1f), ColorF4(1, 0, 0)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(+1.0f, -0.1f), ColorF4(0, 0, 1)));
		poly_gon.Corners.Insert(PolyGon::Corner(Point2D(+1.0f, +0.1f), ColorF4(0, 1, 0)));
		poly_gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(0), PolyGon::SideCorner(1), PolyGon::SideCorner(2)));
		poly_gon.Sides.Insert(PolyGon::Side(PolyGon::SideCorner(2), PolyGon::SideCorner(1), PolyGon::SideCorner(3)));
	}
	obj2.Manager = &Physics2D_Manager;



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
	Physics2D_Manager.Arrow.Main_Default();

	Make();

	GL::Disable(GL::Capability::DepthTest);
	GL::Disable(GL::Capability::CullFace);

	//CheckMomentOfInertia_Arrows.Allocate(Physics2D_Manager.Arrow.Instances, 10);
	//CheckMomentOfInertia_Arrows.Allocate(Arrow2D::Manager::Current().Instances, 10);
	//CheckMomentOfInertia_Arrows.Allocate(10);
}
void Free()
{
	//CheckMomentOfInertia_Arrows.Dispose();

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
		trans.Pos = Point2D(move3D.X, move3D.Z) * 2.0f * view.Scale;

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

void Update(double timeDelta, bool is_paused)
{
	if (!is_paused)
	{
		Physics2D_Manager.Update(timeDelta);
	}
}

void Frame(double timeDelta)
{
	float WantedFramesPerSecond = 60.0f;
	float WantedFrameTime = 1.0f / WantedFramesPerSecond;
	// rename timeDelta to FrameTime
	// make a struct with other Frame Data ?
	// put all the WindowSize and Input stuff in there ?
	if (timeDelta > WantedFrameTime) { timeDelta = WantedFrameTime; }
	SceneData.TimeDelta = timeDelta;

	UpdateView(timeDelta);

	if (window.KeyBoardManager.Keys[UserParameter::KeyBoard::Keys::Space.Flags].IsPress()) { SceneData.IsRunning = !SceneData.IsRunning; }
	SceneData.IsSimulating = SceneData.IsRunning;
	if (!SceneData.IsSimulating)
	{
		if (window.KeyBoardManager.Keys[UserParameter::KeyBoard::Keys::O.Flags].IsDown())
		{ SceneData.IsSimulating = true; }
		else if (window.KeyBoardManager.Keys[UserParameter::KeyBoard::Keys::I.Flags].IsPress())
		{ SceneData.IsSimulating = true; }
	}

	{
		SceneData.Cursor = view * window.Size.Convert(window.MouseManager.CursorPosition());
		SceneData.Hovering = Physics2D_Manager.FindObjectIndex(SceneData.Cursor);

		InteractionObjectMove.Update(SceneData);
		InteractionObjectSpin.Update(SceneData);
		InteractionObjectApplyForce.Update(SceneData);
		ObjectForce.Update(SceneData);
	}

	{
		if (SceneData.IsSimulating)
		{
			Update(timeDelta, false);
		}

		Physics2D_Manager.GraphicsUpdate();
	}



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
	// Select / Select Box
	// View Move / Spin

	if (!params.Mods.IsControl())
	{
		if (params.Code == UserParameter::Mouse::Button::MouseL)
		{
			if (params.Action.IsPress())
			{
				InteractionObjectMove.Start(SceneData);
			}
		}
		if (params.Code == UserParameter::Mouse::Button::MouseR)
		{
			if (params.Action.IsPress())
			{
				InteractionObjectSpin.Start(SceneData);
			}
		}
	}

	if (params.Mods.IsControl())
	{
		if (params.Code == UserParameter::Mouse::Button::MouseL)
		{
			if (params.Action.IsPress())
			{
				InteractionObjectApplyForce.Start(SceneData);
			}
		}
	}

	if (params.Action.IsRelease())
	{
		InteractionObjectMove.End(SceneData);
		InteractionObjectSpin.End(SceneData);
		InteractionObjectApplyForce.End(SceneData);
	}

	if (params.Action.IsPress())
	{
		if (params.Code == UserParameter::Mouse::Button::MouseL)
		{
			if (SceneData.Selected.IsValid())
			{
				Physics2D_Manager.Objects[SceneData.Selected.Value] -> Hide_WireFrame();
				Physics2D_Manager.Objects[SceneData.Selected.Value] -> Hide_WireFrameBox();
				Physics2D_Manager.Objects[SceneData.Selected.Value] -> Hide_Arrows();
			}

			SceneData.Selected = SceneData.Hovering;

			if (SceneData.Selected.IsValid())
			{
				Physics2D_Manager.Objects[SceneData.Selected.Value] -> Show_WireFrame();
				Physics2D_Manager.Objects[SceneData.Selected.Value] -> Show_WireFrameBox();
				Physics2D_Manager.Objects[SceneData.Selected.Value] -> Show_Arrows();
			}
		}
	}
}
void MouseDrag(UserParameter::Mouse::Drag params)
{
	(void)params;
	/*if (Drag.FollowMouse)
	{
		Drag.Begin(view * window.Size.Convert(params.Origin), Physics2D_Manager);
		Drag.Move(view * window.Size.Convert(params.Position));
	}*/
}

void KeyBoardKey(UserParameter::KeyBoard::Key params)
{
	// when use this vs check in Framge ?
	if (params.Action.IsPress())
	{
		if (params.Code == UserParameter::KeyBoard::Keys::Insert)
		{
			Physics2D_Manager.MainInstances[3].MakeCurrent();
			Physics2D::Object & obj = Physics2D::Object::Construct(
				Trans2D(view * window.Size.Convert(window.MouseManager.CursorPosition()), Angle2D()),
				Trans2D(Point2D(), Angle2D()),
				false
			);
			obj.Mass = 1.0f;
		}
		if (params.Code == UserParameter::KeyBoard::Keys::Delete)
		{
			try
			{
				if (SceneData.Selected.IsValid())
				{
					std::cout << "Delete: " << SceneData.Selected << '\n';
					Physics2D_Manager.Objects.Remove(SceneData.Selected.Value);
					SceneData.Selected = Undex::Invalid();
				}
			}
			catch (std::exception & e)
			{
				std::cerr << "Failed to Delete Object " << SceneData.Selected << ": " << e.what() << '\n';
			}
		}

		if (params.Code == UserParameter::KeyBoard::Keys::Escape)
		{
			InteractionObjectMove.Escape(SceneData);
			InteractionObjectSpin.Escape(SceneData);
			InteractionObjectApplyForce.Escape(SceneData);
		}
		if (params.Code == UserParameter::KeyBoard::Keys::R)
		{
			if (!ObjectForce.Undex0.IsValid())
			{
				if (InteractionObjectApplyForce.Undex.IsValid())
				{
					ObjectForce.Undex0 = InteractionObjectApplyForce.Undex;
					ObjectForce.Point0 = InteractionObjectApplyForce.Contact;
					ObjectForce.Point1 = SceneData.Cursor;
					ObjectForce.Show();
				}
			}
			else
			{
				ObjectForce.Undex0 = Undex::Invalid();
				ObjectForce.Hide();
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
