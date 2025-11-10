
#include <iostream>
#include "OpenGL/openGL.h"

#include "Debug.hpp"

#include "DataInclude.hpp"
#include "DataShow.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Graphics/Shader/Base.hpp"

#include "Graphics/UniformsInclude.hpp"
#include "Graphics/MultiformsInclude.hpp"

#include "DataStruct/Full/PolyHedra_3D/PolyHedra_3D_Instances.hpp"

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



struct SplineNode3D
{
	Point3D	Pos;
	Point3D	Dir;

	SplineNode3D() { }
	SplineNode3D(Point3D pos, Point3D dir)
	{
		Pos = pos;
		Dir = dir;
	}
};

struct SplineSegment3D
{
	SplineNode3D	Node0;
	SplineNode3D	Node1;
	SplineSegment3D *	Prev;
	SplineSegment3D *	Next;

	float	T;
	float	C;
	float	B;

	SplineSegment3D() { }
	SplineSegment3D(SplineNode3D node0, SplineNode3D node1)
	{
		Node0 = node0;
		Node1 = node1;
		Prev = NULL;
		Next = NULL;

		T = 0;
		C = 0;
		B = 0;
	}

	SplineNode3D	Calculate(float t) const
	{
		LInter linter;
		linter.SetT0(t);

		float Tm = 1 - T;
		float Cm = 1 - C;
		float Cp = 1 + C;
		float Bm = 1 - B;
		float Bp = 1 + B;

		Point3D p[4]
		{
			(Prev -> Node0).Pos,
			Node0.Pos,
			Node1.Pos,
			(Next -> Node1).Pos,
		};

		float f[4]
		{
			linter.GetT1() * linter.GetT1() * linter.GetT1(),
			linter.GetT0() * linter.GetT1() * linter.GetT1() * 3,
			linter.GetT0() * linter.GetT0() * linter.GetT1() * 3,
			linter.GetT0() * linter.GetT0() * linter.GetT0(),
		};

		float m[4]
		{
			(Tm * Cm * Bp) / 2,
			(Tm * Cp * Bm) / 2,
			(Tm * Cp * Bp) / 2,
			(Tm * Cm * Bm) / 2,
		};

		Point3D dir[2]
		{
			((p[1] - p[0]) * m[0]) + ((p[2] - p[1]) * m[1]),
			((p[2] - p[1]) * m[2]) + ((p[3] - p[2]) * m[3]),
		};

		Point3D vals[4]
		{
			p[1],
			p[1] + (dir[0] / 3),
			p[2] - (dir[1] / 3),
			p[2],
		};



		SplineNode3D node;

		node.Pos = Point3D();
		node.Pos = node.Pos + (vals[0] * f[0]);
		node.Pos = node.Pos + (vals[1] * f[1]);
		node.Pos = node.Pos + (vals[2] * f[2]);
		node.Pos = node.Pos + (vals[3] * f[3]);

		node.Dir = (dir[0] * linter.GetT1()) + (dir[1] * linter.GetT0());

		return node;
	}
	SplineNode3D	CalculateLerp(float t) const
	{
		LInter linter;
		linter.SetT1(t);

		SplineNode3D node;

		node.Pos.X = linter.Calc(Node0.Pos.X, Node1.Pos.X);
		node.Pos.Y = linter.Calc(Node0.Pos.Y, Node1.Pos.Y);
		node.Pos.Z = linter.Calc(Node0.Pos.Z, Node1.Pos.Z);

		node.Dir.X = linter.Calc(Node0.Dir.X, Node1.Dir.X);
		node.Dir.Y = linter.Calc(Node0.Dir.Y, Node1.Dir.Y);
		node.Dir.Z = linter.Calc(Node0.Dir.Z, Node1.Dir.Z);

		return node;
	}};

struct SplineCurve3D
{
	SplineSegment3D	* Segments;
	unsigned int SegmentCount;

	SplineCurve3D(SplineNode3D * nodes, unsigned int count, bool closed)
	{
		count--;
		SegmentCount = count;
		if (closed) { SegmentCount++; }
		Segments = new SplineSegment3D[SegmentCount];

		unsigned int min = 0;
		unsigned int max = SegmentCount - 1;

		for (unsigned int i = min; i < max; i++)
		{
			Segments[i] = SplineSegment3D(nodes[i + 0], nodes[i + 1]);
		}
		if (closed)
		{
			Segments[count] = SplineSegment3D(nodes[max], nodes[min]);
		}

		for (unsigned int i = 0; i < SegmentCount; i++)
		{
			if (i == min)
			{ Segments[i].Prev = &Segments[max]; }
			else
			{ Segments[i].Prev = &Segments[i - 1]; }

			if (i == max)
			{ Segments[i].Next = &Segments[min]; }
			else
			{ Segments[i].Next = &Segments[i + 1]; }
		}
	}
	~SplineCurve3D()
	{
		delete [] Segments;
	}

	SplineNode3D	CalculateLerp(float t) const
	{
		//	Modulate t into range [ 0 ; SegmentCount - 1]
		{
			while (t < 0) { t += SegmentCount; }
			while (t > SegmentCount) { t -= SegmentCount; }
		}

		unsigned int idx = t;	//	floors ?
		return Segments[idx].CalculateLerp(t - idx);
	}
	SplineNode3D	Calculate(float t) const
	{
		//	Modulate t into range [ 0 ; SegmentCount - 1]
		{
			while (t < 0) { t += SegmentCount; }
			while (t > SegmentCount) { t -= SegmentCount; }
		}

		unsigned int idx = t;	//	floors ?
		return Segments[idx].Calculate(t - idx);
	}
};

