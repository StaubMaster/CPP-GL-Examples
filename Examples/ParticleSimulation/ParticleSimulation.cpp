#include <iostream>
#include "OpenGL/openGL.h"

#include "Window.hpp"
#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Generate.hpp"
#include "Graphics/Texture/2DArray.hpp"
#include "PolyHedra/Skin/Skin2DA.hpp"

#include "DataInclude.hpp"
#include "DataShow.hpp"

#include "DataStruct/Main/PolyHedra.hpp"
#include "DataStruct/Inst/Physics3D.hpp"

#include "Graphics/Shader/Base.hpp"
#include "Graphics/Shader/Code.hpp"
#include "Graphics/Buffer/Instance_Base_BufferArray.hpp"

#include "Graphics/UniformsInclude.hpp"

#include "FileContext.hpp"
#include "DirectoryContext.hpp"



#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_TARGET_OPENCL_VERSION 200
#include <CL/opencl.hpp>
//#include <opencl.h>



DirectoryContext ImageDir("../../media/Images");
DirectoryContext ShaderDir("../../media/Shaders");
DirectoryContext KernelDir("../../media/Kernel");



Window * win;

Trans3D	ViewTrans;
Depth	ViewDepth;
Ray3D	ViewRay;

Texture::T2DArray * PH_Texture;

YMT::PolyHedra * PH;

Instance_Base_BufferArray<
	PolyHedra_MainData,
	PolyHedra_MainBuffer,
	Physics3D_InstData,
	Physics3D_InstBuffer
> * PH_Physics3D_BufferArray;

Shader::Base * PH_Physics3D_Shader;

Uniform::SizeRatio2D * Uni_ViewPortSizeRatio;
Uniform::Trans3D * Uni_ViewTrans;
Uniform::Depth * Uni_ViewDepth;



unsigned int EntityCountX = 32;
unsigned int EntityCountY = 32;
unsigned int EntityCountZ = 32;
unsigned int EntityCount = EntityCountX * EntityCountY * EntityCountZ;

void CL_PrintError(cl_int err, bool printSuccess = false)
{
	if (err != CL_SUCCESS)
	{
		std::cout << "Error: " << err << "\n";
	}
	else if (printSuccess)
	{
		std::cout << "Succ\n";
	}
}

cl::Program CL_Program;

cl::SVMAllocator<Ray3D, cl::SVMTraitCoarse<cl::SVMTraitReadOnly<>>> SVM_Ray_Alloc;
Ray3D * ViewRay_GPU_Ptr;

cl::SVMAllocator<Physics3D_InstData, cl::SVMTraitFine<>> SVM_Physics3D_Alloc;
unsigned int BufferSize = EntityCount * sizeof(Physics3D_InstData);
Physics3D_InstData * Physics3D_GPU_Ptr;

cl::KernelFunctor<
	Physics3D_InstData *
> * Kernel_Init;

cl::KernelFunctor<
	Physics3D_InstData *
> * Kernel_Move;

cl::KernelFunctor<
	Physics3D_InstData *
> * Kernel_Keep;

cl::KernelFunctor<
	Physics3D_InstData *
> * Kernel_Look;

cl::KernelFunctor<
	Ray3D *,
	Physics3D_InstData *
> * Kernel_GravRay;

