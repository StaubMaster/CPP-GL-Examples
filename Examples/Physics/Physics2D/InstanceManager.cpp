#include "Physics2D/InstanceManager.hpp"
#include "Physics2D/Manager.hpp"
#include "Physics2D/Object.hpp"

#include "ValueType/AxisBox2D.hpp"
#include "DataShow.hpp"





Physics2D::InstanceManager * Physics2D::InstanceManager::CurrentPointer = nullptr;
Physics2D::InstanceManager & Physics2D::InstanceManager::Current() { return *CurrentPointer; }
bool Physics2D::InstanceManager::CheckCurrent() { return (Physics2D::InstanceManager::CurrentPointer != nullptr); }
void Physics2D::InstanceManager::ClearCurrent() { Physics2D::InstanceManager::CurrentPointer = nullptr; }
bool Physics2D::InstanceManager::IsCurrent() const { return (Physics2D::InstanceManager::CurrentPointer == this); }
void Physics2D::InstanceManager::MakeCurrent() { Physics2D::InstanceManager::CurrentPointer = this; }





Physics2D::InstanceManager::~InstanceManager() { }
Physics2D::InstanceManager::InstanceManager()
	: Manager(nullptr)
	, PolyGon(new ::PolyGon())
	, Bound(new ::PolyGon())
	, Buffer_PolyGon_Full(GL::DrawMode::Triangles)
	, Buffer_PolyGon_Wire(GL::DrawMode::Lines, 2)
	, Buffer_Bound(GL::DrawMode::Lines, 2)
{
	IntData.Density = 1.0f;
	IntData.Restitution = 1.0f;
}
Physics2D::InstanceManager::InstanceManager(const InstanceManager & other)
	: Manager(other.Manager)
	, PolyGon(other.PolyGon)
	, Bound(other.Bound)
	, Buffer_PolyGon_Full(other.Buffer_PolyGon_Full)
	, Buffer_PolyGon_Wire(other.Buffer_PolyGon_Wire)
	, Buffer_Bound(other.Buffer_Bound)
	, IntData(other.IntData)
{ }
Physics2D::InstanceManager & Physics2D::InstanceManager::operator=(const InstanceManager & other)
{
	Manager = other.Manager;
	PolyGon = other.PolyGon;
	Bound = other.Bound;
	Buffer_PolyGon_Full = other.Buffer_PolyGon_Full;
	Buffer_PolyGon_Wire = other.Buffer_PolyGon_Wire;
	Buffer_Bound = other.Buffer_Bound;
	IntData = other.IntData;
	return *this;
}

void Physics2D::InstanceManager::Dispose()
{
	delete PolyGon;
	delete Bound;
}



void Physics2D::InstanceManager::Changed()
{
	{
		AxisBox2D box = PolyGon -> ToAxisBox();
		box.Min -= 0.01f;
		box.Max += 0.01f;

		ColorF4 col(1, 1, 1);
		Bound -> Clear();
		Bound -> NewCorner(Point2D(box.Min.X, box.Min.Y), col);
		Bound -> NewCorner(Point2D(box.Max.X, box.Min.Y), col);
		Bound -> NewCorner(Point2D(box.Max.X, box.Max.Y), col);
		Bound -> NewCorner(Point2D(box.Min.X, box.Max.Y), col);
	}
	{
		IntData.Calculate(*PolyGon);
	}
}



