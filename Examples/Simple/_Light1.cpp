
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



struct MainContext : public MainContext3D
{
struct SpotLightEntry
{
	Point3D		Position;
	Point3D		Target;
	LightSpot	* Light;
	EntryContainer::Entry<Simple3D::Data>	EntryLight;
	EntryContainer::Entry<Simple3D::Data>	EntryHolder;

	SpotLightEntry() :
		Position(),
		Target(),
		Light(NULL),
		EntryLight(),
		EntryHolder()
	{ }

	void LookFromTo(Point3D from, Point3D to)
	{
		Position = from;
		Target = to;
	}
	void Update()
	{
		Angle3D angle = Angle3D::FromPoint3D(Target - Position);

		if (Light != NULL)
		{
			//Light -> Pos = Position + angle.rotate(Point3D(0, 0, 3));
			Light -> Pos = Position + (angle.Mat.Multiply0(Point3D(0, 0, 3)));
			Light -> Dir = (Target - Position).normalize();
		}

		if (EntryLight.Is())
		{
			(*EntryLight).Trans.Pos = Position;
			(*EntryLight).Trans.Rot = angle;
		}

		if (EntryHolder.Is())
		{
			(*EntryHolder).Trans.Pos = Position;
			(*EntryHolder).Trans.Rot = Angle3D(angle.X, Angle(), Angle());
		}
	}

	void Toggle()
	{
		if (Light -> Base.Intensity == 0.0f)
		{
			Light -> Base.Intensity = 1.0f;
		}
		else
		{
			Light -> Base.Intensity = 0.0f;
		}
	}
};

float Light_Ambient_Intensity;
LightBase Light_Ambient;
//Uniform::LightBase * Uni_Light_Ambient;

float Light_Solar_Intensity;
LightSolar Light_Solar;
//Uniform::LightSolar * Uni_Light_Solar;

#define Light_Spot_Limit 4
LightSpot * Light_Spot_Array;
SpotLightEntry * Light_Spot_Entry_Array;

//Uniform::GArray<Uniform::LightSpot, LightSpot> * Uni_Light_Spot_Array;

unsigned int Light_Spot_Count;
//Uniform::UInt1 * Uni_Light_Spot_Count;

class CLightShader : public PolyHedra_Simple3D::Shader
{
	public:
	Uniform::LightBase								Light_Ambient;
	Uniform::LightSolar								Light_Solar;
	Uniform::GArray<Uniform::LightSpot, LightSpot>	Light_Spot_Array;
	Uniform::UInt1									Light_Spot_Count;

	public:
	CLightShader()
		: PolyHedra_Simple3D::Shader(),
		Light_Ambient(*this, "Ambient"),
		Light_Solar(*this, "Solar"),
		Light_Spot_Array(Light_Spot_Limit, *this, "SpotArr"),
		Light_Spot_Count(*this, "SpotCount")
	{ }
	~CLightShader()
	{ }
};



CLightShader LightShader;

PolyHedra_Simple3D::BufferArray		TestBuffer;

PolyHedra * PH;

~MainContext()
{ }
MainContext()
	: MainContext3D()
	, LightShader()
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
		LightShader.Change(code);
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
	LightShader.Create();
	TestBuffer.Create();
}
void GraphicsDelete()
{
	LightShader.Delete();
	TestBuffer.Delete();
}



void Make() override
{
	
}

