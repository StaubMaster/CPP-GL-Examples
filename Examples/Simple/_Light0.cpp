
// main
#include "../main.hpp"
#include "../FrameTime.hpp"
#include "../MainContext3D.hpp"

//
#include <iostream>
#include "OpenGL.hpp"
#include "Debug.hpp"

#include "DataInclude.hpp"
#include "DataShow.hpp"

#include "Graphics/Shader/Code.hpp"

// UniForm
#include "Graphics/UniformsInclude.hpp"
#include "Graphics/MultiformsInclude.hpp"

// PolyHedra
#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Generate.hpp"
#include "PolyHedra/Simple3D/ManagerMulti.hpp"
#include "PolyHedra/Simple3D/ManagerSingle.hpp"
#include "PolyHedra/Template.hpp"
#include "PolyHedra/Data.hpp"

// Containers
#include "Miscellaneous/Container/Array.hpp"
#include "Miscellaneous/Container/Binary.hpp"
#include "Miscellaneous/EntryContainer/Binary.hpp"

//#include "Window.hpp"
//#include "Function/Object.hpp"
//#include "ValueType/View.hpp"

#include "FileInfo.hpp"
//#include "DirectoryInfo.hpp"
#include "Image.hpp"

#include "Graphics/Buffer/MainInst.hpp"



struct MainContext : public MainContext3D
{
PolyHedra_Simple3D::Shader			TestShader;
PolyHedra_Simple3D::BufferArray		TestBuffer;

::PolyHedra * PH;



~MainContext()
{ }
MainContext()
	: MainContext3D()
	, TestShader()
	, TestBuffer()
	, PH(nullptr)
{ }



void InitExternal()
{
	{
		Container::Array<Shader::Code> code({
			Shader::Code(ShaderDir.File("PH/Simple3D.vert")),
			Shader::Code(ShaderDir.File("PH/Direct.frag")),
		});
		TestShader.Change(code);
	}
	{
		TestBuffer.Main.Position.Change(0);
		TestBuffer.Main.Normal.Change(1);
		TestBuffer.Main.Texture.Change(2);
		TestBuffer.Inst.Trans.Pos.Change(3);
		TestBuffer.Inst.Trans.Rot.Change(4, 5, 6);
	}
}
void InitInternal()
{
	{
		TestBuffer.Main.ChangeAttributeBinding();
		TestBuffer.Inst.ChangeAttributeBinding();
	}
}

void GraphicsCreate()
{
	TestShader.Create();
	TestBuffer.Create();
}
void GraphicsDelete()
{
	TestShader.Delete();
	TestBuffer.Delete();
}



void Make() override
{

}

void Init() override
{
	window.DefaultColor = ColorF4(0.5f, 0.0f, 0.0f);
	view.Depth.Color = window.DefaultColor;
	//view.Trans = Trans3D(Point3D(0, 10, -65), Angle3D());
	view.Trans = Trans3D(Point3D(0, 0, -1), Angle3D());

	std::cout << "Init 0\n";

	InitExternal();
	GraphicsCreate();
	InitInternal();

	GL::Disable(GL::Capability::CullFace);
	GL::Disable(GL::Capability::DepthTest);

	{
		TestShader.Bind();
		TestShader.Depth.Put(view.Depth);
		TestShader.FOV.Put(view.FOV);
	}

	{
		PH = PolyHedra::Generate::HexaHedron();

		//Container::Pointer<PolyHedra_Main::Data> data = PH -> ToMainData();
		//TestBuffer.Main.Change(data);
		//data.Clear();
	}

	std::cout << "Init 1\n";
}
void Free() override
{
	std::cout << "Free 0\n";

	GraphicsDelete();

	std::cout << "Free 1\n";
}

void Frame(double timeDelta)
{
	//if (window.KeyBoardManager.Keys[GLFW_KEY_TAB].IsPress()) { window.MouseManager.CursorModeToggle(); }
	//if (window.KeyBoardManager[Keys::Tab].State == State::Press) { window.MouseManager.CursorModeToggle(); }
	//if (window.MouseManager.CursorModeIsLocked())
	{
		//Trans3D trans = window.MoveSpinFromKeysCursor();
		Trans3D trans;
		trans.Pos = window.MoveFromKeys();
		//if (window.KeyBoardManager.Keys[GLFW_KEY_LEFT_CONTROL].IsDown()) { trans.Pos *= 10; }
		if (window.KeyBoardManager[Keys::LeftControl].State == State::Down) { trans.Pos *= 10; }
		trans.Pos *= 2;
		trans.Rot.X *= view.FOV * 0.005f;
		trans.Rot.Y *= view.FOV * 0.005f;
		trans.Rot.Z *= view.FOV * 0.005f;
		view.TransformFlatX(trans, timeDelta);
	}
	(void)timeDelta;

	TestShader.Bind();
	TestShader.View.Put(view.Trans);
	TestShader.FOV.Put(view.FOV);

	/*{
		Container::Binary<PolyHedra_Main::Data> data;
		PolyHedra_Main::Data temp;

		temp.Position = Point3D(0.25f, 0.25f, 0); data.Insert(temp);
		temp.Position = Point3D(0.75f, 0.25f, 0); data.Insert(temp);
		temp.Position = Point3D(0.25f, 0.75f, 0); data.Insert(temp);

		temp.Position = Point3D(0.75f, 0.25f, 0); data.Insert(temp);
		temp.Position = Point3D(0.25f, 0.75f, 0); data.Insert(temp);
		temp.Position = Point3D(0.75f, 0.75f, 0); data.Insert(temp);

		TestBuffer.Bind();
		TestBuffer.Main.Change(data);
	}*/

	{
		Container::Pointer<PolyHedra_Main::Data> data = PH -> ToMainData();
		TestBuffer.Bind();
		TestBuffer.Main.Change(data);
		for (unsigned int i = 0; i < data.Count(); i++)
		{
			std::cout << data[i].Position << '\n';
		}
		std::cout << '\n';
		data.Clear();
	}

	{
		Container::Binary<Simple3D::Data> data;

		data.Insert(Simple3D::Data(Trans3D(Point3D(0, 0, 0), Angle3D())));
		data.Insert(Simple3D::Data(Trans3D(Point3D(-3, 0, 0), Angle3D(Angle::Degrees(45), Angle(), Angle()))));
		data.Insert(Simple3D::Data(Trans3D(Point3D(-3, -3, 0), Angle3D(Angle(), Angle(), Angle::Degrees(45)))));

		TestBuffer.Bind();
		TestBuffer.Inst.Change(data);
	}

	TestBuffer.LogInfo();

	TestShader.Bind();
	TestBuffer.Draw();
}

void Resize(const DisplaySize & WindowSize) override
{
	std::cout << "Resize: " << WindowSize.Ratio.Value << '\n';
	std::cout << "Resize: " << WindowSize.Buffer.Full << '\n';
	std::cout << "Resize: " << WindowSize.Window.Full << '\n';
	TestShader.Bind();
	TestShader.DisplaySize.Put(WindowSize);
}

void MouseScroll(ScrollArgs args) override { (void)args; }
void MouseClick(ClickArgs args) override { (void)args; }
void MouseDrag(DragArgs args) override { (void)args; }
void KeyBoardKey(KeyArgs args) override { (void)args; }
};



int run()
{
	MainContext context;
	return context.Run();
}
