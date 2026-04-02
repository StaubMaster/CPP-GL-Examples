
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

// PolyHedra
#include "PolyHedra/Graphics/Full/Shader.hpp"
#include "PolyHedra/Graphics/Full/Buffer.hpp"
#include "PolyHedra/Graphics/Full/Main/Data.hpp"

#include "PolyHedra/ObjectData.hpp"
#include "PolyHedra/InstanceManager.hpp"
#include "PolyHedra/Manager.hpp"
#include "PolyHedra/Object.hpp"



struct MainContext : public MainContext3D
{
::PolyHedraManager					PolyHedraManager;
Container::Binary<PolyHedraObject>	Objects;



~MainContext()
{ }
MainContext()
	: MainContext3D()
	, PolyHedraManager()
{
	PolyHedraManager.MakeCurrent();
}



struct SpotLightEntry
{
	Point3D		Position;
	Point3D		Target;
	LightSpot *	Light;
	PolyHedraObject		EntryLight;
	PolyHedraObject		EntryHolder;

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
			Light -> Pos = Position + (Point3D(0, 0, 3) * angle.Mat);
			Light -> Dir = (Target - Position).normalize();
		}

		EntryLight.Trans().Position = Position;
		EntryLight.Trans().Rotation = EulerAngle3D(angle.Z, angle.X, angle.Y);

