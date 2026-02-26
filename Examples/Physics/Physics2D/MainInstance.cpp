#include "Physics2D/MainInstance.hpp"

#include "PolyGon/Data.hpp"
#include "ValueType/AxisBox2D.hpp"
#include "DataShow.hpp"



Physics2D::MainInstance::~MainInstance()
{ }
Physics2D::MainInstance::MainInstance()
	: PolyGon(new ::PolyGon())
	, WireFrame(new ::WireFrame2D())
	, WireFrameBox(new ::WireFrame2D())
//	, Instances(new EntryContainer::Binary<Physics2D::Inst::Data>())
	, PolyGon_Instances(new EntryContainer::Binary<Physics2D::Inst::Data>())
	, WireFrame_Instances(new EntryContainer::Binary<Physics2D::Inst::Data>())
	, WireFrameBox_Instances(new EntryContainer::Binary<Physics2D::Inst::Data>())
	, PolyGon_Buffer(GL::DrawMode::Triangles)
	, WireFrame_Buffer(GL::DrawMode::Lines)
	, WireFrameBox_Buffer(GL::DrawMode::Lines)
{
	{
		PolyGon_Buffer.Main.Pos.Change(0);
		PolyGon_Buffer.Main.Col.Change(1);
		PolyGon_Buffer.Inst.Now.Pos.Change(2);
		PolyGon_Buffer.Inst.Now.Rot.Change(3, 4);
		PolyGon_Buffer.Create();
	}
	{
		WireFrame_Buffer.Main.Pos.Change(0);
		WireFrame_Buffer.Main.Col.Change(1);
		WireFrame_Buffer.Inst.Now.Pos.Change(2);
		WireFrame_Buffer.Inst.Now.Rot.Change(3, 4);
		WireFrame_Buffer.Create();
	}
	{
		WireFrameBox_Buffer.Main.Pos.Change(0);
		WireFrameBox_Buffer.Main.Col.Change(1);
		WireFrameBox_Buffer.Inst.Now.Pos.Change(2);
		WireFrameBox_Buffer.Inst.Now.Rot.Change(3, 4);
		WireFrameBox_Buffer.Create();
	}
}
Physics2D::MainInstance::MainInstance(const MainInstance & other)
	: PolyGon(other.PolyGon)
	, WireFrame(other.WireFrame)
	, WireFrameBox(other.WireFrameBox)
//	, Instances(other.Instances)
	, PolyGon_Instances(other.PolyGon_Instances)
	, WireFrame_Instances(other.WireFrame_Instances)
	, WireFrameBox_Instances(other.WireFrameBox_Instances)
	, PolyGon_Buffer(other.PolyGon_Buffer)
	, WireFrame_Buffer(other.WireFrame_Buffer)
	, WireFrameBox_Buffer(other.WireFrameBox_Buffer)
{ }
Physics2D::MainInstance & Physics2D::MainInstance::operator=(const MainInstance & other)
{
	PolyGon = other.PolyGon;
	WireFrame = other.WireFrame;
	WireFrameBox = other.WireFrameBox;
//	Instances = other.Instances;
	PolyGon_Instances = other.PolyGon_Instances;
	WireFrame_Instances = other.WireFrame_Instances;
	WireFrameBox_Instances = other.WireFrameBox_Instances;
	PolyGon_Buffer = other.PolyGon_Buffer;
	WireFrame_Buffer = other.WireFrame_Buffer;
	WireFrameBox_Buffer = other.WireFrameBox_Buffer;
	return *this;
}



void Physics2D::MainInstance::Dispose()
{
	delete PolyGon;
	delete WireFrame;
	delete WireFrameBox;
//	delete Instances;
	delete PolyGon_Instances;
	delete WireFrame_Instances;
	delete WireFrameBox_Instances;
	PolyGon_Buffer.Delete();
	WireFrame_Buffer.Delete();
	WireFrameBox_Buffer.Delete();
}



void Physics2D::MainInstance::UpdateMain()
{
	{
		Container::Pointer<PolyGonGraphics::Data> data = PolyGon -> ToMainData();
		PolyGon_Buffer.Main.Change(data);
		data.Delete();
	}
	{
		WireFrame -> Clear();
		ColorF4 col;
		for (unsigned int i = 0; i < PolyGon -> Corners.Count(); i++)
		{
			col = PolyGon -> Corners[i].Col;
			col.R = 1.0f - col.R;
			col.G = 1.0f - col.G;
			col.B = 1.0f - col.B;
			WireFrame -> Insert_Corner(PolyGon -> Corners[i].Pos, col);
		}
		for (unsigned int i = 0; i < PolyGon -> Sides.Count(); i++)
		{
			WireFrame -> Insert_Side(PolyGon -> Sides[i].Corner0.Udx, PolyGon -> Sides[i].Corner1.Udx);
			WireFrame -> Insert_Side(PolyGon -> Sides[i].Corner1.Udx, PolyGon -> Sides[i].Corner2.Udx);
			WireFrame -> Insert_Side(PolyGon -> Sides[i].Corner2.Udx, PolyGon -> Sides[i].Corner0.Udx);
		}
		WireFrame_Buffer.Main.Change(WireFrame -> Corners);
		WireFrame_Buffer.Elem.Change(WireFrame -> Sides, 2);
	}
	{
		AxisBox2D box = PolyGon -> ToAxisBox();
		box.Min -= 0.01f;
		box.Max += 0.01f;
		WireFrameBox -> Clear();
		WireFrameBox -> Insert_Box(box, ColorF4());
		WireFrameBox_Buffer.Main.Change(WireFrameBox -> Corners);
		WireFrameBox_Buffer.Elem.Change(WireFrameBox -> Sides, 2);
	}
}
void Physics2D::MainInstance::UpdateInst()
{
//	PolyGon_Buffer.Inst.Change(*Instances);
//	WireFrame_Buffer.Inst.Change(*Instances);
//	WireFrameBox_Buffer.Inst.Change(*Instances);

	PolyGon_Instances -> CompactHere();
	WireFrame_Instances -> CompactHere();
	WireFrameBox_Instances -> CompactHere();

	PolyGon_Buffer.Inst.Change(*PolyGon_Instances);
	WireFrame_Buffer.Inst.Change(*WireFrame_Instances);
	WireFrameBox_Buffer.Inst.Change(*WireFrameBox_Instances);
}
