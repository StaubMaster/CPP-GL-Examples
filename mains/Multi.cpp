
#include <iostream>
#include "OpenGL/openGL.h"

#include "Debug.hpp"

#include "DataInclude.hpp"
#include "DataShow.hpp"

#include "Miscellaneous/Container/Dynamic.hpp"
#include "Miscellaneous/EntryContainer/Dynamic.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Graphics/Shader/Base.hpp"

#include "Graphics/UniformsInclude.hpp"
#include "Graphics/MultiformsInclude.hpp"

#include "DataStruct/Full/PolyHedra_3D/PolyHedra_3D_Instances.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Generate.hpp"

#include "PolyHedra/Skin/SkinBase.hpp"
#include "PolyHedra/Skin/Skin2DA.hpp"

#include "Graphics/Texture/Base.hpp"
#include "Graphics/Texture/2DArray.hpp"
#include "Graphics/Texture/Generate.hpp"

#include "Window.hpp"

#include "DirectoryContext.hpp"
#include "FileContext.hpp"
#include "Format/Image.hpp"

#include <signal.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>



DirectoryContext * ImageDir = new DirectoryContext("./media/Images");
DirectoryContext * ShaderDir = new DirectoryContext("./media/Shaders");



Window * win;

Trans3D	ViewTrans;
Depth	ViewDepth;

Container::Dynamic<YMT::PolyHedra *> * PHs;
Container::Dynamic<PolyHedra_3D_Instances *> * PH_Instances;
Container::Dynamic<EntryContainer::Entry<Simple3D_InstData>> * Instance_Entrys;

Container::Dynamic<Shader::Base *> * PH_Shaders;
Container::Dynamic<Uniform::SizeRatio2D *> * Uni_ViewPortSizeRatio;
Container::Dynamic<Uniform::Trans3D *> * Uni_View;
Container::Dynamic<Uniform::Depth *> * Uni_Depth;

Multiform::SizeRatio2D * Multi_ViewPortSizeRatio;
Multiform::Trans3D * Multi_View;
Multiform::Depth * Multi_Depth;



