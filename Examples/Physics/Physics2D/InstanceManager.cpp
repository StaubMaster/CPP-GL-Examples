#include "Physics2D/InstanceManager.hpp"
#include "Physics2D/Manager.hpp"
#include "Physics2D/Object.hpp"

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
	, Buffer_PolyGon(GL::DrawMode::Triangles)
	, Buffer_WireFrame(GL::DrawMode::Lines)
	, Buffer_WireFrameBox(GL::DrawMode::Lines)
{
	IntData.Mass = 1.0f;
}
Physics2D::InstanceManager::InstanceManager(const InstanceManager & other)
	: Manager(other.Manager)
	, PolyGon(other.PolyGon)
	, WireFrame(other.WireFrame)
	, WireFrameBox(other.WireFrameBox)
	, Buffer_PolyGon(other.Buffer_PolyGon)
	, Buffer_WireFrame(other.Buffer_WireFrame)
	, Buffer_WireFrameBox(other.Buffer_WireFrameBox)
	, IntData(other.IntData)
{ }
Physics2D::InstanceManager & Physics2D::InstanceManager::operator=(const InstanceManager & other)
{
	Manager = other.Manager;
	PolyGon = other.PolyGon;
	WireFrame = other.WireFrame;
	WireFrameBox = other.WireFrameBox;
	Buffer_PolyGon = other.Buffer_PolyGon;
	Buffer_WireFrame = other.Buffer_WireFrame;
	Buffer_WireFrameBox = other.Buffer_WireFrameBox;
	IntData = other.IntData;
	return *this;
}



void Physics2D::InstanceManager::Dispose()
{
	delete PolyGon;
	delete WireFrame;
	delete WireFrameBox;
}



static void Calculate_Area(const PolyGon & polygon, Physics2D::IntrinsicData & IntData)
{
	unsigned int n = polygon.Corners.Count();
	IntData.Area = 0.0f;
	for (unsigned int i = 0; i < n; i++)
	{
		Point2D p0;
		Point2D p1;
		if (i == 0)
		{
			p0 = polygon.Corners[n - 1].Pos;
			p1 = polygon.Corners[0 - 0].Pos;
		}
		else
		{
			p0 = polygon.Corners[i - 1].Pos;
			p1 = polygon.Corners[i - 0].Pos;
		}
		float area = Point2D::cross(p0, p1);
		IntData.Area += area;
	}
	IntData.Area *= (1.0 / 2.0f);
}
static void Calculate_CenterOfMass(const PolyGon & polygon, Physics2D::IntrinsicData & IntData)
{
	unsigned int n = polygon.Corners.Count();
	IntData.CenterOfMass = Point2D();
	for (unsigned int i = 0; i < n; i++)
	{
		Point2D p0;
		Point2D p1;
		if (i == 0)
		{
			p0 = polygon.Corners[n - 1].Pos;
			p1 = polygon.Corners[0 - 0].Pos;
		}
		else
		{
			p0 = polygon.Corners[i - 1].Pos;
			p1 = polygon.Corners[i - 0].Pos;
		}
		float area = Point2D::cross(p0, p1);
		IntData.CenterOfMass += (p0 + p1) * area;
	}
	IntData.CenterOfMass *= (1.0 / (6.0f * IntData.Area));
}
static void Calculate_MomentOfInertia(const PolyGon & polygon, Physics2D::IntrinsicData & IntData)
{
	unsigned int n = polygon.Corners.Count();
	/* Moment of Inertia of Triangle
		I = (1/6) * m * ((P ∙ P) + (P ∙ Q) + (Q ∙ Q))
		m = ρ * A
		A = (1/2) * (P × Q)
	*/
	IntData.MomentOfInertia = 0.0f;
	for (unsigned int i = 0; i < n; i++)
	{
		Point2D p0;
		Point2D p1;
		if (i == 0)
		{
			p0 = polygon.Corners[n - 1].Pos;
			p1 = polygon.Corners[0 - 0].Pos;
		}
		else
		{
			p0 = polygon.Corners[i - 1].Pos;
			p1 = polygon.Corners[i - 0].Pos;
		}
		//p0 = p0 - IntData.CenterOfMass;
		//p1 = p1 - IntData.CenterOfMass;
		float area = Point2D::cross(p0, p1);
		float moment_of_inertia_of_triangle = 0.0f;
		moment_of_inertia_of_triangle += Point2D::dot(p0, p0);
		moment_of_inertia_of_triangle += Point2D::dot(p0, p1);
		moment_of_inertia_of_triangle += Point2D::dot(p1, p1);
		IntData.MomentOfInertia += area * moment_of_inertia_of_triangle;
	}
	IntData.MomentOfInertia *= ((IntData.Mass / IntData.Area) / 12.0f);
}

