
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



struct MainContext : public MainContext3D
{



PolyHedraFull::Shader						PolyHedraFullShader;
Container::Binary<PolyHedraInstanceManager>	PolyHedraInstanceManagers;
Container::Binary<PolyHedraObjectData>		PolyHedraTransObjects;



~MainContext()
{ }
MainContext()
	: MainContext3D()
	, PolyHedraFullShader()
	, PolyHedraInstanceManagers()
	, PolyHedraTransObjects()
{ }



struct SpotLightEntry
{
	Point3D		Position;
	Point3D		Target;
	LightSpot *	Light;
	PolyHedraObjectData		EntryLight;
	PolyHedraObjectData		EntryHolder;

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

		EntryLight.Data.Pos = Position;
		EntryLight.Data.Rot = angle;

		EntryHolder.Data.Pos = Position;
		EntryHolder.Data.Rot = Angle3D(angle.X, Angle(), Angle());
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



class CLightShader : public PolyHedra_Simple3D::Shader
{
	public:
	Uniform::LightBase								Light_Ambient;
	Uniform::LightSolar								Light_Solar;
	Uniform::GArray<Uniform::LightSpot, LightSpot>	Light_Spot_Array;
	Uniform::UInt									Light_Spot_Count;

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



void GraphicsCreate()
{
	LightShader.Create();
	PolyHedraFullShader.Create();
}
void GraphicsDelete()
{
	LightShader.Delete();
	PolyHedraFullShader.Delete();
}

void InitExternal()
{
	{
		Container::Array<Shader::Code> code({
			Shader::Code(ShaderDir.File("PH/Simple3D.vert")),
			Shader::Code(ShaderDir.File("PH/UniLight4.frag")),
		});
		LightShader.Change(code);
	}
	{
		Container::Array<Shader::Code> code({
			Shader::Code(ShaderDir.File("PH/Simple3D.vert")),
			Shader::Code(ShaderDir.File("PH/Full.frag")),
		});
		PolyHedraFullShader.Change(code);
	}
}
void InitInternal()
{
	{
		LightShader.Bind();
		LightShader.Depth.Put(view.Depth);
		LightShader.FOV.Put(view.FOV);
	}
	{
		PolyHedraFullShader.Bind();
		PolyHedraFullShader.Depth.Put(view.Depth);
		PolyHedraFullShader.FOV.Put(view.FOV);
	}
}



void AddInstances()
{
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
		Angle3D rot(
			Angle::Radians((std::rand() & Range_Size1) - Range_SizeH),
			Angle::Radians((std::rand() & Range_Size1) - Range_SizeH),
			Angle::Radians((std::rand() & Range_Size1) - Range_SizeH)
		);

		for (int i = 0; i < i_len; i++)
		{
			PolyHedraTransObjects.Insert(PolyHedraObjectData(PolyHedraInstanceManagers[0].PolyHedra, Trans3D(
				center + Point3D(
					(std::rand() & Range_Size1) - Range_SizeH,
					(std::rand() & Range_Size1) - Range_SizeH,
					(std::rand() & Range_Size1) - Range_SizeH
				), rot
			)));
		}
	}

