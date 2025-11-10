
#include <iostream>
#include "OpenGL/openGL.h"

#include "DataStruct/Full/PolyHedra_3D/PolyHedra_3D_Instances.hpp"

#include "DataInclude.hpp"
#include "DataShow.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Graphics/Shader/Base.hpp"

#include "Graphics/UniformsInclude.hpp"
#include "Graphics/MultiformsInclude.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Skin/SkinBase.hpp"
#include "PolyHedra/Skin/Skin2DA.hpp"

#include "Graphics/Texture/Base.hpp"
#include "Graphics/Texture/2DArray.hpp"
#include "Graphics/Texture/Generate.hpp"

#include "Window.hpp"

#include "DirectoryContext.hpp"
#include "FileContext.hpp"
#include "Format/Image.hpp"

struct SpotLightEntry
{
	Point3D		Position;
	Point3D		Target;
	LightSpot	* Light;
	EntryContainerDynamic<Simple3D_InstData>::Entry *	EntryLight;
	EntryContainerDynamic<Simple3D_InstData>::Entry *	EntryHolder;

	SpotLightEntry() :
		Position(),
		Target(),
		Light(NULL),
		EntryLight(NULL),
		EntryHolder(NULL)
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

		if (EntryLight != NULL)
		{
			(*EntryLight)[0].Trans.Pos = Position;
			(*EntryLight)[0].Trans.Rot = angle;
			(*EntryLight)[0].Trans.Rot.CalcBack();
		}