void Physics2D::InstanceManager::Changed()
{
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
		/*for (unsigned int i = 0; i < PolyGon -> Sides.Count(); i++)
		{
			WireFrame -> Insert_Side(PolyGon -> Sides[i].Corner0.Udx, PolyGon -> Sides[i].Corner1.Udx);
			WireFrame -> Insert_Side(PolyGon -> Sides[i].Corner1.Udx, PolyGon -> Sides[i].Corner2.Udx);
			WireFrame -> Insert_Side(PolyGon -> Sides[i].Corner2.Udx, PolyGon -> Sides[i].Corner0.Udx);
		}*/

		for (unsigned int i = 0; i < PolyGon -> Corners.Count(); i++)
		{
			if (i == 0)
			{
				WireFrame -> Insert_Side(PolyGon -> Corners.Count() - 1, 0);
			}
			else
			{
				WireFrame -> Insert_Side(i - 1, i - 0);
			}
		}
	}
	{
		AxisBox2D box = PolyGon -> ToAxisBox();
		box.Min -= 0.01f;
		box.Max += 0.01f;
		WireFrameBox -> Clear();
		WireFrameBox -> Insert_Box(box, ColorF4());
	}
	{
		Calculate_Area(*PolyGon, IntData);
		Calculate_CenterOfMass(*PolyGon, IntData);
		Calculate_MomentOfInertia(*PolyGon, IntData);

		{
			AxisBox2D box = PolyGon -> ToAxisBox();
			Point2D size = box.Size();
			// Box Center
			// Ic = (1/12) * m * (w^2 + h^2)
			IntData.BoxCMomentOfInertia = (IntData.Mass / 12.0f) * ((size.X * size.X) + (size.Y * size.Y));
			// Box Side W Middle
			// Ic = (1/12) * m * (w^2 + 4 * h^2)
			IntData.BoxWMomentOfInertia = (IntData.Mass / 12.0f) * ((size.X * size.X) + 4 * (size.Y * size.Y));
			// Box Side H Middle
			// Ic = (1/12) * m * (4 * w^2 + h^2)
			IntData.BoxHMomentOfInertia = (IntData.Mass / 12.0f) * (4 * (size.X * size.X) + (size.Y * size.Y));
		}
	}
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
{
	{
		Buffer_PolyGon.Main.ChangeAttributeBinding();
		Buffer_PolyGon.Inst.ChangeAttributeBinding();
	}
	{
		Buffer_WireFrame.Main.ChangeAttributeBinding();
		Buffer_WireFrame.Inst.ChangeAttributeBinding();
	}
	{
		Buffer_WireFrameBox.Main.ChangeAttributeBinding();
		Buffer_WireFrameBox.Inst.ChangeAttributeBinding();
	}
}

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
		Buffer_WireFrame.Main.Change(WireFrame -> Corners);
		Buffer_WireFrame.Elem.Change(WireFrame -> Sides, 2);
	}
	{
		Buffer_WireFrameBox.Main.Change(WireFrameBox -> Corners);
		Buffer_WireFrameBox.Elem.Change(WireFrameBox -> Sides, 2);
	}
}
void Physics2D::InstanceManager::UpdateInst()
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

	Container::Fixed<Physics2D::Inst::Data> Data_PolyGon(Count_PolyGon);
	Container::Fixed<Physics2D::Inst::Data> Data_WireFrame(Count_WireFrame);
	Container::Fixed<Physics2D::Inst::Data> Data_WireFrameBox(Count_WireFrameBox);
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		if (Objects[i] == nullptr) { continue; }
		Physics2D::Object & obj = *Objects[i];
		if (obj.InstanceManager == this)
		{
			if (obj.DrawPolyGon) { Data_PolyGon.Insert(obj.Data); }
			if (obj.DrawWireFrame) { Data_WireFrame.Insert(obj.Data); }
			if (obj.DrawWireFrameBox) { Data_WireFrameBox.Insert(obj.Data); }
		}
	}

	Buffer_PolyGon.Inst.Change(Data_PolyGon);
	Buffer_WireFrame.Inst.Change(Data_WireFrame);
	Buffer_WireFrameBox.Inst.Change(Data_WireFrameBox);
}