	{
		//std::cout << "Instance Count: " << (PH0_Instances -> Instances.Count()) << "\n";
		//int MemSize = (PH0_Instances -> Instances.Length) * sizeof(Simple3D_InstData);
		//std::cout << (MemSize / (1)) << " Bytes\n";
		//std::cout << (MemSize / (1 * 1000)) << "k Bytes\n";
		//std::cout << (MemSize / (1 * 1000 * 1000)) << "M Bytes\n";
	}
}

unsigned int FancyInsert(const char * polyhedra_file_path)
{
	PolyHedra * polyhedra = PolyHedra::Load(PolyHedraDir.File(polyhedra_file_path));
	
	unsigned int idx = PolyHedraInstanceManagers.Count();
	PolyHedraInstanceManagers.Insert(PolyHedraInstanceManager(polyhedra));

	return idx;
}
void FancyInsert(unsigned int ph_idx, Point3D pos, Angle3D rot)
{
	PolyHedraTransObjects.Insert(PolyHedraObjectData(PolyHedraInstanceManagers[ph_idx].PolyHedra, Trans3D(pos, rot)));
}
void Fancify()
{
	unsigned int idx_stage =				FancyInsert("Light/Stage.polyhedra.ymt");
	unsigned int idx_stage_light =			FancyInsert("Light/Stage_Light.polyhedra.ymt");
	unsigned int idx_stage_light_holder =	FancyInsert("Light/Stage_Light_Holder.polyhedra.ymt");
	unsigned int idx_truss =				FancyInsert("Light/Truss_Square40cm_Len200cm.polyhedra.ymt");
	unsigned int idx_truss_cube =			FancyInsert("Light/Truss_Cube40cm.polyhedra.ymt");
	unsigned int idx_chair =				FancyInsert("Light/Chair.polyhedra.ymt");

	FancyInsert(idx_stage, Point3D(0, 0, 0), Angle3D());

	FancyInsert(idx_truss, Point3D(-32, 10, -22), Angle3D(Angle(), Angle::Degrees(90), Angle()));
	FancyInsert(idx_truss, Point3D(-32, 30, -22), Angle3D(Angle(), Angle::Degrees(90), Angle()));
	FancyInsert(idx_truss_cube, Point3D(-32, 42, -22), Angle3D());

	FancyInsert(idx_truss, Point3D(+32, 10, -22), Angle3D(Angle(), Angle::Degrees(90), Angle()));
	FancyInsert(idx_truss, Point3D(+32, 30, -22), Angle3D(Angle(), Angle::Degrees(90), Angle()));
	FancyInsert(idx_truss_cube, Point3D(+32, 42 + 5, -22), Angle3D());

	FancyInsert(idx_truss, Point3D(-20, 42, -22), Angle3D(Angle::Degrees(90), Angle(), Angle()));
	FancyInsert(idx_truss, Point3D(  0, 42, -22), Angle3D(Angle::Degrees(90), Angle(), Angle()));
	FancyInsert(idx_truss, Point3D(+20, 42, -22), Angle3D(Angle::Degrees(90), Angle(), Angle()));

	FancyInsert(idx_truss, Point3D(-32, 42, -10), Angle3D());
	FancyInsert(idx_truss, Point3D(+32, 42, -10), Angle3D());
	FancyInsert(idx_truss, Point3D(-32, 42, +10), Angle3D());
	FancyInsert(idx_truss, Point3D(+32, 42, +10), Angle3D());

	FancyInsert(idx_truss, Point3D(-32, 10, +22), Angle3D(Angle(), Angle::Degrees(90), Angle()));
	FancyInsert(idx_truss, Point3D(-32, 30, +22), Angle3D(Angle(), Angle::Degrees(90), Angle()));
	FancyInsert(idx_truss_cube, Point3D(-32, 42, +22), Angle3D());

	FancyInsert(idx_truss, Point3D(+32, 10, +22), Angle3D(Angle(), Angle::Degrees(90), Angle()));
	FancyInsert(idx_truss, Point3D(+32, 30, +22), Angle3D(Angle(), Angle::Degrees(90), Angle()));
	FancyInsert(idx_truss_cube, Point3D(+32, 42, +22), Angle3D());

	FancyInsert(idx_truss, Point3D(-20, 42, +22), Angle3D(Angle::Degrees(90), Angle(), Angle()));
	FancyInsert(idx_truss, Point3D(  0, 42, +22), Angle3D(Angle::Degrees(90), Angle(), Angle()));
	FancyInsert(idx_truss, Point3D(+20, 42, +22), Angle3D(Angle::Degrees(90), Angle(), Angle()));

	for (unsigned int i = 0; i < Light_Spot_Limit; i++)
	{
		Light_Spot_Entry_Array[i].EntryLight = PolyHedraObjectData(PolyHedraInstanceManagers[idx_stage_light].PolyHedra);
		Light_Spot_Entry_Array[i].EntryHolder = PolyHedraObjectData(PolyHedraInstanceManagers[idx_stage_light_holder].PolyHedra);
	}

	for (int y = 0; y < 5; y++)
	{
		for (int x = -5; x <= +5; x++)
		{
			FancyInsert(idx_chair, Point3D(x * +5.0f, (y * 2.0f), (y * -7.5f) -50), Angle3D());
		}
	}

	for (int i = 0; i < 10; i++)
	{
		FancyInsert(idx_chair, Point3D(-50, i, -40), Angle3D(Angle::Degrees(90), Angle(), Angle()));
	}
	for (int i = 0; i < 3; i++)
	{
		FancyInsert(idx_chair, Point3D(-50, i, -45), Angle3D(Angle::Degrees(90), Angle(), Angle()));
	}
}



void Make() override { }

void Init() override
{
	window.DefaultColor = ColorF4(0.75f, 0.0f, 0.0f);
	view.Depth.Color = window.DefaultColor;
	view.Trans = Trans3D(Point3D(0, 10, -65), Angle3D());

	std::cout << "Init 0\n";

	LightsInit();

	InitExternal();
	GraphicsCreate();
	InitInternal();

	{
		PolyHedra * PH = PolyHedra::Generate::HexaHedron();
		PolyHedraInstanceManagers.Insert(PolyHedraInstanceManager(PH));
		AddInstances();
	}

	Fancify();

	for (unsigned int i = 0; i < PolyHedraInstanceManagers.Count(); i++)
	{
		PolyHedraInstanceManagers[i].InitExternal();
		PolyHedraInstanceManagers[i].GraphicsCreate();
		PolyHedraInstanceManagers[i].InitInternal();
		PolyHedraInstanceManagers[i].UpdateBufferMain();
	}

	std::cout << "Init 1\n";
}
void Free() override
{
	std::cout << "Free 0\n";

	/*for (unsigned int i = 0; i < Light_Spot_Limit; i++)
	{
		Light_Spot_Entry_Array[i].EntryLight.Dispose();
		Light_Spot_Entry_Array[i].EntryHolder.Dispose();
	}*/

	for (unsigned int i = 0; i < PolyHedraInstanceManagers.Count(); i++)
	{
		delete PolyHedraInstanceManagers[i].PolyHedra;
		PolyHedraInstanceManagers[i].PolyHedra = nullptr;
		PolyHedraInstanceManagers[i].Buffer.Delete();
	}

	GraphicsDelete();

	LightsFree();

	std::cout << "Free 1\n";
}



void UpdateView(float timeDelta)
{
	if (window.KeyBoardManager[Keys::Tab].State == State::Press) { window.MouseManager.CursorModeToggle(); }
	if (window.MouseManager.CursorModeIsLocked())
	{
		Trans3D trans = window.MoveSpinFromKeysCursor();
		if (window.KeyBoardManager[Keys::LeftControl].State == State::Down) { trans.Pos *= 10; }
		trans.Pos *= 2;
		trans.Rot.X *= view.FOV * 0.05f;
		trans.Rot.Y *= view.FOV * 0.05f;
		trans.Rot.Z *= view.FOV * 0.05f;
		view.TransformFlatX(trans, timeDelta);
	}
}
void Frame(double timeDelta)
{
	UpdateView(timeDelta);

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

	LightShader.Light_Spot_Count.Put(Light_Spot_Count);

	PolyHedraTransObjects[0].Data.Pos = Point3D(0, 10, 0);
	PolyHedraTransObjects[0].Data.Rot.X += Angle::Radians(0.01f);
	PolyHedraTransObjects[0].Data.Rot.CalcMatrix();

	for (unsigned int i = 0; i < PolyHedraInstanceManagers.Count(); i++)
	{
		PolyHedraInstanceManagers[i].Clear();
		PolyHedraInstanceManagers[i].Place(PolyHedraTransObjects);
		for (unsigned int j = 0; j < Light_Spot_Limit; j++)
		{
			PolyHedraInstanceManagers[i].Place(Light_Spot_Entry_Array[j].EntryLight);
			PolyHedraInstanceManagers[i].Place(Light_Spot_Entry_Array[j].EntryHolder);
		}
		PolyHedraInstanceManagers[i].UpdateBufferInst();
	}

	{
		PolyHedraFullShader.Bind();
		PolyHedraFullShader.View.Put(view.Trans);
		PolyHedraFullShader.FOV.Put(view.FOV);
		for (unsigned int i = 0; i < PolyHedraInstanceManagers.Count(); i++)
		{
			PolyHedraInstanceManagers[i].Draw();
		}
	}
}



void Resize(const DisplaySize & WindowSize)
{
	LightShader.Bind();
	LightShader.DisplaySize.Put(WindowSize);

	PolyHedraFullShader.Bind();
	PolyHedraFullShader.DisplaySize.Put(WindowSize);
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
