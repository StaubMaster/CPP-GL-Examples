
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



struct MainContext : public MainContext3D
{
struct PolyHedraTransBuffer
{
	::PolyHedra *				PolyHedra;
	::PolyHedraFull::Buffer		Buffer;

	~PolyHedraTransBuffer()
	{ }
	PolyHedraTransBuffer()
		: PolyHedra(nullptr)
		, Buffer(GL::DrawMode::Triangles)
	{ }
	PolyHedraTransBuffer(::PolyHedra * polyhedra)
		: PolyHedra(polyhedra)
		, Buffer(GL::DrawMode::Triangles)
	{ }

	void GraphicsCreate()
	{
		Buffer.Create();
	}
	void GraphicsDelete()
	{
		Buffer.Delete();
	}

	void InitExternal()
	{
		Buffer.Main.Position.Change(0);
		Buffer.Main.Normal.Change(1);
		Buffer.Main.Texture.Change(2);
		Buffer.Inst.Data.Pos.Change(3);
		Buffer.Inst.Data.Rot.Change(4, 5, 6);
	}
	void InitInternal()
	{
		Buffer.Main.ChangeAttributeBinding();
		Buffer.Inst.ChangeAttributeBinding();
	}

	void ChangeMain()
	{
		if (PolyHedra == nullptr) { return; }

		Container::Pointer<PolyHedra_Main::Data> data0 = PolyHedra -> ToMainData();
		Container::Array<PolyHedraFull::Main::Data> data1(data0.Count());
		for (unsigned int i = 0; i < data1.Count(); i++)
		{
			data1[i].Position = data0[i].Position;
			data1[i].Normal = data0[i].Normal;
			data1[i].Texture = data0[i].Texture;
		}
		Buffer.Main.Change(data1);
		data0.Clear();
	}
};
struct PolyHedraTransObject
{
	::PolyHedra *	PolyHedra;
	Trans3D			Data;

	~PolyHedraTransObject()
	{ }
	PolyHedraTransObject()
		: PolyHedra(nullptr)
		, Data()
	{ }
	PolyHedraTransObject(::PolyHedra * polyhedra, Trans3D data)
		: PolyHedra(polyhedra)
		, Data(data)
	{ }
};

PolyHedraFull::Shader					PolyHedraFullShader;
Container::Binary<PolyHedraTransBuffer>	PolyHedraBuffers;
Container::Binary<PolyHedraTransObject>	PolyHedraTransObjects;



~MainContext()
{ }
MainContext()
	: MainContext3D()
	, PolyHedraFullShader()
	, PolyHedraBuffers()
	, PolyHedraTransObjects()
{ }



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

PolyHedra_Simple3D::ManagerMulti PolyHedra_3D_Manager;

Container::Binary<EntryContainer::Entry<Simple3D::Data>> Entrys;

PolyHedra * PH;
Container::Binary<PolyHedra *> FancyPolyHedras;



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
		PolyHedra_3D_Manager.DefaultShaderToUse = &LightShader;
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
		//Entrys.Insert(PH0_Instances -> Alloc(i_len));
		Entrys.Insert(PolyHedra_3D_Manager.Place(PH, i_len));
		//Entrys.Insert(EntryContainer::Entry<Simple3D::Data>(PH0_Instances -> Instances, i_len));
		//std::cout << "[" << j << "]" << (*Entrys[j]).Offset << "|" << (*Entrys[j]).Length << "\n";
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
		//rot.CalcFore();
		for (int i = 0; i < i_len; i++)
		{
			(Entrys[j])[i].Trans.Pos = center + Point3D(
				(std::rand() & Range_Size1) - Range_SizeH,
				(std::rand() & Range_Size1) - Range_SizeH,
				(std::rand() & Range_Size1) - Range_SizeH
			);
			(Entrys[j])[i].Trans.Rot = rot;
		}
	}

	/*for (int j = 0; j < j_len; j++)
	{
		std::cout << "[" << j << "]" << (*Entrys[j]).Offset << "|" << (*Entrys[j]).Length << "\n";
	}*/

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