void Physics2D::InstanceManager::GraphicsInitExternal()
{
	{
		Buffer_PolyGon_Full.Main.Pos.Change(0);
		Buffer_PolyGon_Full.Main.Col.Change(1);
		Buffer_PolyGon_Full.Inst.Now.Pos.Change(2);
		Buffer_PolyGon_Full.Inst.Now.Rot.Change(3, 4);
	}
	{
		Buffer_PolyGon_Wire.Main.Pos.Change(0);
		Buffer_PolyGon_Wire.Main.Col.Change(1);
		Buffer_PolyGon_Wire.Inst.Now.Pos.Change(2);
		Buffer_PolyGon_Wire.Inst.Now.Rot.Change(3, 4);
	}
	{
		Buffer_Bound.Main.Pos.Change(0);
		Buffer_Bound.Main.Col.Change(1);
		Buffer_Bound.Inst.Now.Pos.Change(2);
		Buffer_Bound.Inst.Now.Rot.Change(3, 4);
	}
}
void Physics2D::InstanceManager::GraphicsInitInternal()
{
	{
		Buffer_PolyGon_Full.Main.ChangeAttributeBinding();
		Buffer_PolyGon_Full.Inst.ChangeAttributeBinding();
	}
	{
		Buffer_PolyGon_Wire.Main.ChangeAttributeBinding();
		Buffer_PolyGon_Wire.Inst.ChangeAttributeBinding();
	}
	{
		Buffer_Bound.Main.ChangeAttributeBinding();
		Buffer_Bound.Inst.ChangeAttributeBinding();
	}
}

void Physics2D::InstanceManager::GraphicsCreate()
{
	Buffer_PolyGon_Full.Create();
	Buffer_PolyGon_Wire.Create();
	Buffer_Bound.Create();
}
void Physics2D::InstanceManager::GraphicsDelete()
{
	Buffer_PolyGon_Full.Delete();
	Buffer_PolyGon_Wire.Delete();
	Buffer_Bound.Delete();
}

void Physics2D::InstanceManager::GraphicsUpdateMain()
{
	{
		Container::Pointer<PolyGonFull::Main::Data> data = PolyGon -> ToFullData();
		Buffer_PolyGon_Full.Main.Change(data);
		data.Delete();
	}
	{
		// Corner Color should be inverted
		Buffer_PolyGon_Wire.Main.Change(PolyGon -> Corners);
		Buffer_PolyGon_Wire.Elem.Change(PolyGon -> Edges);
	}
	{
		Buffer_Bound.Main.Change(Bound -> Corners);
		Buffer_Bound.Elem.Change(Bound -> Edges);
	}
}
void Physics2D::InstanceManager::GraphicsUpdateInst()
{
	Container::Binary<Physics2D::Object*> & Objects = Manager -> Objects;

	unsigned int Count_PolyGon = 0;
	unsigned int Count_WireFrame = 0;
	unsigned int Count_WireFrameBox = 0;
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		if (Objects[i] == nullptr) { continue; }
		Physics2D::Object & obj = *Objects[i];
		if (obj.InstanceManager == this)
		{
			if (obj.DrawPolyGon) { Count_PolyGon++; }
			if (obj.DrawWireFrame) { Count_WireFrame++; }
			if (obj.DrawWireFrameBox) { Count_WireFrameBox++; }
		}
	}

	Container::Fixed<Trans2D> Data_PolyGon(Count_PolyGon);
	Container::Fixed<Trans2D> Data_WireFrame(Count_WireFrame);
	Container::Fixed<Trans2D> Data_WireFrameBox(Count_WireFrameBox);
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		if (Objects[i] == nullptr) { continue; }
		Physics2D::Object & obj = *Objects[i];
		if (obj.InstanceManager == this)
		{
			//if (obj.DrawPolyGon) { Data_PolyGon.Insert(obj.Data); }
			//if (obj.DrawWireFrame) { Data_WireFrame.Insert(obj.Data); }
			//if (obj.DrawWireFrameBox) { Data_WireFrameBox.Insert(obj.Data); }
			if (obj.DrawPolyGon) { Data_PolyGon.Insert(obj.ExtData.Now); }
			if (obj.DrawWireFrame) { Data_WireFrame.Insert(obj.ExtData.Now); }
			if (obj.DrawWireFrameBox) { Data_WireFrameBox.Insert(obj.ExtData.Now); }
		}
	}

	Buffer_PolyGon_Full.Inst.Change(Data_PolyGon);
	Buffer_PolyGon_Wire.Inst.Change(Data_WireFrame);
	Buffer_Bound.Inst.Change(Data_WireFrameBox);
}