void CL_Run_Init()
{
	cl_int err = CL_SUCCESS;
	(*Kernel_Init)(
		cl::EnqueueArgs(
			cl::NDRange(EntityCountX, EntityCountY, EntityCountZ)
		),
		Physics3D_GPU_Ptr,
		err
	);
	CL_PrintError(err);
	//cl::finish();
}
void CL_Run_Move()
{
	cl_int err = CL_SUCCESS;
	(*Kernel_Move)(
		cl::EnqueueArgs(
			cl::NDRange(EntityCount)
		),
		Physics3D_GPU_Ptr,
		err
	);
	CL_PrintError(err);
	//cl::finish();
}
void CL_Run_Keep()
{
	cl_int err = CL_SUCCESS;
	(*Kernel_Keep)(
		cl::EnqueueArgs(
			cl::NDRange(EntityCount)
		),
		Physics3D_GPU_Ptr,
		err
	);
	CL_PrintError(err);
	//cl::finish();
}
void CL_Run_Look()
{
	cl_int err = CL_SUCCESS;
	(*Kernel_Look)(
		cl::EnqueueArgs(
			cl::NDRange(EntityCount)
		),
		Physics3D_GPU_Ptr,
		err
	);
	CL_PrintError(err);
	//cl::finish();
}
void CL_Run_GravRay()
{
	cl_int err = CL_SUCCESS;
	(*Kernel_GravRay)(
		cl::EnqueueArgs(
			cl::NDRange(EntityCount)
		),
		ViewRay_GPU_Ptr,
		Physics3D_GPU_Ptr,
		err
	);
	CL_PrintError(err);
	//cl::finish();
}

void CL_Init()
{
	cl_int err = CL_SUCCESS;

	FileContext file = KernelDir.File("PhysSim.cl");
	CL_Program = cl::Program(file.LoadText());
	try
	{
		CL_Program.build("-cl-std=CL2.0");
	}
	catch (...)
	{
		cl::BuildLogType buildInfo = CL_Program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(&err);
		CL_PrintError(err);
		for (std::pair<cl::Device, std::string> &pair : buildInfo)
		{
			std::cerr << pair.second << std::endl << std::endl;
		}
	}

	try
	{
		Kernel_Init = new cl::KernelFunctor<
			Physics3D_InstData *
		>(CL_Program, "Init", &err);
		CL_PrintError(err);

		Kernel_Move = new cl::KernelFunctor<
			Physics3D_InstData *
		>(CL_Program, "Move", &err);
		CL_PrintError(err);

		Kernel_Keep = new cl::KernelFunctor<
			Physics3D_InstData *
		>(CL_Program, "Keep", &err);
		CL_PrintError(err);

		Kernel_Look = new cl::KernelFunctor<
			Physics3D_InstData *
		>(CL_Program, "Look", &err);
		CL_PrintError(err);

		Kernel_GravRay = new cl::KernelFunctor<
			Ray3D *,
			Physics3D_InstData *
		>(CL_Program, "GravRay", &err);
		CL_PrintError(err);
	}
	catch(...)
	{
		std::cout << "Kernel Error\n";
		CL_PrintError(err);
		exit(1);
	}

	ViewRay_GPU_Ptr = SVM_Ray_Alloc.allocate(1);
	Physics3D_GPU_Ptr = SVM_Physics3D_Alloc.allocate(BufferSize);

	CL_Run_Init();
	cl::finish();
}
void CL_Free()
{
	delete Kernel_Init;
	delete Kernel_Move;
	delete Kernel_Keep;
	delete Kernel_Look;
	delete Kernel_GravRay;

	SVM_Ray_Alloc.deallocate(ViewRay_GPU_Ptr, 1);
	SVM_Physics3D_Alloc.deallocate(Physics3D_GPU_Ptr, BufferSize);
}