void InitRun()
{
	std::cout << "\nINIT ...\n\n";
	std::cout << std::flush;
	std::cout.flush();
	//return;

	std::cout << "\nShaders\n\n";
	std::cout << __FILE__ << ':' << __LINE__ << '\n';
	PH_Shaders = new Container::Dynamic<Shader::Base *>();
	std::cout << __FILE__ << ':' << __LINE__ << '\n';
	PH_Shaders -> Insert(new Shader::Base((const Shader::Code []) {
		Shader::Code::FromFile(ShaderDir -> File("PH_S3D.vert")),
		Shader::Code::FromFile(ShaderDir -> File("PH_Full.frag"))
	}, 2));
	std::cout << __FILE__ << ':' << __LINE__ << '\n';
	PH_Shaders -> Insert(new Shader::Base((const Shader::Code []) {
		Shader::Code::FromFile(ShaderDir -> File("PH_S3D.vert")),
		Shader::Code::FromFile(ShaderDir -> File("PH_R.frag"))
	}, 2));
	std::cout << __FILE__ << ':' << __LINE__ << '\n';
	PH_Shaders -> Insert(new Shader::Base((const Shader::Code []) {
		Shader::Code::FromFile(ShaderDir -> File("PH_S3D.vert")),
		Shader::Code::FromFile(ShaderDir -> File("PH_G.frag"))
	}, 2));
	std::cout << __FILE__ << ':' << __LINE__ << '\n';
	PH_Shaders -> Insert(new Shader::Base((const Shader::Code []) {
		Shader::Code::FromFile(ShaderDir -> File("PH_S3D.vert")),
		Shader::Code::FromFile(ShaderDir -> File("PH_B.frag"))
	}, 2));

	std::cout << "\nUniforms\n\n";
	Uni_ViewPortSizeRatio = new Container::Dynamic<Uniform::SizeRatio2D *>();
	Uni_View = new Container::Dynamic<Uniform::Trans3D *>();
	Uni_Depth = new Container::Dynamic<Uniform::Depth *>();
	std::cout << "\nUniforms\n\n";
	for (unsigned int i = 0; i < PH_Shaders -> Count(); i++)
	{
		Uni_ViewPortSizeRatio -> Insert(new Uniform::SizeRatio2D("ViewPortSizeRatio", *((*PH_Shaders)[i])));
		Uni_View -> Insert(new Uniform::Trans3D("View", *((*PH_Shaders)[i])));
		Uni_Depth -> Insert(new Uniform::Depth("Depth", *((*PH_Shaders)[i])));
	}

	std::cout << "\nMultiform\n\n";
	Multi_ViewPortSizeRatio = new Multiform::SizeRatio2D("ViewPortSizeRatio");
	Multi_View = new Multiform::Trans3D("View");
	Multi_Depth = new Multiform::Depth("Depth");
	{
		Shader::Base** shaders = (Shader::Base**)PH_Shaders -> Data();
		unsigned int shaders_count = PH_Shaders -> Count();

		Multi_ViewPortSizeRatio -> FindUniforms(shaders, shaders_count);
		Multi_View -> FindUniforms(shaders, shaders_count);
		Multi_Depth -> FindUniforms(shaders, shaders_count);
	}
	Multi_Depth -> ChangeData(ViewDepth);
	
	std::cout << "\nPolyHedra\n\n";
	PHs = new Container::Dynamic<YMT::PolyHedra *>();
	std::cout << "\nPolyHedra\n\n";
	PHs -> Insert(YMT::PolyHedra::Generate::Cube(2.0f));
	PHs -> Insert(YMT::PolyHedra::Generate::Cube(0.5f));
	PHs -> Insert(YMT::PolyHedra::Generate::Cube(1.0f));
	PHs -> Insert(YMT::PolyHedra::Generate::Cube(1.5f));

	std::cout << "\nPolyHedra Instances\n\n";
	PH_Instances = new Container::Dynamic<PolyHedra_3D_Instances *>();
	std::cout << "\nPolyHedra Instances\n\n";
	for (unsigned int i = 0; i < PHs -> Count(); i++)
	{
		PH_Instances -> Insert(new PolyHedra_3D_Instances((*PHs)[i]));
	}

	std::cout << "\nPolyHedra Instances Entrys\n\n";
	Instance_Entrys = new Container::Dynamic<EntryContainer::Entry<Simple3D_InstData>>();
	std::cout << "\nPolyHedra Instances Entrys\n\n";
	if (PH_Instances -> Count() > 0)
	{
		std::cout << __FILE__ << ':' << __LINE__ << '\n';
		std::cout << "Instance Count: " << ((*PH_Instances)[0] -> Instances.Count()) << '\n';
		EntryContainer::Entry<Simple3D_InstData> entry((*PH_Instances)[0] -> Instances, 8);
		std::cout << "Instance Count: " << ((*PH_Instances)[0] -> Instances.Count()) << '\n';
		std::cout << __FILE__ << ':' << __LINE__ << '\n';
		std::cout << "Instance_Entrys Count: " << (Instance_Entrys -> Count()) << '\n';
		unsigned int idx = Instance_Entrys -> Count();
		Instance_Entrys -> Insert(entry);
		std::cout << "Instance_Entrys Count: " << (Instance_Entrys -> Count()) << '\n';
		std::cout << __FILE__ << ':' << __LINE__ << '\n';
		//unsigned int idx = Instance_Entrys.Insert(EntryContainer::Entry<Simple3D_InstData>(PH_Instances[0] -> Instances, 1));
		Point3D pos[8] = {
			Point3D(-10, -10, -10),
			Point3D(+10, -10, -10),
			Point3D(-10, +10, -10),
			Point3D(+10, +10, -10),
			Point3D(-10, -10, +10),
			Point3D(+10, -10, +10),
			Point3D(-10, +10, +10),
			Point3D(+10, +10, +10),
		};
		std::cout << __FILE__ << ':' << __LINE__ << '\n';
		for (unsigned int i = 0; i < ((*Instance_Entrys)[idx]).Length(); i++)
		{
			((*Instance_Entrys)[idx])[i].Trans.Pos = pos[i];
			((*Instance_Entrys)[idx])[i].Trans.Rot = Angle3D();
			((*Instance_Entrys)[idx])[i].Trans.Rot.CalcBack();
		}
		std::cout << __FILE__ << ':' << __LINE__ << '\n';
	}
	std::cout << '\n';
	if (PH_Instances -> Count() > 1)
	{
		std::cout << __FILE__ << ':' << __LINE__ << '\n';
		std::cout << "Instance Count: " << ((*PH_Instances)[1] -> Instances.Count()) << '\n';
		EntryContainer::Entry<Simple3D_InstData> entry((*PH_Instances)[1] -> Instances, 8);
		std::cout << "Instance Count: " << ((*PH_Instances)[1] -> Instances.Count()) << '\n';
		std::cout << __FILE__ << ':' << __LINE__ << '\n';
		std::cout << "Instance_Entrys Count: " << (Instance_Entrys -> Count()) << '\n';
		unsigned int idx = Instance_Entrys -> Count();
		Instance_Entrys -> Insert(entry);
		std::cout << "Instance_Entrys Count: " << (Instance_Entrys -> Count()) << '\n';
		std::cout << __FILE__ << ':' << __LINE__ << '\n';
		//unsigned int idx = Instance_Entrys.Insert(EntryContainer::Entry<Simple3D_InstData>(PH_Instances[1] -> Instances, 1));
		for (unsigned int i = 0; i < ((*Instance_Entrys)[idx]).Length(); i++)
		{
			Angle3D a((TAU * i) / ((*Instance_Entrys)[idx]).Length(), 0, 0);
			a.CalcBack();
			((*Instance_Entrys)[idx])[i].Trans.Pos = a.rotate(Point3D(0, 0, 10));
			((*Instance_Entrys)[idx])[i].Trans.Rot = a;
		}
		std::cout << __FILE__ << ':' << __LINE__ << '\n';
	}
	std::cout << '\n';
	if (PH_Instances -> Count() > 2)
	{
		std::cout << __FILE__ << ':' << __LINE__ << '\n';
		std::cout << "Instance Count: " << ((*PH_Instances)[2] -> Instances.Count()) << '\n';
		EntryContainer::Entry<Simple3D_InstData> entry((*PH_Instances)[2] -> Instances, 8);
		std::cout << "Instance Count: " << ((*PH_Instances)[2] -> Instances.Count()) << '\n';
		std::cout << __FILE__ << ':' << __LINE__ << '\n';
		std::cout << "Instance_Entrys Count: " << (Instance_Entrys -> Count()) << '\n';
		unsigned int idx = Instance_Entrys -> Count();
		Instance_Entrys -> Insert(entry);
		std::cout << "Instance_Entrys Count: " << (Instance_Entrys -> Count()) << '\n';
		std::cout << __FILE__ << ':' << __LINE__ << '\n';
		//unsigned int idx = Instance_Entrys.Insert(EntryContainer::Entry<Simple3D_InstData>(PH_Instances[2] -> Instances, 1));
		for (unsigned int i = 0; i < ((*Instance_Entrys)[idx]).Length(); i++)
		{
			Angle3D a(0, (TAU * i) / ((*Instance_Entrys)[idx]).Length(), 0);
			a.CalcBack();
			((*Instance_Entrys)[idx])[i].Trans.Pos = a.rotate(Point3D(0, 15, 0));
			((*Instance_Entrys)[idx])[i].Trans.Rot = a;
		}
		std::cout << __FILE__ << ':' << __LINE__ << '\n';
	}
	std::cout << '\n';
	if (PH_Instances -> Count() > 3)
	{
		std::cout << __FILE__ << ':' << __LINE__ << '\n';
		std::cout << "Instance Count: " << ((*PH_Instances)[3] -> Instances.Count()) << '\n';
		EntryContainer::Entry<Simple3D_InstData> entry((*PH_Instances)[3] -> Instances, 8);
		std::cout << "Instance Count: " << ((*PH_Instances)[3] -> Instances.Count()) << '\n';
		std::cout << __FILE__ << ':' << __LINE__ << '\n';
		std::cout << "Instance_Entrys Count: " << (Instance_Entrys -> Count()) << '\n';
		unsigned int idx = Instance_Entrys -> Count();
		Instance_Entrys -> Insert(entry);
		std::cout << "Instance_Entrys Count: " << (Instance_Entrys -> Count()) << '\n';
		std::cout << __FILE__ << ':' << __LINE__ << '\n';
		//unsigned int idx = Instance_Entrys.Insert(EntryContainer::Entry<Simple3D_InstData>(PH_Instances[3] -> Instances, 1));
		for (unsigned int i = 0; i < ((*Instance_Entrys)[idx]).Length(); i++)
		{
			Angle3D a(0, 0, (TAU * i) / ((*Instance_Entrys)[idx]).Length());
			a.CalcBack();
			((*Instance_Entrys)[idx])[i].Trans.Pos = a.rotate(Point3D(20, 0, 0));
			((*Instance_Entrys)[idx])[i].Trans.Rot = a;
		}
		std::cout << __FILE__ << ':' << __LINE__ << '\n';
	}
	std::cout << '\n';
	{
		std::cout << "PH_Instances " << (PH_Instances -> Count()) << '\n';
		for (unsigned int i = 0; i < PH_Instances -> Count(); i++)
		{
			std::cout << "PH_Instances" << " [" << i << "] " << ((*PH_Instances)[i] -> Instances.Count()) << '\n';
		}
		std::cout << "Instance_Entrys " << (Instance_Entrys -> Count()) << '\n';
	}
	std::cout << "\nINIT done\n\n";
	std::cout << "Init _CrtDumpMemoryLeaks" << ' ' << _CrtDumpMemoryLeaks() << '\n';
	std::cout << std::flush;
	//std::cout.flush();
}
void FreeRun()
{
	std::cerr << "Free _CrtDumpMemoryLeaks" << ' ' << _CrtDumpMemoryLeaks() << '\n';

	std::cout << "\nFREE ...\n\n";
	std::cout << std::flush;
	//std::cout.flush();
	//return;

	std::cout << __FILE__ << ':' << __LINE__ << '\n';
	//Instance_Entrys.Dispose();

	std::cout << '\n';
	std::cout << "PH_Instances" << ' ' << "Count" << ' ' << PH_Instances -> Count() << '\n';
	for (unsigned int i = 0; i < PH_Instances -> Count(); i++)
	{
		std::cout << "[" << i << "]";
		std::cout << (*PH_Instances)[i] -> Instances.Count();
		std::cout << '\n';
		delete (*PH_Instances)[i];
		std::cout << "[" << i << "]";
		std::cout << " done";
		std::cout << '\n';
	}
	std::cout << __FILE__ << ':' << __LINE__ << '\n';
	delete PH_Instances;

	std::cout << '\n';
	std::cout << "PHs" << ' ' << "Count" << ' ' << PHs -> Count() << '\n';
	for (unsigned int i = 0; i < PHs -> Count(); i++)
	{
		delete (*PHs)[i];
	}
	std::cout << __FILE__ << ':' << __LINE__ << '\n';
	delete PHs;

	std::cout << '\n';
	std::cout << "PH_Shaders" << ' ' << "Count" << ' ' << PH_Shaders -> Count() << '\n';
	for (unsigned int i = 0; i < PH_Shaders -> Count(); i++)
	{
		delete (*PH_Shaders)[i];
	}
	std::cout << __FILE__ << ':' << __LINE__ << '\n';
	delete PH_Shaders;

	std::cout << '\n';
	std::cout << "Uni_ViewPortSizeRatio" << ' ' << "Count" << ' ' << Uni_ViewPortSizeRatio -> Count() << '\n';
	for (unsigned int i = 0; i < Uni_ViewPortSizeRatio -> Count(); i++)
	{
		delete (*Uni_ViewPortSizeRatio)[i];
	}
	std::cout << __FILE__ << ':' << __LINE__ << '\n';
	delete Uni_ViewPortSizeRatio;

	std::cout << '\n';
	std::cout << "Uni_View" << ' ' << "Count" << ' ' << Uni_View -> Count() << '\n';
	for (unsigned int i = 0; i < Uni_View -> Count(); i++)
	{
		delete (*Uni_View)[i];
	}
	std::cout << __FILE__ << ':' << __LINE__ << '\n';
	delete Uni_View;

	std::cout << '\n';
	std::cout << "Uni_Depth" << ' ' << "Count" << ' ' << Uni_Depth -> Count() << '\n';
	for (unsigned int i = 0; i < Uni_Depth -> Count(); i++)
	{
		delete (*Uni_Depth)[i];
	}
	std::cout << __FILE__ << ':' << __LINE__ << '\n';
	delete Uni_Depth;

	std::cout << '\n';
	std::cout << __FILE__ << ':' << __LINE__ << '\n';

	std::cout << "\nFREE done\n\n";
	std::cout << std::flush;
	//std::cout.flush();
}



