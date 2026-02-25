#include "Physics2D/MainInstance.hpp"

#include "PolyGon/Data.hpp"
#include "ValueType/AxisBox2D.hpp"
#include "DataShow.hpp"



Physics2D::MainInstance::~MainInstance()
{ }
Physics2D::MainInstance::MainInstance()
	: PolyGon(new ::PolyGon())
	, Instances(new EntryContainer::Binary<Physics2D::Inst::Data>())
	, PolyGon_Buffer(GL::DrawMode::Triangles)
	, WireFrame_Buffer(GL::DrawMode::Lines)
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
}
Physics2D::MainInstance::MainInstance(const MainInstance & other)
	: PolyGon(other.PolyGon)
	, Instances(other.Instances)
	, PolyGon_Buffer(other.PolyGon_Buffer)
	, WireFrame_Buffer(other.WireFrame_Buffer)
{ }
Physics2D::MainInstance & Physics2D::MainInstance::operator=(const MainInstance & other)
{
	PolyGon = other.PolyGon;
	Instances = other.Instances;
	PolyGon_Buffer = other.PolyGon_Buffer;
	WireFrame_Buffer = other.WireFrame_Buffer;
	return *this;
}



void Physics2D::MainInstance::Dispose()
{
	PolyGon_Buffer.Delete();
	WireFrame_Buffer.Delete();
	delete PolyGon;
	delete Instances;
}



void Physics2D::MainInstance::UpdateMain()
{
	{
		Container::Pointer<PolyGonGraphics::Data> data = PolyGon -> ToMainData();
		PolyGon_Buffer.Main.Change(data);
		data.Delete();
	}
	{
		AxisBox2D box;
		for (unsigned int i = 0; i < PolyGon -> Corners.Count(); i++)
		{
			box.Consider(PolyGon -> Corners[i].Pos);
		}
		box.Min -= 0.01f;
		box.Max += 0.01f;

		WireFrame.Clear();

		WireFrame.Insert_Corner(Point2D(box.Min.X, box.Min.Y), ColorF4(0, 0, 0));
		WireFrame.Insert_Corner(Point2D(box.Max.X, box.Min.Y), ColorF4(1, 0, 0));
		WireFrame.Insert_Corner(Point2D(box.Max.X, box.Max.Y), ColorF4(0, 1, 0));
		WireFrame.Insert_Corner(Point2D(box.Min.X, box.Max.Y), ColorF4(0, 0, 1));

		WireFrame.Insert_Side(0, 1);
		WireFrame.Insert_Side(1, 2);
		WireFrame.Insert_Side(2, 3);
		WireFrame.Insert_Side(3, 0);

		WireFrame_Buffer.Main.Change(WireFrame.Corners);
		WireFrame_Buffer.Elem.Change(WireFrame.Sides, 2);
	}
}
void Physics2D::MainInstance::UpdateInst()
{
	PolyGon_Buffer.Inst.Change(*Instances);
	WireFrame_Buffer.Inst.Change(*Instances);
}
