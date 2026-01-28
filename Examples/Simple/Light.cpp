
#include <iostream>
#include "OpenGL.hpp"
#include "Debug.hpp"

#include "DataInclude.hpp"
#include "DataShow.hpp"

#include "Graphics/Shader/Code.hpp"

#include "Graphics/UniformsInclude.hpp"
#include "Graphics/MultiformsInclude.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Generate.hpp"
#include "PolyHedra/Simple3D/ManagerMulti.hpp"

#include "Miscellaneous/Container/Binary.hpp"
#include "Miscellaneous/EntryContainer/Binary.hpp"

#include "Window.hpp"
#include "Function/Object.hpp"
#include "ValueType/View.hpp"

#include "FileInfo.hpp"
#include "DirectoryInfo.hpp"
#include "Image.hpp"



struct MainContext
{
DirectoryInfo ImageDir;
DirectoryInfo ShaderDir;
DirectoryInfo PolyHedraDir;

Window window;
View	view;

MainContext() :
	ImageDir("../../media/Images"),
	ShaderDir("../../media/Shaders"),
	PolyHedraDir("../../media/YMT/Light/"),
	window(),
	view()
{ }
~MainContext()
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
		angle.CalcBack();

		if (Light != NULL)
		{
			Light -> Pos = Position + angle.rotate(Point3D(0, 0, 3));
			Light -> Dir = (Target - Position).normalize();
		}

		if (EntryLight.Is())
		{
			(*EntryLight).Trans.Pos = Position;
			(*EntryLight).Trans.Rot = angle;
			(*EntryLight).Trans.Rot.CalcBack();
		}