void Init() override
{
	MainInit();

	std::cout << "Init 0\n";

	InitExternal();
	GraphicsCreate();
	InitInternal();

	GL::Disable(GL::Capability::CullFace);
	GL::Disable(GL::Capability::DepthTest);

	{
		LightShader.Bind();
		LightShader.Depth.Put(view.Depth);
		LightShader.FOV.Put(view.FOV);
	}

	{
		PH = PolyHedra::Generate::HexaHedron();
		//PolyHedra_3D_Manager.Insert(PH);
		Container::Pointer<PolyHedra_Main::Data> data = PH -> ToMainData();
		TestBuffer.Main.Change(data);
		data.Clear();
	}

	std::cout << "Init 1\n";
}
void Free() override
{
	std::cout << "Free 0\n";

	for (unsigned int i = 0; i < Light_Spot_Limit; i++)
	{
		Light_Spot_Entry_Array[i].EntryLight.Dispose();
		Light_Spot_Entry_Array[i].EntryHolder.Dispose();
	}

	//PolyHedra_3D_Manager.Dispose();

	GraphicsDelete();

	std::cout << "Free 1\n";

	MainFree();
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

	std::cout << "view: " << view.Trans.Pos << '\n';

	LightShader.Bind();
	LightShader.View.Put(view.Trans);
	LightShader.FOV.Put(view.FOV);
	//Light_Spot.Pos = ViewTrans.Pos;
	//Light_Spot.Dir = ViewTrans.Rot.rotate(Point3D(0, 0, 1));

	if (window.KeyBoardManager[Keys::D1].State == State::Press)
	{
		if (Light_Ambient.Intensity == 0.0f)
		{ Light_Ambient.Intensity = Light_Ambient_Intensity; }
		else
		{ Light_Ambient.Intensity = 0.0f; }
	}
	if (window.KeyBoardManager[Keys::D2].State == State::Press)
	{
		if (Light_Solar.Base.Intensity == 0.0f)
		{ Light_Solar.Base.Intensity = Light_Solar_Intensity; }
		else
		{ Light_Solar.Base.Intensity = 0.0f; }
	}
	if (window.KeyBoardManager[Keys::D3].State == State::Press) { Light_Spot_Entry_Array[0].Toggle(); }
	if (window.KeyBoardManager[Keys::D4].State == State::Press) { Light_Spot_Entry_Array[1].Toggle(); }
	if (window.KeyBoardManager[Keys::D5].State == State::Press) { Light_Spot_Entry_Array[2].Toggle(); }

	for (unsigned int i = 0; i < Light_Spot_Limit; i++)
	{
		Light_Spot_Entry_Array[i].Update();
	}

	LightShader.Bind();
	LightShader.Light_Ambient.Put(Light_Ambient);
	LightShader.Light_Solar.Put(Light_Solar);

	for (unsigned int i = 0; i < LightShader.Light_Spot_Array.Limit; i++)
	{
		if (Light_Spot_Entry_Array[i].Light != NULL)
		{
			LightShader.Light_Spot_Array[i].Put(*(Light_Spot_Entry_Array[i].Light));
		}
	}

	{
		Container::Binary<Simple3D::Data> data;
		data.Insert(Simple3D::Data(Trans3D(Point3D(0, 0, 0), Angle3D())));
		TestBuffer.Inst.Change(data);
	}

	LightShader.Bind();
	TestBuffer.Draw();
}

void Resize(const DisplaySize & WindowSize)
{
	LightShader.Bind();
	LightShader.DisplaySize.Put(WindowSize);
	//Multi_WindowSize -> ChangeData(WindowSize);
}

void MouseScroll(ScrollArgs args) override { (void)args; }
void MouseClick(ClickArgs args) override { (void)args; }
void MouseDrag(DragArgs args) override { (void)args; }
void KeyBoardKey(KeyArgs args) override { (void)args; }

void MainInit()
{
	window.DefaultColor = ColorF4(0.0f, 0.0f, 0.0f);
	view.Depth.Color = window.DefaultColor;
	//view.Trans = Trans3D(Point3D(0, 10, -65), Angle3D());
	view.Trans = Trans3D(Point3D(0, 10, -20), Angle3D());

	Light_Ambient_Intensity = 0.01f;
	Light_Solar_Intensity = 0.2f;
	Light_Ambient = LightBase(Light_Ambient_Intensity, ColorF4(1.0f, 1.0f, 1.0f));
	Light_Solar = LightSolar(Light_Solar_Intensity, ColorF4(1.0f, 1.0f, 1.0f), Point3D(+1, -3, +2).normalize());

	Light_Spot_Array = new LightSpot[Light_Spot_Limit];
	Light_Spot_Array[0] = LightSpot(1.0f, ColorF4(1.0f, 0.0f, 0.0f), Point3D(), Point3D(), Range(0.8, 0.95));
	Light_Spot_Array[1] = LightSpot(1.0f, ColorF4(0.0f, 1.0f, 0.0f), Point3D(), Point3D(), Range(0.8, 0.95));
	Light_Spot_Array[2] = LightSpot(1.0f, ColorF4(0.0f, 0.0f, 1.0f), Point3D(), Point3D(), Range(0.8, 0.95));
	Light_Spot_Array[3] = LightSpot(1.0f, ColorF4(1.0f, 1.0f, 1.0f), Point3D(), Point3D(), Range(0.8, 0.95));
	Light_Spot_Count = 3;

	Light_Spot_Entry_Array = new SpotLightEntry[Light_Spot_Limit];
	Light_Spot_Entry_Array[0].LookFromTo(Point3D(+22, 30, -22), Point3D(0, 0, 0));
	Light_Spot_Entry_Array[1].LookFromTo(Point3D(  0, 30, +22), Point3D(0, 0, 0));
	Light_Spot_Entry_Array[2].LookFromTo(Point3D(-22, 30, -22), Point3D(0, 0, 0));
	Light_Spot_Entry_Array[3].LookFromTo(Point3D(  0, 30, -22), Point3D(0, 0, 0));

	Light_Spot_Entry_Array[0].Light = &Light_Spot_Array[0];
	Light_Spot_Entry_Array[1].Light = &Light_Spot_Array[1];
	Light_Spot_Entry_Array[2].Light = &Light_Spot_Array[2];
	Light_Spot_Entry_Array[3].Light = &Light_Spot_Array[3];
}
void MainFree()
{
	delete[] Light_Spot_Entry_Array;
	delete[] Light_Spot_Array;
}
};



int run()
{
	MainContext context;
	return context.Run();
}