//	unsigned int idx = FancyPolyHedras.Count();
	FancyPolyHedras.Insert(polyhedra); // removing this causes it to stop drawing

	unsigned int idx = PolyHedraBuffers.Count();
	PolyHedraBuffers.Insert(PolyHedraTransBuffer(polyhedra));

	return idx;
}
void FancyInsert(unsigned int ph_idx, Point3D pos, Angle3D rot)
{
//	unsigned int idx = Entrys.Count();
//	//Entrys.Insert(EntryContainer::Entry<Simple3D::Data>(FancyPolyHedraInstances[ph_idx] -> Instances, 1));
//	Entrys.Insert(PolyHedra_3D_Manager.Place(FancyPolyHedras[ph_idx], 1));
//	(*(Entrys[idx])).Trans = Trans3D(pos, rot);
//	//(*(Entrys[idx])).Trans.Rot.CalcBack();

	//PolyHedraTransObjects.Insert(PolyHedraTransObject(FancyPolyHedras[ph_idx], Trans3D(pos, rot)));
	PolyHedraTransObjects.Insert(PolyHedraTransObject(PolyHedraBuffers[ph_idx].PolyHedra, Trans3D(pos, rot)));
}
void Fancify()
{
	unsigned int idx_stage =				FancyInsert("Light/Stage.polyhedra.ymt");
	unsigned int idx_stage_light =			FancyInsert("Light/Stage_Light.polyhedra.ymt");
	unsigned int idx_stage_light_holder =	FancyInsert("Light/Stage_Light_Holder.polyhedra.ymt");
	unsigned int idx_truss =				FancyInsert("Light/Truss_Square40cm_Len200cm.polyhedra.ymt");
	unsigned int idx_truss_cube =			FancyInsert("Light/Truss_Cube40cm.polyhedra.ymt");
	unsigned int idx_chair =				FancyInsert("Light/Chair.polyhedra.ymt");

	for (unsigned int i = 0; i < FancyPolyHedras.Count(); i++)
	{
		PolyHedra_3D_Manager.Insert(FancyPolyHedras[i]); // removing this causes it to stop drawing
		//FancyPolyHedraInstances.Insert(new PolyHedra_3D_Instances(FancyPolyHedras[i]));
	}

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

	/*for (unsigned int i = 0; i < Light_Spot_Limit; i++)
	{
		Light_Spot_Entry_Array[i].EntryLight = PolyHedra_3D_Manager.Place(FancyPolyHedras[idx_stage_light], 1);
		Light_Spot_Entry_Array[i].EntryHolder = PolyHedra_3D_Manager.Place(FancyPolyHedras[idx_stage_light_holder], 1);
		//Light_Spot_Entry_Array[i].EntryLight.Allocate(FancyPolyHedraInstances[idx_stage_light] -> Instances, 1);
		//Light_Spot_Entry_Array[i].EntryHolder.Allocate(FancyPolyHedraInstances[idx_stage_light_holder] -> Instances, 1);
	}*/
	(void)idx_stage_light;
	(void)idx_stage_light_holder;

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
	window.DefaultColor = ColorF4(0.0f, 0.0f, 0.0f);
	view.Depth.Color = window.DefaultColor;
	view.Trans = Trans3D(Point3D(0, 10, -65), Angle3D());

	std::cout << "Init 0\n";

	LightsInit();

	InitExternal();
	GraphicsCreate();
	InitInternal();

	/*{
		PH = PolyHedra::Generate::HexaHedron();
		PolyHedra_3D_Manager.Insert(PH);
		PolyHedraBuffers.Insert(PH);
		AddInstances();
	}*/

	Fancify();

	/*for (unsigned int i = 0; i < PolyHedra_3D_Manager.MultiplePolyHedra.Count(); i++)
	{
		PolyHedra_3D_Manager.MultiplePolyHedra[i] -> _Buffer.Main.Position.Change(0);
		PolyHedra_3D_Manager.MultiplePolyHedra[i] -> _Buffer.Main.Normal.Change(1);
		PolyHedra_3D_Manager.MultiplePolyHedra[i] -> _Buffer.Main.Texture.Change(2);
		PolyHedra_3D_Manager.MultiplePolyHedra[i] -> _Buffer.Main.ChangeAttributeBinding();

		PolyHedra_3D_Manager.MultiplePolyHedra[i] -> _Buffer.Inst.Trans.Pos.Change(3);
		PolyHedra_3D_Manager.MultiplePolyHedra[i] -> _Buffer.Inst.Trans.Rot.Change(4, 5, 6);
		PolyHedra_3D_Manager.MultiplePolyHedra[i] -> _Buffer.Inst.ChangeAttributeBinding();

		PolyHedra * _PolyHedra = PolyHedra_3D_Manager.MultiplePolyHedra[i] -> _PolyHedra;
		PolyHedra_Simple3D::BufferArray & _Buffer = PolyHedra_3D_Manager.MultiplePolyHedra[i] -> _Buffer;
		{
			_Buffer.Bind();
			Container::Pointer<PolyHedra_Main::Data> data = _PolyHedra -> ToMainData();
			_Buffer.Main.Change(data);
			data.Clear();
		}
	}*/

	/*for (unsigned int i = 0; i < PolyHedra_3D_Manager.MultiplePolyHedra.Count(); i++)
	{
		PolyHedraBuffers.Insert(PolyHedraTransBuffer());
	}*/

	for (unsigned int i = 0; i < PolyHedraBuffers.Count(); i++)
	{
		PolyHedraBuffers[i].InitExternal();
		PolyHedraBuffers[i].GraphicsCreate();
		PolyHedraBuffers[i].InitInternal();
		PolyHedraBuffers[i].ChangeMain();
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
	for (unsigned int i = 0; i < Entrys.Count(); i++)
	{
		Entrys[i].Dispose();
	}

	PolyHedra_3D_Manager.Dispose();

	for (unsigned int i = 0; i < PolyHedraBuffers.Count(); i++)
	{
		PolyHedraBuffers[i].Buffer.Delete();
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

//	(Entrys[0])[0].Trans.Pos = Point3D(0, 10, 0);
//	(Entrys[0])[0].Trans.Rot.X += Angle::Radians(0.01f);
//	(Entrys[0])[0].Trans.Rot.CalcMatrix();

	//PolyHedra_3D_Manager.Draw();

	/*for (unsigned int i = 0; i < PolyHedra_3D_Manager.MultiplePolyHedra.Count(); i++)
	{
		Container::Binary<Trans3D> data;
		for (unsigned int j = 0; j < PolyHedra_3D_Manager.MultiplePolyHedra[i] -> _Instances.Count(); j++)
		{
			data.Insert(PolyHedra_3D_Manager.MultiplePolyHedra[i] -> _Instances[j].Trans);
		}
		PolyHedraBuffers[i].Buffer.Inst.Change(data);
	}*/

	for (unsigned int i = 0; i < PolyHedraBuffers.Count(); i++)
	{
		PolyHedra * polyhedra = PolyHedraBuffers[i].PolyHedra;
		Container::Binary<Trans3D> data;
		for (unsigned int j = 0; j < PolyHedraTransObjects.Count(); j++)
		{
			if (PolyHedraTransObjects[j].PolyHedra == polyhedra)
			{
				data.Insert(PolyHedraTransObjects[j].Data);
			}
		}
		PolyHedraBuffers[i].Buffer.Inst.Change(data);
	}

	{
		PolyHedraFullShader.Bind();
		PolyHedraFullShader.View.Put(view.Trans);
		PolyHedraFullShader.FOV.Put(view.FOV);
		for (unsigned int i = 0; i < PolyHedraBuffers.Count(); i++)
		{
			PolyHedraBuffers[i].Buffer.Draw();
		}
	}
}



void Resize(const DisplaySize & WindowSize)
{
	LightShader.Bind();
	LightShader.DisplaySize.Put(WindowSize);

	PolyHedraFullShader.Bind();
	PolyHedraFullShader.DisplaySize.Put(WindowSize);

	//Multi_WindowSize -> ChangeData(WindowSize);
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
