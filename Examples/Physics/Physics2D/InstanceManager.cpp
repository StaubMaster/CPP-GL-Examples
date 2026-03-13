#include "Physics2D/InstanceManager.hpp"

#include "PolyGon/Data.hpp"
#include "ValueType/AxisBox2D.hpp"
#include "DataShow.hpp"





Physics2D::InstanceManager * Physics2D::InstanceManager::CurrentPointer = nullptr;
Physics2D::InstanceManager & Physics2D::InstanceManager::Current() { return *CurrentPointer; }
bool Physics2D::InstanceManager::CheckCurrent() { return (Physics2D::InstanceManager::CurrentPointer != nullptr); }
void Physics2D::InstanceManager::ClearCurrent() { Physics2D::InstanceManager::CurrentPointer = nullptr; }
bool Physics2D::InstanceManager::IsCurrent() const { return (Physics2D::InstanceManager::CurrentPointer == this); }
void Physics2D::InstanceManager::MakeCurrent() { Physics2D::InstanceManager::CurrentPointer = this; }





Physics2D::InstanceManager::~InstanceManager()
{ }
Physics2D::InstanceManager::InstanceManager()
	: Manager(nullptr)
	, PolyGon(new ::PolyGon())
	, WireFrame(new ::WireFrame2D())
	, WireFrameBox(new ::WireFrame2D())
//	, Instances_PolyGon(new EntryContainer::Binary<Physics2D::Inst::Data>())
//	, Instances_WireFrame(new EntryContainer::Binary<Physics2D::Inst::Data>())
//	, Instances_WireFrameBox(new EntryContainer::Binary<Physics2D::Inst::Data>())
	, Buffer_PolyGon(GL::DrawMode::Triangles)
	, Buffer_WireFrame(GL::DrawMode::Lines)
	, Buffer_WireFrameBox(GL::DrawMode::Lines)
{ }
Physics2D::InstanceManager::InstanceManager(const InstanceManager & other)
	: Manager(other.Manager)
	, PolyGon(other.PolyGon)
	, WireFrame(other.WireFrame)
	, WireFrameBox(other.WireFrameBox)
//	, Instances_PolyGon(other.Instances_PolyGon)
//	, Instances_WireFrame(other.Instances_WireFrame)
//	, Instances_WireFrameBox(other.Instances_WireFrameBox)
	, Buffer_PolyGon(other.Buffer_PolyGon)
	, Buffer_WireFrame(other.Buffer_WireFrame)
	, Buffer_WireFrameBox(other.Buffer_WireFrameBox)
{ }
Physics2D::InstanceManager & Physics2D::InstanceManager::operator=(const InstanceManager & other)
{
	Manager = other.Manager;
	PolyGon = other.PolyGon;
	WireFrame = other.WireFrame;
	WireFrameBox = other.WireFrameBox;
//	Instances_PolyGon = other.Instances_PolyGon;
//	Instances_WireFrame = other.Instances_WireFrame;
//	Instances_WireFrameBox = other.Instances_WireFrameBox;
	Buffer_PolyGon = other.Buffer_PolyGon;
	Buffer_WireFrame = other.Buffer_WireFrame;
	Buffer_WireFrameBox = other.Buffer_WireFrameBox;
	return *this;
}



void Physics2D::InstanceManager::Dispose()
{
	delete PolyGon;
	delete WireFrame;
	delete WireFrameBox;

//	delete Instances_PolyGon;
//	delete Instances_WireFrame;
//	delete Instances_WireFrameBox;
}



void Physics2D::InstanceManager::InitExternal()
{
	{
		Buffer_PolyGon.Main.Pos.Change(0);
		Buffer_PolyGon.Main.Col.Change(1);
		Buffer_PolyGon.Inst.Now.Pos.Change(2);
		Buffer_PolyGon.Inst.Now.Rot.Change(3, 4);
	}
	{
		Buffer_WireFrame.Main.Pos.Change(0);
		Buffer_WireFrame.Main.Col.Change(1);
		Buffer_WireFrame.Inst.Now.Pos.Change(2);
		Buffer_WireFrame.Inst.Now.Rot.Change(3, 4);
	}
	{
		Buffer_WireFrameBox.Main.Pos.Change(0);
		Buffer_WireFrameBox.Main.Col.Change(1);
		Buffer_WireFrameBox.Inst.Now.Pos.Change(2);
		Buffer_WireFrameBox.Inst.Now.Rot.Change(3, 4);
	}
}
void Physics2D::InstanceManager::InitInternal()
{ }

void Physics2D::InstanceManager::GraphicsCreate()
{
	Buffer_PolyGon.Create();
	Buffer_WireFrame.Create();
	Buffer_WireFrameBox.Create();
}
void Physics2D::InstanceManager::GraphicsDelete()
{
	Buffer_PolyGon.Delete();
	Buffer_WireFrame.Delete();
	Buffer_WireFrameBox.Delete();
}



void Physics2D::InstanceManager::UpdateMain()
{
	{
		Container::Pointer<PolyGonGraphics::Data> data = PolyGon -> ToMainData();
		Buffer_PolyGon.Main.Change(data);
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
		Buffer_WireFrame.Main.Change(WireFrame -> Corners);
		Buffer_WireFrame.Elem.Change(WireFrame -> Sides, 2);
	}
	{
		AxisBox2D box = PolyGon -> ToAxisBox();
		box.Min -= 0.01f;
		box.Max += 0.01f;
		WireFrameBox -> Clear();
		WireFrameBox -> Insert_Box(box, ColorF4());
		Buffer_WireFrameBox.Main.Change(WireFrameBox -> Corners);
		Buffer_WireFrameBox.Elem.Change(WireFrameBox -> Sides, 2);
	}
}
void Physics2D::InstanceManager::UpdateInst()
{
//	Buffer_PolyGon.Inst.Change(*Instances);
//	Buffer_WireFrame.Inst.Change(*Instances);
//	Buffer_WireFrameBox.Inst.Change(*Instances);

//	Instances_PolyGon -> CompactHere();
//	Instances_WireFrame -> CompactHere();
//	Instances_WireFrameBox -> CompactHere();

//	Buffer_PolyGon.Inst.Change(*Instances_PolyGon);
//	Buffer_WireFrame.Inst.Change(*Instances_WireFrame);
//	Buffer_WireFrameBox.Inst.Change(*Instances_WireFrameBox);
}
