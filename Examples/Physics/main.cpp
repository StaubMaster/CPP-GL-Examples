
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
#include "PolyGon/Graphics/Full/Shader.hpp"
#include "PolyGon/Graphics/Full/Main/Data.hpp"

#include "PolyGon/PolyGon.hpp"

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
//#include "WireFrame2D/WireFrame2D.hpp"
//#include "WireFrame2D/Manager.hpp"

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

// Grid
# include "Grid2D/Grid2D.hpp"
# include "Grid2D/Graphics/Main/Data.hpp"
# include "Grid2D/Graphics/Main/Buffer.hpp"
# include "Grid2D/Graphics/Elem/Data.hpp"
# include "Grid2D/Graphics/Elem/Buffer.hpp"
# include "Grid2D/Graphics/Inst/Data.hpp"
# include "Grid2D/Graphics/Inst/Buffer.hpp"
# include "Grid2D/Graphics/Buffer.hpp"
# include "Grid2D/Graphics/Shader.hpp"

// Other
#include "Arrow2D/RankLengths.hpp"
#include "FrameTime.hpp"
#include "Physics2D/Collision/Projection.hpp"



// MainContext
#include "MainContext2D.hpp"

struct MainContext : public MainContext2D
{
Physics2D::Manager	Physics2D_Manager;

::SceneInteractionData	SceneData;
::InteractionObjectMove	InteractionObjectMove;
::InteractionObjectSpin	InteractionObjectSpin;
::InteractionObjectDrag	InteractionObjectApplyForce;
::InteractionObjectDrag	InteractionObjectApplyForceUnbound;

MainContext()
	: MainContext2D()
	, Physics2D_Manager()
	, SceneData(Physics2D_Manager)
{
	Physics2D_Manager.GraphicsInitExternal(ShaderDir);

	Container::Array<Shader::Base*> shaders({
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



//::ObjectForce	ObjectForce;



void Make() override
{
	//	Physics2D_Manager.AirResistance = 0.1f;
	//	Physics2D_Manager.GravityToY = 10.0f;
	//	Physics2D_Manager.GravityToY = 1.0f;
	Physics2D_Manager.Gravity = Point2D(0, -1.0f);



	InteractionObjectMove.Show();
	InteractionObjectSpin.Show();
	InteractionObjectApplyForce.Show();

	InteractionObjectApplyForceUnbound.Show();



	unsigned int idx;

	idx = Physics2D_Manager.MainInstances.Insert(Physics2D::InstanceManager()).Offset;
	Physics2D::InstanceManager & wall = Physics2D_Manager.MainInstances[idx];
	{
		float thickness0 = 1.0f;
		float thickness1 = 0.1f;
		PolyGon & polygon = *(wall.PolyGon);
		polygon.NewCorner(Point2D(-thickness0, 0), ColorF4(1, 1, 1));
		polygon.NewCorner(Point2D(+thickness0, 0), ColorF4(1, 1, 1));
		polygon.NewCorner(Point2D(-thickness0 - thickness1, -thickness1), ColorF4(0, 0, 0));
		polygon.NewCorner(Point2D(+thickness0 + thickness1, -thickness1), ColorF4(0, 0, 0));
		polygon.NewFace(0, 1, 2);
		polygon.NewFace(2, 1, 3);
	}
	wall.Manager = &Physics2D_Manager;

	idx = Physics2D_Manager.MainInstances.Insert(Physics2D::InstanceManager()).Offset;
	Physics2D::InstanceManager & obj0 = Physics2D_Manager.MainInstances[idx];
	{
		PolyGon & polygon = *(obj0.PolyGon);
		polygon.NewCorner(Point2D(+0.1f, -0.1f), ColorF4(1, 0, 0));
		polygon.NewCorner(Point2D(-0.1f, -0.1f), ColorF4(0, 1, 0));
		polygon.NewCorner(Point2D( 0.0f, +0.1f), ColorF4(0, 0, 1));
		polygon.NewFace(0, 1, 2);
	}
	obj0.Manager = &Physics2D_Manager;

	idx = Physics2D_Manager.MainInstances.Insert(Physics2D::InstanceManager()).Offset;
	Physics2D::InstanceManager & obj1 = Physics2D_Manager.MainInstances[idx];
	{
		float size = 0.1f;
		PolyGon & polygon = *(obj1.PolyGon);
		polygon.NewCorner(Point2D(-size, -size), ColorF4(0, 1, 0));
		polygon.NewCorner(Point2D(+size, -size), ColorF4(0, 0, 1));
		polygon.NewCorner(Point2D(+size, +size), ColorF4(0, 1, 0));
		polygon.NewCorner(Point2D(-size, +size), ColorF4(1, 0, 0));
		polygon.NewFace(0, 1, 2);
		polygon.NewFace(2, 0, 3);
	}
	obj1.Manager = &Physics2D_Manager;

	idx = Physics2D_Manager.MainInstances.Insert(Physics2D::InstanceManager()).Offset;
	Physics2D::InstanceManager & obj2 = Physics2D_Manager.MainInstances[idx];
	{
		PolyGon & polygon = *(obj2.PolyGon);
		//polygon.NewCorner(Point2D(-0.5f, -0.025f), ColorF4(0, 1, 0));
		//polygon.NewCorner(Point2D(+0.5f, -0.025f), ColorF4(0, 0, 1));
		//polygon.NewCorner(Point2D(+0.5f, +0.025f), ColorF4(0, 1, 0));
		//polygon.NewCorner(Point2D(-0.5f, +0.025f), ColorF4(1, 0, 0));
		polygon.NewCorner(Point2D(-1.0f, -0.1f), ColorF4(0, 1, 0));
		polygon.NewCorner(Point2D(+1.0f, -0.1f), ColorF4(0, 0, 1));
		polygon.NewCorner(Point2D(+1.0f, +0.1f), ColorF4(0, 1, 0));
		polygon.NewCorner(Point2D(-1.0f, +0.1f), ColorF4(1, 0, 0));
		polygon.NewFace(0, 1, 2);
		polygon.NewFace(2, 0, 3);
	}
	obj2.Manager = &Physics2D_Manager;

	for (unsigned int i = 0; i < Physics2D_Manager.MainInstances.Count(); i++)
	{
		Physics2D_Manager.MainInstances[i].Changed();
		Physics2D_Manager.MainInstances[i].Manager = &Physics2D_Manager;
		Physics2D_Manager.MainInstances[i].GraphicsInitExternal();
		Physics2D_Manager.MainInstances[i].GraphicsCreate();
		Physics2D_Manager.MainInstances[i].GraphicsInitInternal();
		Physics2D_Manager.MainInstances[i].GraphicsUpdateMain();
	}



	{
		wall.MakeCurrent();
		float thickness0 = 1.0f;
		//Physics2D::Object::Construct(Trans2D(Point2D(0, -thickness0), Angle2D(Angle::Degrees(  0))), true);
		//Physics2D::Object::Construct(Trans2D(Point2D(+thickness0, 0), Angle2D(Angle::Degrees( 90))), true);
		//Physics2D::Object::Construct(Trans2D(Point2D(0, +thickness0), Angle2D(Angle::Degrees(180))), true);
		//Physics2D::Object::Construct(Trans2D(Point2D(-thickness0, 0), Angle2D(Angle::Degrees(270))), true);
		(void)thickness0;
	}

	{
		obj2.MakeCurrent();
		//Physics2D::Object::Construct(Trans2D(), Trans2D(Point2D(), Angle2D(Angle::Degrees(90))), false);
		Physics2D::Object::Construct(Trans2D(Point2D(0, 0.0f), Angle2D(Angle::Degrees(0))), Trans2D(), true);
		Physics2D::Object::Construct(Trans2D(Point2D(0, 0.5f), Angle2D(Angle::Degrees(15))), Trans2D(), false);
		//Physics2D::Object::Construct(Trans2D(Point2D(0, 1.5f), Angle2D(Angle::Degrees(90))), Trans2D(), false);
	}


//	Physics2D_Manager.Objects.Insert(Physics2D::Object(obj0, Trans2D(Point2D(+0.3f, -0.1f), Angle2D(Angle::Degrees(160))), Trans2D(Point2D(0.0f, 0.1f), Angle2D(Angle::Degrees(45))), false));

//	Physics2D_Manager.Objects.Insert(Physics2D::Object(obj0, Trans2D(Point2D(0.0f, 0.0f), Angle2D(Angle::Degrees(0))), Trans2D(Point2D(0.0f, 0.0f), Angle2D()), false));

//	Physics2D_Manager.Objects.Insert(Physics2D::Object(obj0, Trans2D(Point2D(+0.3f, -0.1f), Angle2D(Angle::Degrees(160))), Trans2D(Point2D(-0.1f, 0.0f), Angle2D()), false));
//	Physics2D_Manager.Objects.Insert(Physics2D::Object(obj0, Trans2D(Point2D(-0.3f, -0.1f), Angle2D(Angle::Degrees( 80))), Trans2D(Point2D(+0.1f, 0.0f), Angle2D()), false));
//	Physics2D_Manager.Objects.Insert(Physics2D::Object(obj0, Trans2D(Point2D(+0.3f, +0.1f), Angle2D(Angle::Degrees(190))), Trans2D(Point2D(-0.1f, 0.0f), Angle2D()), false));
//	Physics2D_Manager.Objects.Insert(Physics2D::Object(obj0, Trans2D(Point2D(-0.3f, +0.1f), Angle2D(Angle::Degrees(140))), Trans2D(Point2D(+0.1f, 0.0f), Angle2D()), false));

//	Stuck in Wall. Bounces back "into" Wall every time it would get out.
//	No Force pushing it out.
//	Physics2D_Manager.Objects.Insert(Physics2D::Object(obj0, Trans2D(Point2D(-1.0f, 0.0f), Angle2D(Angle::Degrees(0))), Trans2D(Point2D(-1, 0), Angle2D()), false));



//	Physics2D_Manager.Objects.Insert(Physics2D::Object(obj1, Trans2D(Point2D(-0.3f, 0.000f), Angle2D(Angle::Degrees(90))), Trans2D(Point2D(0, 0), Angle2D()), false));
//	Physics2D_Manager.Objects.Insert(Physics2D::Object(obj1, Trans2D(Point2D(+0.3f, 0.025f), Angle2D(Angle::Degrees(180))), Trans2D(Point2D(0, 0), Angle2D(Angle::Degrees(-45))), false));
}



void Init() override
{
	Physics2D_Manager.GraphicsCreate();
	Physics2D_Manager.GraphicsInitInternal(ImageDir);
	Physics2D_Manager.Arrow.GraphicsUpdateMain();

	Make();

	GL::Disable(GL::Capability::DepthTest);
	GL::Disable(GL::Capability::CullFace);

	//CheckMomentOfInertia_Arrows.Allocate(Physics2D_Manager.Arrow.Instances, 10);
	//CheckMomentOfInertia_Arrows.Allocate(Arrow2D::Manager::Current().Instances, 10);
	//CheckMomentOfInertia_Arrows.Allocate(10);
}
void Free() override
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



// turn this into another "Manager"
void GridTest()
{
	Grid2DGraphics::Shader shader;
	{
		Container::Array<::Shader::Code> code({
			::Shader::Code(ShaderDir.File("Grid2D/Grid2D.vert")),
			::Shader::Code(ShaderDir.File("Grid2D/Basic.frag")),
		});
		shader.Change(code);
	}
	Grid2DGraphics::Buffer buffer(GL::DrawMode::Lines, 2);
	{
		buffer.Main.Pos.Change(0);
		buffer.Inst.Pos.Change(1);
		buffer.Inst.Size.Change(2);
	}

	Grid2D & grid = SceneData.Grid;

	shader.Create();
	buffer.Create();
	buffer.Main.ChangeAttributeBinding();
	buffer.Inst.ChangeAttributeBinding();
	{
		shader.Bind();
		shader.DisplaySize.Put(window.Size);
		shader.View.Put(view.Trans);
		shader.Scale.Put(view.Scale);

		buffer.Bind();
		{
{
	Container::Binary<Grid2DGraphics::Main::Data> data;
	Grid2DGraphics::Main::Data temp;
	for (unsigned int i = 0; i <= grid.LinSections; i++)
	{
		float t = ((float)i) / grid.LinSections;
		temp.Pos = Point2D(0, t); data.Insert(temp);
	}
	for (unsigned int i = 0; i <= grid.LinSections; i++)
	{
		float t = ((float)i) / grid.LinSections;
		temp.Pos = Point2D(1, t); data.Insert(temp);
	}
	for (unsigned int i = 0; i <= grid.LinSections; i++)
	{
		float t = ((float)i) / grid.LinSections;
		temp.Pos = Point2D(t, 0); data.Insert(temp);
	}
	for (unsigned int i = 0; i <= grid.LinSections; i++)
	{
		float t = ((float)i) / grid.LinSections;
		temp.Pos = Point2D(t, 1); data.Insert(temp);
	}
	buffer.Main.Change(data);
}
{
	Container::Binary<Grid2DGraphics::Elem::Data> data;
	Grid2DGraphics::Elem::Data temp;
	for (unsigned int i = 0; i <= grid.LinSections; i++)
	{
		temp.udx[0] = i + (0 * grid.LinSections) + 0;
		temp.udx[1] = i + (1 * grid.LinSections) + 1;
		data.Insert(temp);
	}
	for (unsigned int i = 0; i <= grid.LinSections; i++)
	{
		temp.udx[0] = i + (2 * grid.LinSections) + 1;
		temp.udx[1] = i + (3 * grid.LinSections) + 2;
		data.Insert(temp);
	}
	buffer.Elem.Change(data);
}
{
/* these are grid Sections
	the grid has a float Scale
	aligh the grid Sections with that Scale
	relative to the Origin
*/

	Container::Binary<Grid2DGraphics::Inst::Data> data;
	Grid2DGraphics::Inst::Data temp;

	Point2D pos(
		floor(view.Trans.Pos.X / (grid.Lin * grid.LinSections)) * (grid.Lin * grid.LinSections),
		floor(view.Trans.Pos.Y / (grid.Lin * grid.LinSections)) * (grid.Lin * grid.LinSections)
	);

	float k = 2;
	for (int y = +k; y >= -k; y--)
	{
		for (int x = +k; x >= -k; x--)
		{
			temp.Pos.X = pos.X + (x * grid.Lin * grid.LinSections);
			temp.Pos.Y = pos.Y + (y * grid.Lin * grid.LinSections);
			temp.Size = grid.Lin * grid.LinSections;
			data.Insert(temp);
		}
	}

	buffer.Inst.Change(data);
}
		}

		buffer.Draw();

		{
{
	Container::Binary<Grid2DGraphics::Main::Data> data;
	Grid2DGraphics::Main::Data temp;
	temp.Pos = Point2D(); data.Insert(temp);
	for (unsigned int i = 0; i < grid.AngSections; i++)
	{
		temp.Pos = Angle2D(Angle::Section(grid.AngSections) * i) * Point2D(1, 0);
		data.Insert(temp);
	}
	buffer.Main.Change(data);
}
{
	Container::Binary<Grid2DGraphics::Elem::Data> data;
	Grid2DGraphics::Elem::Data temp;
	for (unsigned int i = 0; i < grid.AngSections; i++)
	{
		temp.udx[0] = 0;
		temp.udx[1] = i + 1;
		data.Insert(temp);
		if (i == 0)
		{
			temp.udx[0] = grid.AngSections;
			temp.udx[1] = i + 1;
		}
		else
		{
			temp.udx[0] = i + 0;
			temp.udx[1] = i + 1;
		}
		data.Insert(temp);
	}
	buffer.Elem.Change(data);
}
{
	Container::Binary<Grid2DGraphics::Inst::Data> data;
	Grid2DGraphics::Inst::Data temp;
	if (SceneData.Selected)
	{
		temp.Pos = Physics2D_Manager.Objects[SceneData.Selected] -> ExtData.Now.Pos;
		temp.Size = view.Scale * 0.5f;
		data.Insert(temp);
	}
	buffer.Inst.Change(data);
}
		}
		buffer.Draw();
	}
	shader.Delete();
	buffer.Delete();
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
	GridTest();
}

void Frame(double timeDelta) override
{
	FrameTime frame_time(60.0f);
	frame_time.Update(timeDelta);
	SceneData.FrameTime.Update(timeDelta);

	UpdateView(frame_time);

	if (window.KeyBoardManager[Keys::Space].State == State::Press) { SceneData.IsRunning = !SceneData.IsRunning; }
	SceneData.IsSimulating = SceneData.IsRunning;
	if (!SceneData.IsSimulating)
	{
		if (window.KeyBoardManager[Keys::O].State == State::Down)
		{ SceneData.IsSimulating = true; }
		else if (window.KeyBoardManager[Keys::I].State == State::Press)
		{ SceneData.IsSimulating = true; }
	}

	if (window.KeyBoardManager[Keys::Home].State == State::Press)
	{
		if (SceneData.Selected)
		{
			Physics2D_Manager.Objects[SceneData.Selected] -> ExtData.Vel = Trans2D();
		}
	}

	if (window.KeyBoardManager[Keys::NumPadAdd].State == State::Press)
	{
		Physics2D::Collision::Projection::DebugEdgeUndex++;
	}
	if (window.KeyBoardManager[Keys::NumPadSub].State == State::Press)
	{
		Physics2D::Collision::Projection::DebugEdgeUndex--;
	}
	if (SceneData.Selected)
	{
		Physics2D::Collision::Projection::DebugObject = Physics2D_Manager.Objects[SceneData.Selected];
	}
	else
	{
		Physics2D::Collision::Projection::DebugObject = nullptr;
	}


	{
		SceneData.Cursor = view * window.Size.Convert(window.MouseManager.CursorPosition());
		SceneData.Hovering = Physics2D_Manager.FindObjectIndex(SceneData.Cursor);

		InteractionObjectMove.Change(SceneData);
		InteractionObjectSpin.Change(SceneData);
		InteractionObjectApplyForce.Change(SceneData);
	}

	{
		if (SceneData.IsSimulating)
		{
			Physics2D_Manager.Update(timeDelta);
		}
		else
		{
			Physics2D_Manager.Update(0.0f);
		}

		InteractionObjectMove.Update(SceneData);
		InteractionObjectSpin.Update(SceneData);
		InteractionObjectApplyForce.Update(SceneData);
		InteractionObjectApplyForceUnbound.Update(SceneData);

		Physics2D_Manager.GraphicsUpdate();
	}

	/*if (SceneData.Selected)
	{
		Physics2D::Object & obj = *Physics2D_Manager.Objects[SceneData.Selected];
		obj.ExtData.Update(obj.IntData);
		std::cout << obj.IntData;
		std::cout << obj.ExtData;
	}*/

	Draw();

	if (window.KeyBoardManager[Keys::F12].State == State::Press)
	{
		ScreenShot();
	}
}

void MouseScroll(ScrollArgs args) override
{
	UpdateViewZoom(args);
}
void MouseClick(ClickArgs params) override
{
	if (params.Action == Action::Press)
	{
		if (params.Button == MouseButtons::MouseL)
		{
			if (SceneData.Selected.IsValid())
			{
				Physics2D_Manager.Objects[SceneData.Selected] -> Hide_WireFrame();
				Physics2D_Manager.Objects[SceneData.Selected] -> Hide_WireFrameBox();
				Physics2D_Manager.Objects[SceneData.Selected] -> Hide_Arrows();
			}

			SceneData.Selected = SceneData.Hovering;

			if (SceneData.Selected.IsValid())
			{
				Physics2D_Manager.Objects[SceneData.Selected] -> Show_WireFrame();
				Physics2D_Manager.Objects[SceneData.Selected] -> Show_WireFrameBox();
				Physics2D_Manager.Objects[SceneData.Selected] -> Show_Arrows();
			}
		}
	}

	//if (!params.Mods.IsControl())
	if ((params.Mods & Modifier::Control) == Modifier::Control)
	{
		if (params.Button == MouseButtons::MouseL)
		{
			if (params.Action == Action::Press)
			{
				InteractionObjectMove.Start(SceneData);
			}
		}
		if (params.Button == MouseButtons::MouseR)
		{
			if (params.Action == Action::Press)
			{
				InteractionObjectSpin.Start(SceneData);
			}
		}
	}

	//if (params.Mods.IsControl())
	if (params.Mods == Modifier::Control)
	{
		if (params.Button == MouseButtons::MouseL)
		{
			if (params.Action == Action::Press)
			{
				InteractionObjectApplyForce.Start(SceneData);
			}
		}
	}

	if (params.Action == Action::Release)
	{
		InteractionObjectMove.End(SceneData);
		InteractionObjectSpin.End(SceneData);
		InteractionObjectApplyForce.End(SceneData);
	}
}
void MouseDrag(DragArgs args) override
{
	UpdateViewDrag(args);
}

void KeyBoardKey(KeyArgs args) override
{
	// when use this vs check in Framge ?
	if (args.Action == Action::Press)
	{
		if (args.Key == Keys::Insert)
		{
			Physics2D_Manager.MainInstances[2].MakeCurrent();
			Physics2D::Object & obj = Physics2D::Object::Construct(
				Trans2D(view * window.Size.Convert(window.MouseManager.CursorPosition()), Angle2D()),
				Trans2D(Point2D(), Angle2D()),
				false
			);
			(void)obj;
		}
		if (args.Key == Keys::Delete)
		{
			try
			{
				if (SceneData.Selected.IsValid())
				{
					std::cout << "Delete: " << SceneData.Selected << '\n';
					delete Physics2D_Manager.Objects[SceneData.Selected.Value];
					Physics2D_Manager.Objects.Remove(SceneData.Selected.Value);
					SceneData.Selected = Undex::Invalid();
				}
			}
			catch (std::exception & e)
			{
				std::cerr << "Failed to Delete Object " << SceneData.Selected << ": " << e.what() << '\n';
			}
		}

		if (args.Key == Keys::Escape)
		{
			InteractionObjectMove.Escape(SceneData);
			InteractionObjectSpin.Escape(SceneData);
			InteractionObjectApplyForce.Escape(SceneData);
		}
		if (args.Key == Keys::R)
		{
			if (!InteractionObjectApplyForceUnbound.Object.IsValid())
			{
				if (InteractionObjectApplyForce.Object.IsValid())
				{
					InteractionObjectApplyForceUnbound.Object = InteractionObjectApplyForce.Object;
					InteractionObjectApplyForceUnbound.Offset = InteractionObjectApplyForce.Offset;
					InteractionObjectApplyForceUnbound.Target = InteractionObjectApplyForce.Target;
					InteractionObjectApplyForce.End(SceneData);
				}
			}
			else
			{
				InteractionObjectApplyForceUnbound.End(SceneData);
			}
		}
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
			MainContext context;
			//ret = context.Main();
			ret = context.Run();
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