		if (EntryHolder.Is())
		{
			(*EntryHolder).Trans.Pos = Position;
			(*EntryHolder).Trans.Rot = Angle3D(angle.X, 0, 0);
			(*EntryHolder).Trans.Rot.CalcBack();
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
		Light_Ambient(Uniform::NameShader("Ambient", *this)),
		Light_Solar(Uniform::NameShader("Solar", *this)),
		Light_Spot_Array(Light_Spot_Limit, Uniform::NameShader("SpotArr", *this)),
		Light_Spot_Count(Uniform::NameShader("SpotCount", *this))
	{ }
	/*CLightShader(const DirectoryInfo & dir)
		: PolyHedra_Simple3D::Shader(dir),
		Light_Ambient(Uniform::NameShader("Ambient", *this)),
		Light_Solar(Uniform::NameShader("Solar", *this)),
		Light_Spot_Array(Light_Spot_Limit, Uniform::NameShader("SpotArr", *this)),
		Light_Spot_Count(Uniform::NameShader("SpotCount", *this))
	{ }*/
	~CLightShader()
	{ }
};

CLightShader LightShader;

PolyHedra_Simple3D::ManagerMulti PolyHedra_3D_Manager;

Container::Binary<EntryContainer::Entry<Simple3D::Data>> Entrys;

PolyHedra * PH;
Container::Binary<PolyHedra *> FancyPolyHedras;



void InitShaders()
{
	{
		Container::Fixed<Shader::Code> code(2);
		code.Insert(Shader::Code(ShaderDir.File("PH/Simple3D.vert")));
		code.Insert(Shader::Code(ShaderDir.File("PH/UniLight4.frag")));
		//code.Insert(Shader::Code(ShaderDir.File("PH_Full.frag")));
		LightShader.Change(code);
		code.Dispose();
	}
	LightShader.Create();
	LightShader.Bind();
	LightShader.Depth.Put(view.Depth);
	float fov_rad = Angle3D::DegreeToRadian(view.FOV);
	LightShader.FOV.PutData(&fov_rad);
	PolyHedra_3D_Manager.DefaultShaderToUse = &LightShader;
}
void FreeShaders()
{
	LightShader.Delete();
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
			(std::rand() & Range_Size1) - Range_SizeH,
			(std::rand() & Range_Size1) - Range_SizeH,
			(std::rand() & Range_Size1) - Range_SizeH
		);
		rot.CalcFore();
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


void FancyInsert(unsigned int ph_idx, Point3D pos, Angle3D rot)
{
	unsigned int idx = Entrys.Count();
	//Entrys.Insert(EntryContainer::Entry<Simple3D::Data>(FancyPolyHedraInstances[ph_idx] -> Instances, 1));
	Entrys.Insert(PolyHedra_3D_Manager.Place(FancyPolyHedras[ph_idx], 1));
	(*(Entrys[idx])).Trans = Trans3D(pos, rot);
	(*(Entrys[idx])).Trans.Rot.CalcBack();
}
void Fancify()
{
	unsigned int idx_stage =				FancyPolyHedras.Count(); FancyPolyHedras.Insert(PolyHedra::Load(PolyHedraDir.File("Stage.polyhedra.ymt")));
	unsigned int idx_stage_light =			FancyPolyHedras.Count(); FancyPolyHedras.Insert(PolyHedra::Load(PolyHedraDir.File("Stage_Light.polyhedra.ymt")));
	unsigned int idx_stage_light_holder =	FancyPolyHedras.Count(); FancyPolyHedras.Insert(PolyHedra::Load(PolyHedraDir.File("Stage_Light_Holder.polyhedra.ymt")));
	unsigned int idx_truss =				FancyPolyHedras.Count(); FancyPolyHedras.Insert(PolyHedra::Load(PolyHedraDir.File("Truss_Square40cm_Len200cm.polyhedra.ymt")));
	unsigned int idx_truss_cube =			FancyPolyHedras.Count(); FancyPolyHedras.Insert(PolyHedra::Load(PolyHedraDir.File("Truss_Cube40cm.polyhedra.ymt")));
	unsigned int idx_chair =				FancyPolyHedras.Count(); FancyPolyHedras.Insert(PolyHedra::Load(PolyHedraDir.File("Chair.polyhedra.ymt")));

	for (unsigned int i = 0; i < FancyPolyHedras.Count(); i++)
	{
		PolyHedra_3D_Manager.Insert(FancyPolyHedras[i]);
		//FancyPolyHedraInstances.Insert(new PolyHedra_3D_Instances(FancyPolyHedras[i]));
	}

	FancyInsert(idx_stage, Point3D(0, 0, 0), Angle3D(0, 0, 0));

	FancyInsert(idx_truss, Point3D(-32, 10, -22), Angle3D(0, Angle3D::DegreeToRadian(90), 0));
	FancyInsert(idx_truss, Point3D(-32, 30, -22), Angle3D(0, Angle3D::DegreeToRadian(90), 0));
	FancyInsert(idx_truss_cube, Point3D(-32, 42, -22), Angle3D(0, 0, 0));

	FancyInsert(idx_truss, Point3D(+32, 10, -22), Angle3D(0, Angle3D::DegreeToRadian(90), 0));
	FancyInsert(idx_truss, Point3D(+32, 30, -22), Angle3D(0, Angle3D::DegreeToRadian(90), 0));
	FancyInsert(idx_truss_cube, Point3D(+32, 42, -22), Angle3D(0, 0, 0));

	FancyInsert(idx_truss, Point3D(-20, 42, -22), Angle3D(Angle3D::DegreeToRadian(90), 0, 0));
	FancyInsert(idx_truss, Point3D(  0, 42, -22), Angle3D(Angle3D::DegreeToRadian(90), 0, 0));
	FancyInsert(idx_truss, Point3D(+20, 42, -22), Angle3D(Angle3D::DegreeToRadian(90), 0, 0));

	FancyInsert(idx_truss, Point3D(-32, 42, -10), Angle3D(0, 0, 0));
	FancyInsert(idx_truss, Point3D(+32, 42, -10), Angle3D(0, 0, 0));
	FancyInsert(idx_truss, Point3D(-32, 42, +10), Angle3D(0, 0, 0));
	FancyInsert(idx_truss, Point3D(+32, 42, +10), Angle3D(0, 0, 0));

	FancyInsert(idx_truss, Point3D(-32, 10, +22), Angle3D(0, Angle3D::DegreeToRadian(90), 0));
	FancyInsert(idx_truss, Point3D(-32, 30, +22), Angle3D(0, Angle3D::DegreeToRadian(90), 0));
	FancyInsert(idx_truss_cube, Point3D(-32, 42, +22), Angle3D(0, 0, 0));

	FancyInsert(idx_truss, Point3D(+32, 10, +22), Angle3D(0, Angle3D::DegreeToRadian(90), 0));
	FancyInsert(idx_truss, Point3D(+32, 30, +22), Angle3D(0, Angle3D::DegreeToRadian(90), 0));
	FancyInsert(idx_truss_cube, Point3D(+32, 42, +22), Angle3D(0, 0, 0));

	FancyInsert(idx_truss, Point3D(-20, 42, +22), Angle3D(Angle3D::DegreeToRadian(90), 0, 0));
	FancyInsert(idx_truss, Point3D(  0, 42, +22), Angle3D(Angle3D::DegreeToRadian(90), 0, 0));
	FancyInsert(idx_truss, Point3D(+20, 42, +22), Angle3D(Angle3D::DegreeToRadian(90), 0, 0));

	for (unsigned int i = 0; i < Light_Spot_Limit; i++)
	{
		Light_Spot_Entry_Array[i].EntryLight = PolyHedra_3D_Manager.Place(FancyPolyHedras[idx_stage_light], 1);
		Light_Spot_Entry_Array[i].EntryHolder = PolyHedra_3D_Manager.Place(FancyPolyHedras[idx_stage_light_holder], 1);
		//Light_Spot_Entry_Array[i].EntryLight.Allocate(FancyPolyHedraInstances[idx_stage_light] -> Instances, 1);
		//Light_Spot_Entry_Array[i].EntryHolder.Allocate(FancyPolyHedraInstances[idx_stage_light_holder] -> Instances, 1);
	}

	for (int y = 0; y < 5; y++)
	{
		for (int x = -5; x <= +5; x++)
		{
			FancyInsert(idx_chair, Point3D(x * +5.0f, (y * 2.0f), (y * -7.5f) -50), Angle3D(0, 0, 0));
		}
	}

	for (int i = 0; i < 10; i++)
	{
		FancyInsert(idx_chair, Point3D(-50, i, -40), Angle3D(Angle3D::DegreeToRadian(90), 0, 0));
	}
	for (int i = 0; i < 3; i++)
	{
		FancyInsert(idx_chair, Point3D(-50, i, -45), Angle3D(Angle3D::DegreeToRadian(90), 0, 0));
	}
}

void Init()
{
	std::cout << "Init 0\n";

	InitShaders();

	{
		PH = PolyHedra::Generate::HexaHedron();
		PolyHedra_3D_Manager.Insert(PH);
	}

	AddInstances();
	Fancify();

	std::cout << "Init 1\n";
}
void Free()
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