void Init()
{
	std::cout << "Init 0\n";

	PH_Texture = new Texture::T2DArray(128, 128, 1, (FileContext[])
	{
		ImageDir.File("GrayDeant.png"),
	});

	PH = YMT::PolyHedra::Generate::ConeC(4, 0.5f, 1.0f);
	std::cout << (PH -> ToInfo()) << "\n";

	PH_Physics3D_BufferArray = new Instance_Base_BufferArray<
		PolyHedra_MainData,
		PolyHedra_MainBuffer,
		Physics3D_InstData,
		Physics3D_InstBuffer
	> (
		new PolyHedra_MainBuffer(0, 1, 2),
		new Physics3D_InstBuffer(3, 4, 7, 8),
		GL_TRIANGLES
	);
	{
		int count;
		PolyHedra_MainData * data = PH -> ToMainData(count);
		PH_Physics3D_BufferArray -> BindMain(data, count);
		delete [] data;
	}

	PH_Physics3D_Shader = new Shader::Base((const Shader::Code []) {
		Shader::Code::FromFile(ShaderDir.File("PH_Phys3D.vert")),
		Shader::Code::FromFile(ShaderDir.File("PH_Full.frag"))
	}, 2);
	Uni_ViewPortSizeRatio = new Uniform::SizeRatio2D("ViewPortSizeRatio", *PH_Physics3D_Shader);
	Uni_ViewTrans = new Uniform::Trans3D("View", *PH_Physics3D_Shader);
	Uni_ViewDepth = new Uniform::Depth("Depth", *PH_Physics3D_Shader);

	PH_Physics3D_Shader -> Use();
	Uni_ViewDepth -> PutData(ViewDepth);

	CL_Init();

	std::cout << "Init 1\n";
}
void Free()
{
	std::cout << "Free 0\n";

	delete PH_Texture;
	delete PH;

	delete PH_Physics3D_BufferArray;
	delete PH_Physics3D_Shader;
	delete Uni_ViewPortSizeRatio;
	delete Uni_ViewTrans;
	delete Uni_ViewDepth;

	CL_Free();

	std::cout << "Free 1\n";
}
void Frame(double timeDelta)
{
	PH_Physics3D_Shader -> Use();

	if (win -> IsCursorLocked())
	{
		ViewTrans.TransformFlatX(win -> MoveFromKeys(20.0f * timeDelta), win -> SpinFromCursor(0.2f * timeDelta));
	}
	ViewTrans.Rot.CalcBack();
	Point2D cursor = win -> CursorCentered();
	ViewRay_GPU_Ptr -> Pos = ViewTrans.Pos;
	ViewRay_GPU_Ptr -> Dir = ViewTrans.Rot.rotate(Point3D(cursor.X, cursor.Y, 1));
	Uni_ViewTrans -> PutData(ViewTrans);

	if (glfwGetMouseButton(win -> win, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		CL_Run_GravRay();
	}

	CL_Run_Keep();
	CL_Run_Look();
	CL_Run_Move();
	cl::finish();

	PH_Physics3D_BufferArray -> BindInst((const Physics3D_InstData *)Physics3D_GPU_Ptr, EntityCount);
	PH_Texture -> Bind();
	PH_Physics3D_BufferArray -> Draw();
}
void Resize(const SizeRatio2D & ViewPortSizeRatio)
{
	PH_Physics3D_Shader -> Use();
	Uni_ViewPortSizeRatio -> PutData(ViewPortSizeRatio);
}



int main()
{
	if (glfwInit() == 0)
	{
		std::cout << "Init Failed\n";
		return -1;
	}



	try
	{
		win = new Window(640, 480);
		win -> InitFunc = Init;
		win -> FrameFunc = Frame;
		win -> FreeFunc = Free;
		win -> ResizeFunc = Resize;
	}
	catch (std::exception & ex)
	{
		std::cout << "exception: " << ex.what() << "\n";
	}
	catch (const char * err)
	{
		std::cerr << "String Error: "<< err << "\n";
		glfwTerminate();
		return -1;
	}
	catch (...)
	{
		std::cerr << "Unknown Error" << "\n";
		glfwTerminate();
		return -1;
	}

	win -> DefaultColor = Color(0.125f, 0.0f, 0.0f);

	ViewTrans = Trans3D(Point3D(0, 0, 0), Angle3D(0, 0, 0));
	ViewDepth = Depth();
	ViewDepth.Factors = DepthFactors(0.1f, 1000.0f);
	ViewDepth.Range = Range(0.8f, 1.0f);
	ViewDepth.Color = win -> DefaultColor;

	std::cout << "Count: " << EntityCount << "\n";

	std::cout << "++++ Run\n";
	win -> Run();
	std::cout << "---- Run\n";



	delete win;



	glfwTerminate();
	std::cout << "main() return";
	return 0;
}