struct SplineObject
{
	unsigned int	Index;
	float			SplineValue;

	SplineObject() { }
	SplineObject(unsigned int idx, float val)
	{
		Index = idx;
		SplineValue = val;
	}
};

SplineCurve3D * Spline;



DirectoryContext ImageDir("./media/Images");
DirectoryContext ShaderDir("./media/Shaders");



Window * win;

Trans3D	ViewTrans;
Depth	ViewDepth;

YMT::PolyHedra * PH;
PolyHedra_3D_Instances * PH_Instances;
ContainerDynamic<SplineObject> Spline_Entrys;
ContainerDynamic<EntryContainerDynamic<Simple3D_InstData>::Entry*> Instance_Entrys;

Shader::Base * PH_Shader;

Uniform::SizeRatio2D * Uni_ViewPortSizeRatio;
Uniform::Trans3D * Uni_View;
Uniform::Depth * Uni_Depth;



void InitGraphics()
{
	PH_Shader = new Shader::Base((const Shader::Code []) {
		Shader::Code::FromFile(ShaderDir.File("PH_S3D.vert")),
		Shader::Code::FromFile(ShaderDir.File("PH_Full.frag"))
	}, 2);

	Uni_ViewPortSizeRatio = new Uniform::SizeRatio2D("ViewPortSizeRatio", *PH_Shader);
	Uni_View = new Uniform::Trans3D("View", *PH_Shader);
	Uni_Depth = new Uniform::Depth("Depth", *PH_Shader);

	PH_Shader -> Use();
	Uni_Depth -> PutData(ViewDepth);
}
void FreeGraphics()
{
	delete PH_Shader;

	delete Uni_ViewPortSizeRatio;
	delete Uni_View;
	delete Uni_Depth;
}



//YMT::PolyHedra::Load(FileContext("../media/YMT/Spline/Drehgestell_Achse.polyhedra.ymt"));
//YMT::PolyHedra::Load(FileContext("../media/YMT/Spline/Drehgestell_Halter.polyhedra.ymt"));	//	Faces wrong way
//YMT::PolyHedra::Load(FileContext("../media/YMT/Spline/Drehgestell_Rahmen.polyhedra.ymt"));	//	Faces Wrong way
//YMT::PolyHedra::Load(FileContext("../media/YMT/Spline/Gleis_Seg.polyhedra.ymt"));				//	Faces Wrong way
//YMT::PolyHedra::Load(FileContext("../media/YMT/Spline/Schienen_Seg.polyhedra.ymt"));			//	Faces Wrong way
//YMT::PolyHedra::Load(FileContext("../media/YMT/Spline/Wagen_Flach.polyhedra.ymt"));			//	Faces Wrong way, some Geometry Wrong
//YMT::PolyHedra::Load(FileContext("../media/YMT/Spline/Wagen_Tief.polyhedra.ymt"));			//	Faces Wrong way, some Geometry Wrong



void InitRun()
{
	InitGraphics();

	Spline = new SplineCurve3D((SplineNode3D []) {
		SplineNode3D(Point3D(+40, +10, -20), Point3D(+1, 0, +1)),
		SplineNode3D(Point3D(+40, -10, +20), Point3D(-1, 0, +1)),
		SplineNode3D(Point3D(-40,   0, +20), Point3D(-1, 0, -1)),
		SplineNode3D(Point3D(-40,   0, -20), Point3D(+1, 0, -1)),
	}, 4, true);

	//PH = YMT::PolyHedra::Cube();
	PH = YMT::PolyHedra::ConeC(8, 0.5f, 2.0f);
	PH_Instances = new PolyHedra_3D_Instances(PH);

	unsigned int idx = Instance_Entrys.Insert(PH_Instances -> Alloc(32));
	for (int i = 0; i < (*Instance_Entrys[idx]).Length; i++)
	{
		Spline_Entrys.Insert(SplineObject(i, (((float)i) / (*Instance_Entrys[idx]).Length) * Spline -> SegmentCount));
	}
}
void FreeRun()
{
	delete PH_Instances;
	delete PH;

	FreeGraphics();
}



void Frame(double timeDelta)
{
	if (win -> IsCursorLocked())
	{
		ViewTrans.TransformFlatX(win -> MoveFromKeys(20.0f * timeDelta), win -> SpinFromCursor(0.2f * timeDelta));
	}
	ViewTrans.Rot.CalcBack();

	for (int i = 0; i < (*Instance_Entrys[0]).Length; i++)
	{
		//SplineNode3D node = Spline -> CalculateLerp(Spline_Entrys[i].SplineValue);
		SplineNode3D node = Spline -> Calculate(Spline_Entrys[i].SplineValue);

		(*Instance_Entrys[0])[i].Trans.Pos = node.Pos;
		(*Instance_Entrys[0])[i].Trans.Rot = Angle3D::FromPoint3D(node.Dir);
		(*Instance_Entrys[0])[i].Trans.Rot.CalcBack();

		Spline_Entrys[i].SplineValue += 0.1f * timeDelta;
	}

	PH_Shader -> Use();
	Uni_View -> PutData(ViewTrans);
	PH_Instances -> Update().Draw();
}

void Resize(int w, int h)
{
	PH_Shader -> Use();
	Uni_ViewPortSizeRatio -> PutData(SizeRatio2D(w, h));
}





int main()
{
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



	Debug::Log << "<<<< Run Window" << Debug::Done;
	win -> Run();
	Debug::Log << ">>>> Run Window" << Debug::Done;



	delete win;

	glfwTerminate();
	std::cout << "main() return";
	return 0;
}