		EntryHolder.Trans().Position = Position;
		EntryHolder.Trans().Rotation = EulerAngle3D(angle.X, Angle(), Angle());
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

float Light_Solar_Intensity;
LightSolar Light_Solar;

#define Light_Spot_Limit 4
LightSpot * Light_Spot_Array;
SpotLightEntry * Light_Spot_Entry_Array;

unsigned int Light_Spot_Count;

void LightsInit()
{
	//Light_Ambient_Intensity = 0.01f;
	//Light_Solar_Intensity = 0.2f;
	Light_Ambient_Intensity = 0.1f;
	Light_Solar_Intensity = 0.8f;
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
void LightsFree()
{
	delete[] Light_Spot_Entry_Array;
	delete[] Light_Spot_Array;
}



class CLightShader : public PolyHedraFull::Shader
{
	public:
	Uniform::LightBase								Light_Ambient;
	Uniform::LightSolar								Light_Solar;
	Uniform::GArray<Uniform::LightSpot, LightSpot>	Light_Spot_Array;
	Uniform::UInt									Light_Spot_Count;

	public:
	CLightShader()
		: PolyHedraFull::Shader()
		, Light_Ambient(*this, "Ambient")
		, Light_Solar(*this, "Solar")
		, Light_Spot_Array(Light_Spot_Limit, *this, "SpotArr")
		, Light_Spot_Count(*this, "SpotCount")
	{ }
	~CLightShader()
	{ }
};

CLightShader LightShader;



void GraphicsCreate()
{
	LightShader.Create();
	PolyHedraManager.GraphicsCreate();
}
void GraphicsDelete()
{
	LightShader.Delete();
	PolyHedraManager.GraphicsDelete();
}

void InitExternal()
{
	{
		Container::Array<Shader::Code> code({
			Shader::Code(MediaDirectory.File("Shaders/PH/Simple3D.vert")),
			Shader::Code(MediaDirectory.File("Shaders/PH/UniLight4.frag")),
			//Shader::Code(MediaDirectory.File("Shaders/PH/Direct.frag")),
		});
		LightShader.Change(code);
	}
	PolyHedraManager.InitExternal(MediaDirectory);
	PolyHedraManager.ShaderFullOther = &LightShader;
}
void InitInternal()
{
	{
		LightShader.Bind();
		LightShader.Depth.Put(view.Depth);
		LightShader.FOV.Put(view.FOV);
	}
	{
		PolyHedraManager.ShaderFullDefault.Bind();
		PolyHedraManager.ShaderFullDefault.Depth.Put(view.Depth);
		PolyHedraManager.ShaderFullDefault.FOV.Put(view.FOV);
	}
	PolyHedraManager.InitInternal();
}



void RandomCubes()
{
	PolyHedra * polyhedra = PolyHedra::Generate::HexaHedron();

	int Range_Size1 = 0x1FF;
	int Range_SizeH = 0x0FF;
	int j_len = 16;
	int i_len = 16;
	for (int j = 0; j < j_len; j++)
	{
		Point3D center(
			(std::rand() & Range_Size1) - Range_SizeH,
			(std::rand() & Range_Size1) - Range_SizeH,
			(std::rand() & Range_Size1) - Range_SizeH
		);
		EulerAngle3D rot = EulerAngle3D::Radians(
			(std::rand() & Range_Size1) - Range_SizeH,
			(std::rand() & Range_Size1) - Range_SizeH,
			(std::rand() & Range_Size1) - Range_SizeH
		);

		for (int i = 0; i < i_len; i++)
		{
			Objects.Insert(PolyHedraObject(polyhedra, Trans3D(
				center + Point3D(
					(std::rand() & Range_Size1) - Range_SizeH,
					(std::rand() & Range_Size1) - Range_SizeH,
					(std::rand() & Range_Size1) - Range_SizeH
				), rot
			)));
		}
	}
}

void FancyLights()
{
	DirectoryInfo dir = MediaDirectory.Child("YMT/Light");
	PolyHedra * stage_light =			PolyHedra::Load(dir.File("Stage_Light.polyhedra.ymt"));
	PolyHedra * stage_light_holder =	PolyHedra::Load(dir.File("Stage_Light_Holder.polyhedra.ymt"));

	for (unsigned int i = 0; i < Light_Spot_Limit; i++)
	{
		Light_Spot_Entry_Array[i].EntryLight = PolyHedraObject(stage_light);
		Light_Spot_Entry_Array[i].EntryHolder = PolyHedraObject(stage_light_holder);
	}
}

void Fancify()
{
	DirectoryInfo dir = MediaDirectory.Child("YMT/Light");
	PolyHedra * stage =					PolyHedra::Load(dir.File("Stage.polyhedra.ymt"));
	PolyHedra * truss =					PolyHedra::Load(dir.File("Truss_Square40cm_Len200cm.polyhedra"));
	PolyHedra * truss_cube =			PolyHedra::Load(dir.File("Truss_Cube40cm.polyhedra"));
	PolyHedra * chair =					PolyHedra::Load(dir.File("Chair.polyhedra.ymt"));

	Objects.Insert(PolyHedraObject(stage, Point3D(0, 0, 0)));

	float truss_long = 20.0f;
	float truss_wide = 4.5f;

	float w0 = truss_long * 1.0f;
	float w1 = truss_long * 1.5f + truss_wide * 0.5f;

	float h0 = truss_long * 0.5f;
	float h1 = truss_long * 1.5f;
	float h2 = truss_long * 2.0f + truss_wide * 0.5f;

	float d0 = truss_long * 0.5f;
	float d1 = truss_long * 1.0f + truss_wide * 0.5f;

	Objects.Insert(PolyHedraObject(truss,      Point3D(-w1, h0, -d1), EulerAngle3D::Degrees(0, 90, 0)));
	Objects.Insert(PolyHedraObject(truss,      Point3D(-w1, h1, -d1), EulerAngle3D::Degrees(0, 90, 0)));
	Objects.Insert(PolyHedraObject(truss_cube, Point3D(-w1, h2, -d1)));

	Objects.Insert(PolyHedraObject(truss,      Point3D(+w1, h0, -d1), EulerAngle3D::Degrees(0, 90, 0)));
	Objects.Insert(PolyHedraObject(truss,      Point3D(+w1, h1, -d1), EulerAngle3D::Degrees(0, 90, 0)));
	Objects.Insert(PolyHedraObject(truss_cube, Point3D(+w1, h2, -d1)));

	Objects.Insert(PolyHedraObject(truss,      Point3D(-w0, h2, -d1), EulerAngle3D::Degrees(0, 0, 90)));
	Objects.Insert(PolyHedraObject(truss,      Point3D(  0, h2, -d1), EulerAngle3D::Degrees(0, 0, 90)));
	Objects.Insert(PolyHedraObject(truss,      Point3D(+w0, h2, -d1), EulerAngle3D::Degrees(0, 0, 90)));

	Objects.Insert(PolyHedraObject(truss,      Point3D(-w1, h2, -d0)));
	Objects.Insert(PolyHedraObject(truss,      Point3D(+w1, h2, -d0)));
	Objects.Insert(PolyHedraObject(truss,      Point3D(-w1, h2, +d0)));
	Objects.Insert(PolyHedraObject(truss,      Point3D(+w1, h2, +d0)));

	Objects.Insert(PolyHedraObject(truss,      Point3D(-w1, h0, +d1), EulerAngle3D::Degrees(0, 90, 0)));
	Objects.Insert(PolyHedraObject(truss,      Point3D(-w1, h1, +d1), EulerAngle3D::Degrees(0, 90, 0)));
	Objects.Insert(PolyHedraObject(truss_cube, Point3D(-w1, h2, +d1)));

	Objects.Insert(PolyHedraObject(truss,      Point3D(+w1, h0, +d1), EulerAngle3D::Degrees(0, 90, 0)));
	Objects.Insert(PolyHedraObject(truss,      Point3D(+w1, h1, +d1), EulerAngle3D::Degrees(0, 90, 0)));
	Objects.Insert(PolyHedraObject(truss_cube, Point3D(+w1, h2, +d1)));

	Objects.Insert(PolyHedraObject(truss,      Point3D(-w0, h2, +d1), EulerAngle3D::Degrees(0, 0, 90)));
	Objects.Insert(PolyHedraObject(truss,      Point3D(  0, h2, +d1), EulerAngle3D::Degrees(0, 0, 90)));
	Objects.Insert(PolyHedraObject(truss,      Point3D(+w0, h2, +d1), EulerAngle3D::Degrees(0, 0, 90)));

	for (int y = 0; y < 5; y++)
	{
		for (int x = -5; x <= +5; x++)
		{
			Objects.Insert(PolyHedraObject(chair, Trans3D(Point3D(x * +5.0f, (y * 2.0f), (y * -7.5f) -50), EulerAngle3D())));
		}
	}

	for (int i = 0; i < 10; i++)
	{
		Objects.Insert(PolyHedraObject(chair, Trans3D(Point3D(-50, i, -40), EulerAngle3D::Degrees(0, 0, 90))));
	}
	for (int i = 0; i < 3; i++)
	{
		Objects.Insert(PolyHedraObject(chair, Trans3D(Point3D(-50, i, -45), EulerAngle3D::Degrees(0, 0, 90))));
	}
}



void Make() override { }

void Init() override
{
	window.DefaultColor = ColorF4(0.25f, 0.0f, 0.0f);
	view.Depth.Color = window.DefaultColor;
	view.Trans = Trans3D(Point3D(0, 10, -65), EulerAngle3D());

	std::cout << "Init 0\n";

	LightsInit();

	RandomCubes();
	Fancify();
	FancyLights();

	InitExternal();
	GraphicsCreate();
	InitInternal();

	std::cout << "Init 1\n";
}
void Free() override
{
	std::cout << "Free 0\n";

	GraphicsDelete();

	LightsFree();

	std::cout << "Free 1\n";
}



void Frame(double timeDelta)
{
	static float frameSum = 0;
	frameSum += timeDelta;

	FrameTime frame_time(60);
	frame_time.Update(timeDelta);
	UpdateView(frame_time);

	LightShader.Bind();
	LightShader.View.Put(view.Trans.ToMatrixReverse());
	LightShader.FOV.Put(view.FOV);
	//Light_Spot.Pos = ViewTrans.Pos;
	//Light_Spot.Dir = ViewTrans.Rot.rotate(Point3D(0, 0, 1));

	{
		PolyHedraObject obj(5);
		Point3D center(0, 30, 0);
		Angle a = Angle::Radians(frameSum);

		Point3D rel = Point3D(a.Sin() * 10, (a * 2).Sin(), a.Cos() * 10);
		EulerAngle3D rot;

		obj.Trans().Position = pos + center;
		obj.Trans().Rotation = rot
	}

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

	LightShader.Light_Spot_Count.Put(Light_Spot_Count);

	//Objects[0].Trans().Position = Point3D(0, 10, 0);
	//Objects[0].Trans().Rotation.X1 += Angle::Radians(0.01f);
	//Objects[0].Trans().Rotation.CalcMatrix();



	PolyHedraManager.ClearInstances();
	PolyHedraManager.Update();
	{
		PolyHedraManager.ShaderFullDefault.Bind();
		PolyHedraManager.ShaderFullDefault.View.Put(view.Trans.ToMatrixReverse());
		PolyHedraManager.ShaderFullDefault.FOV.Put(view.FOV);
		PolyHedraManager.Draw();
	}
}



void Resize(const DisplaySize & WindowSize)
{
	LightShader.Bind();
	LightShader.DisplaySize.Put(WindowSize);

	//PolyHedraFullShader.Bind();
	//PolyHedraFullShader.DisplaySize.Put(WindowSize);

	PolyHedraManager.ShaderFullDefault.Bind();
	PolyHedraManager.ShaderFullDefault.DisplaySize.Put(WindowSize);
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