	FreeShaders();

	std::cout << "Free 1\n";
}

void Update(double timeDelta)
{
	(void)timeDelta;
}
void Frame(double timeDelta)
{
	if (window.Keys[GLFW_KEY_TAB].IsPress()) { window.MouseManager.CursorModeToggle(); }
	if (window.MouseManager.CursorModeIsLocked())
	{
		Trans3D trans = window.MoveSpinFromKeysCursor();
		if (window.Keys[GLFW_KEY_LEFT_CONTROL].IsDown()) { trans.Pos *= 10; }
		trans.Pos *= 2;
		trans.Rot.X *= view.FOV * 0.005f;
		trans.Rot.Y *= view.FOV * 0.005f;
		trans.Rot.Z *= view.FOV * 0.005f;
		view.TransformFlatX(trans, timeDelta);
	}

	LightShader.Bind();
	LightShader.View.Put(view.Trans);
	//Light_Spot.Pos = ViewTrans.Pos;
	//Light_Spot.Dir = ViewTrans.Rot.rotate(Point3D(0, 0, 1));

	if (window.Keys[GLFW_KEY_1].IsPress())
	{
		if (Light_Ambient.Intensity == 0.0f)
		{ Light_Ambient.Intensity = Light_Ambient_Intensity; }
		else
		{ Light_Ambient.Intensity = 0.0f; }
	}
	if (window.Keys[GLFW_KEY_2].IsPress())
	{
		if (Light_Solar.Base.Intensity == 0.0f)
		{ Light_Solar.Base.Intensity = Light_Solar_Intensity; }
		else
		{ Light_Solar.Base.Intensity = 0.0f; }
	}
	if (window.Keys[GLFW_KEY_3].IsPress()) { Light_Spot_Entry_Array[0].Toggle(); }
	if (window.Keys[GLFW_KEY_4].IsPress()) { Light_Spot_Entry_Array[1].Toggle(); }
	if (window.Keys[GLFW_KEY_5].IsPress()) { Light_Spot_Entry_Array[2].Toggle(); }

	for (unsigned int i = 0; i < Light_Spot_Limit; i++)
	{
		Light_Spot_Entry_Array[i].Update();
	}

	LightShader.Bind();
	LightShader.Light_Ambient.Put(Light_Ambient);
	LightShader.Light_Solar.Put(Light_Solar);
	LightShader.Light_Solar.Put(Light_Solar);
	for (unsigned int i = 0; i < LightShader.Light_Spot_Array.Limit; i++)
	{
		if (Light_Spot_Entry_Array[i].Light != NULL)
		{
			LightShader.Light_Spot_Array[i].Put(*(Light_Spot_Entry_Array[i].Light));
		}
	}
	LightShader.Light_Spot_Count.PutData(&Light_Spot_Count);

	(Entrys[0])[0].Trans.Pos = Point3D(0, 10, 0);
	(Entrys[0])[0].Trans.Rot.X += 0.01f;
	(Entrys[0])[0].Trans.Rot.CalcBack();

	PolyHedra_3D_Manager.Draw();
	/*PH0_Instances -> Update().Draw();
	for (unsigned int i = 0; i < FancyPolyHedraInstances.Count(); i++)
	{
		FancyPolyHedraInstances[i] -> Update().Draw();
	}*/
}

void Resize(const WindowBufferSize2D & WindowSize)
{
	LightShader.Bind();
	LightShader.WindowSize.Put(WindowSize);
	//Multi_WindowSize -> ChangeData(WindowSize);
}

int Main()
{
	window.Create();
	window.InitCallBack.Change(ObjectFunction<MainContext, void>::New(this, &MainContext::Init));
	window.FreeCallBack.Change(ObjectFunction<MainContext, void>::New(this, &MainContext::Free));
	window.FrameCallBack.Change(ObjectFunction<MainContext, void, double>::New(this, &MainContext::Frame));
	window.ResizeCallBack.Change(ObjectFunction<MainContext, void, const WindowBufferSize2D &>::New(this, &MainContext::Resize));

	window.DefaultColor = ColorF4(0.0f, 0.0f, 0.0f);
	view.Depth.Color = window.DefaultColor;
	view.Trans = Trans3D(Point3D(0, 10, -65), Angle3D(0, 0, 0));

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



	std::cout << "++++ Run\n";
	window.Run();
	std::cout << "---- Run\n";



	delete[] Light_Spot_Entry_Array;
	delete[] Light_Spot_Array;
	window.Delete();

	return 0;
}
};



int main(int argc, char * argv[])
{
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