		if (EntryHolder != NULL)
		{
			(*EntryHolder)[0].Trans.Pos = Position;
			(*EntryHolder)[0].Trans.Rot = Angle3D(angle.X, 0, 0);
			(*EntryHolder)[0].Trans.Rot.CalcBack();
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

DirectoryContext ImageDir("./media/Images");
DirectoryContext ShaderDir("./media/Shaders");

Window * win;

Trans3D	ViewTrans;
Depth	ViewDepth;

ContainerDynamic<YMT::PolyHedra*> FancyPolyHedras;
ContainerDynamic<PolyHedra_3D_Instances*> FancyPolyHedraInstances;

YMT::PolyHedra * Poly0;
PolyHedra_3D_Instances * PH0_Instances;

ContainerDynamic<EntryContainerDynamic<Simple3D_InstData>::Entry*> Entrys;

Shader::Base * PH_Shader;

Uniform::SizeRatio2D * Uni_ViewPortSizeRatio;
Uniform::Trans3D * Uni_View;
Uniform::Depth * Uni_Depth;

Multiform::SizeRatio2D * Multi_ViewPortSizeRatio;
Multiform::Trans3D * Multi_View;
Multiform::Depth * Multi_Depth;

float Light_Ambient_Intensity;
LightBase Light_Ambient;
Uniform::LightBase * Uni_Light_Ambient;

float Light_Solar_Intensity;
LightSolar Light_Solar;
Uniform::LightSolar * Uni_Light_Solar;

unsigned int Light_Spot_Limit;
LightSpot * Light_Spot_Array;
SpotLightEntry * Light_Spot_Entry_Array;

Uniform::GArray<Uniform::LightSpot, LightSpot> * Uni_Light_Spot_Array;

unsigned int Light_Spot_Count;
Uniform::UInt1 * Uni_Light_Spot_Count;



void InitShaders()
{
	PH_Shader = new Shader::Base((const Shader::Code []) {
		Shader::Code::FromFile(ShaderDir.File("PH_S3D.vert")),
		Shader::Code::FromFile(ShaderDir.File("PH_ULight.frag"))
	}, 2);

	Uni_ViewPortSizeRatio = new Uniform::SizeRatio2D("ViewPortSizeRatio", *PH_Shader);
	Uni_View = new Uniform::Trans3D("View", *PH_Shader);
	Uni_Depth = new Uniform::Depth("Depth", *PH_Shader);

	Multi_ViewPortSizeRatio = new Multiform::SizeRatio2D("ViewPortSizeRatio");
	Multi_View = new Multiform::Trans3D("View");
	Multi_Depth = new Multiform::Depth("Depth");

	Shader::Base * shaders [] = {
		PH_Shader,
	};
	int shader_count = 1;

	Multi_ViewPortSizeRatio -> FindUniforms(shaders, shader_count);
	Multi_View -> FindUniforms(shaders, shader_count);
	Multi_Depth -> FindUniforms(shaders, shader_count);

	Multi_Depth -> ChangeData(ViewDepth);

	Uni_Light_Ambient = new Uniform::LightBase("Ambient", *PH_Shader);
	Uni_Light_Solar = new Uniform::LightSolar("Solar", *PH_Shader);
	Uni_Light_Spot_Array = new Uniform::GArray<Uniform::LightSpot, LightSpot>(Light_Spot_Limit, "SpotArr", *PH_Shader);
	Uni_Light_Spot_Count = new Uniform::UInt1(1, "SpotCount", *PH_Shader);
}
void FreeShaders()
{
	delete PH_Shader;

	delete Uni_ViewPortSizeRatio;
	delete Uni_View;
	delete Uni_Depth;

	delete Multi_ViewPortSizeRatio;
	delete Multi_View;
	delete Multi_Depth;

	delete Uni_Light_Ambient;
	delete Uni_Light_Solar;
	delete Uni_Light_Spot_Array;
	delete Uni_Light_Spot_Count;
}

void AddInstances()
{
	int Range_Size1 = 0x1FF;
	int Range_SizeH = 0x0FF;
	int j_len = 16;
	int i_len = 16;
	for (int j = 0; j < j_len; j++)
	{
		Entrys.Insert(PH0_Instances -> Alloc(i_len));
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
			(*Entrys[j])[i].Trans.Pos = center + Point3D(
				(std::rand() & Range_Size1) - Range_SizeH,
				(std::rand() & Range_Size1) - Range_SizeH,
				(std::rand() & Range_Size1) - Range_SizeH
			);
			(*Entrys[j])[i].Trans.Rot = rot;
		}
	}

	/*for (int j = 0; j < j_len; j++)
	{
		std::cout << "[" << j << "]" << (*Entrys[j]).Offset << "|" << (*Entrys[j]).Length << "\n";
	}*/

	{
		std::cout << "Instance Count: " << (PH0_Instances -> Instances.Length) << "\n";
		//int MemSize = (PH0_Instances -> Instances.Length) * sizeof(Simple3D_InstData);
		//std::cout << (MemSize / (1)) << " Bytes\n";
		//std::cout << (MemSize / (1 * 1000)) << "k Bytes\n";
		//std::cout << (MemSize / (1 * 1000 * 1000)) << "M Bytes\n";
	}
}


void FancyInsert(unsigned int ph_idx, Point3D pos, Angle3D rot)
{
	unsigned int idx = Entrys.Count();
	Entrys.Insert(FancyPolyHedraInstances[ph_idx] -> Alloc(1));
	(*Entrys[idx])[0].Trans = Trans3D(pos, rot);
	(*Entrys[idx])[0].Trans.Rot.CalcBack();
}
void Fancify()
{
	DirectoryContext YMT_Dir("./media/YMT/Light/");
	unsigned int idx_stage =				FancyPolyHedras.Insert(YMT::PolyHedra::Load(YMT_Dir.File("Stage.polyhedra.ymt")));
	unsigned int idx_stage_light =			FancyPolyHedras.Insert(YMT::PolyHedra::Load(YMT_Dir.File("Stage_Light.polyhedra.ymt")));
	unsigned int idx_stage_light_holder =	FancyPolyHedras.Insert(YMT::PolyHedra::Load(YMT_Dir.File("Stage_Light_Holder.polyhedra.ymt")));
	unsigned int idx_truss =				FancyPolyHedras.Insert(YMT::PolyHedra::Load(YMT_Dir.File("Truss_Square40cm_Len200cm.polyhedra.ymt")));
	unsigned int idx_truss_cube =			FancyPolyHedras.Insert(YMT::PolyHedra::Load(YMT_Dir.File("Truss_Cube40cm.polyhedra.ymt")));
	unsigned int idx_chair =				FancyPolyHedras.Insert(YMT::PolyHedra::Load(YMT_Dir.File("Chair.polyhedra.ymt")));

	for (unsigned int i = 0; i < FancyPolyHedras.Count(); i++)
	{
		FancyPolyHedraInstances.Insert(new PolyHedra_3D_Instances(FancyPolyHedras[i]));
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
		Light_Spot_Entry_Array[i].EntryLight = FancyPolyHedraInstances[idx_stage_light] -> Alloc(1);
		Light_Spot_Entry_Array[i].EntryHolder = FancyPolyHedraInstances[idx_stage_light_holder] -> Alloc(1);
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

	Poly0 = YMT::PolyHedra::Cube();
	PH0_Instances = new PolyHedra_3D_Instances(Poly0);

	AddInstances();
	Fancify();

	std::cout << "Init 1\n";
}
void Free()
{
	std::cout << "Free 0\n";

	delete PH0_Instances;
	delete Poly0;
	for (unsigned int i = 0; i < FancyPolyHedraInstances.Count(); i++)
	{
		delete FancyPolyHedraInstances[i];
	}
	for (unsigned int i = 0; i < FancyPolyHedras.Count(); i++)
	{
		delete FancyPolyHedras[i];
	}

	FreeShaders();

	std::cout << "Free 1\n";
}

void Update(double timeDelta)
{
	(void)timeDelta;
}
void Frame(double timeDelta)
{
	if (win -> IsCursorLocked())
	{
		ViewTrans.TransformFlatX(win -> MoveFromKeys(20.0f * timeDelta), win -> SpinFromCursor(0.2f * timeDelta));
	}
	ViewTrans.Rot.CalcBack();
	Multi_View -> ChangeData(ViewTrans);
	//Light_Spot.Pos = ViewTrans.Pos;
	//Light_Spot.Dir = ViewTrans.Rot.rotate(Point3D(0, 0, 1));

	if (win -> Keys[GLFW_KEY_1].State.GetPressed())
	{
		if (Light_Ambient.Intensity == 0.0f)
		{ Light_Ambient.Intensity = Light_Ambient_Intensity; }
		else
		{ Light_Ambient.Intensity = 0.0f; }
	}
	if (win -> Keys[GLFW_KEY_2].State.GetPressed())
	{
		if (Light_Solar.Base.Intensity == 0.0f)
		{ Light_Solar.Base.Intensity = Light_Solar_Intensity; }
		else
		{ Light_Solar.Base.Intensity = 0.0f; }
	}
	if (win -> Keys[GLFW_KEY_3].State.GetPressed()) { Light_Spot_Entry_Array[0].Toggle(); }
	if (win -> Keys[GLFW_KEY_4].State.GetPressed()) { Light_Spot_Entry_Array[1].Toggle(); }
	if (win -> Keys[GLFW_KEY_5].State.GetPressed()) { Light_Spot_Entry_Array[2].Toggle(); }

	if (win -> Keys[GLFW_KEY_Q].State.GetPressed())
	{
		std::cout << "View.Pos: " << ViewTrans.Pos << "\n";
	}

	for (unsigned int i = 0; i < Light_Spot_Limit; i++)
	{
		Light_Spot_Entry_Array[i].Update();
	}

	PH_Shader -> Use();
	Uni_Light_Ambient -> PutData(Light_Ambient);
	Uni_Light_Solar -> PutData(Light_Solar);
	for (unsigned int i = 0; i < Light_Spot_Limit; i++)
	{
		if (Light_Spot_Entry_Array[i].Light != NULL)
		{
			(*Uni_Light_Spot_Array)[i].PutData(*(Light_Spot_Entry_Array[i].Light));
		}
	}
	Uni_Light_Spot_Count -> PutData(&Light_Spot_Count);

	(*Entrys[0])[0].Trans.Pos = Point3D(0, 10, 0);
	(*Entrys[0])[0].Trans.Rot.X += 0.01f;
	(*Entrys[0])[0].Trans.Rot.CalcBack();

	PH0_Instances -> Update().Draw();
	for (unsigned int i = 0; i < FancyPolyHedraInstances.Count(); i++)
	{
		FancyPolyHedraInstances[i] -> Update().Draw();
	}
}

void Resize(int w, int h)
{
	Multi_ViewPortSizeRatio -> ChangeData(SizeRatio2D(w, h));
}



int main()
{
	if (glfwInit() == 0)
	{
		std::cout << "GLFW Init Failed\n";
		return -1;
	}

	win = new Window(640, 480);
	win -> InitFunc = Init;
	win -> FrameFunc = Frame;
	win -> FreeFunc = Free;
	win -> ResizeFunc = Resize;

	win -> DefaultColor = Color(0.0f, 0.0f, 0.0f);

	ViewTrans = Trans3D(Point3D(0, 10, -65), Angle3D(0, 0, 0));
	ViewDepth.Factors = DepthFactors(0.1f, 1000.0f);
	ViewDepth.Range = Range(0.8f, 1.0f);
	ViewDepth.Color = win -> DefaultColor;

	Light_Ambient_Intensity = 0.01f;
	Light_Solar_Intensity = 0.2f;
	Light_Ambient = LightBase(Light_Ambient_Intensity, Color(1.0f, 1.0f, 1.0f));
	Light_Solar = LightSolar(Light_Solar_Intensity, Color(1.0f, 1.0f, 1.0f), Point3D(+1, -3, +2).normalize());

	Light_Spot_Limit = 4;
	Light_Spot_Array = new LightSpot[Light_Spot_Limit];
	Light_Spot_Array[0] = LightSpot(1.0f, Color(1.0f, 0.0f, 0.0f), Point3D(), Point3D(), Range(0.8, 0.95));
	Light_Spot_Array[1] = LightSpot(1.0f, Color(0.0f, 1.0f, 0.0f), Point3D(), Point3D(), Range(0.8, 0.95));
	Light_Spot_Array[2] = LightSpot(1.0f, Color(0.0f, 0.0f, 1.0f), Point3D(), Point3D(), Range(0.8, 0.95));
	Light_Spot_Array[3] = LightSpot(1.0f, Color(1.0f, 1.0f, 1.0f), Point3D(), Point3D(), Range(0.8, 0.95));
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
	win -> Run();
	std::cout << "---- Run\n";



	delete[] Light_Spot_Entry_Array;
	delete[] Light_Spot_Array;
	delete win;



	glfwTerminate();
	std::cout << "main() return";
	return 0;
}