void Frame(double timeDelta)
{
	if (win -> IsCursorLocked())
	{
		ViewTrans.TransformFlatX(win -> MoveFromKeys(20.0f * timeDelta), win -> SpinFromCursor(0.2f * timeDelta));
	}
	ViewTrans.Rot.CalcBack();
	Multi_View -> ChangeData(ViewTrans);
	for (unsigned int i = 0; i < PH_Shaders -> Count(); i++)
	{
		(*PH_Shaders)[i] -> Use();
		if (i < PH_Instances -> Count())
		{
			(*PH_Instances)[i] -> Update().Draw();
		}
	}
}

void Resize(int w, int h)
{
	Multi_ViewPortSizeRatio -> ChangeData(SizeRatio2D(w, h));
	(void)w;
	(void)h;
}




void signal_handler(int s)
{
	std::cerr << "\nSignal " << s << "\n";
	std::cerr << "SIGINT " << SIGINT << "\n";
	std::cerr << "done\n";
	glfwSetWindowShouldClose(win -> win, GL_TRUE);
}

/*void check_leaks()
{
	system("leaks");
}*/



int main()
{
	try
	{
	//atexit(check_leaks);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	signal(SIGINT, signal_handler);
	std::cout << "here\n";
	//std::cout << std::flush;
	std::cout.flush();

	Debug::NewFileInDir(DirectoryContext("logs/"));

	if (glfwInit() == 0)
	{
		std::cout << "GLFW Init Failed\n";
		return -1;
	}

	win = new Window(640, 480);
	win -> InitFunc = InitRun;
	win -> FrameFunc = Frame;
	win -> FreeFunc = FreeRun;
	win -> ResizeFunc = Resize;

	win -> DefaultColor = Color(0.5f, 0.5f, 0.5f);

	ViewTrans = Trans3D(Point3D(0, 0, 0), Angle3D(0, 0, 0));
	ViewDepth.Factors = DepthFactors(0.1f, 1000.0f);
	ViewDepth.Range = Range(0.8f, 1.0f);
	ViewDepth.Color = win -> DefaultColor;

	std::cout << __FILE__ << ':' << __LINE__ << '\n';

	std::cout << "<<<< Run Window" << '\n';
	Debug::Log << "<<<< Run Window" << Debug::Done;
	win -> Run();
	Debug::Log << ">>>> Run Window" << Debug::Done;
	std::cout << ">>>> Run Window" << '\n';
	
	std::cout << __FILE__ << ':' << __LINE__ << '\n';
	std::cout << "_CrtDumpMemoryLeaks" << ' ' << _CrtDumpMemoryLeaks() << '\n';

	delete win;
	std::cout << __FILE__ << ':' << __LINE__ << '\n';
	glfwTerminate();	// Crashes here ?
	std::cout << __FILE__ << ':' << __LINE__ << '\n';

	}
	catch (std::exception & ex)
	{
		std::cerr << "Error: " << ex.what() << '\n';
	}
	catch (...)
	{
		std::cerr << "Error: " << "Unknown" << '\n';
	}

	std::cout << "_CrtDumpMemoryLeaks" << ' ' << _CrtDumpMemoryLeaks() << '\n';
	std::cout << "\nmain() return\n\n";
	return 0;
}
