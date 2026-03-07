#include "Physics2D/Object.hpp"
#include "Physics2D/InstanceManager.hpp"
#include "Physics2D/Manager.hpp"

#include "PolyGon/PolyGon.hpp"
#include "PolyGon/Data.hpp"



bool Physics2D::Object::IsValid() const { return (InstanceManager != nullptr); }
const ::PolyGon * Physics2D::Object::PolyGon() const { if (IsValid()) { return (InstanceManager -> PolyGon); } return nullptr; }



void Physics2D::Object::UpdateEntrys()
{
	if (Data_PolyGon.Is()) { (*Data_PolyGon) = Data; }
	if (Data_WireFrame.Is()) { (*Data_WireFrame) = Data; }
	if (Data_WireFrameBox.Is()) { (*Data_WireFrameBox) = Data; }
	if (Data_Arrows.Is())
	{
		Point2D now = Data.Now.Pos;
		Point2D vel = Data.Vel.Pos;
		Data_Arrows[0] = Arrow2D::Inst::Data(now, now + vel, 10, ColorF4(0.5f, 0.5f, 1.0f));
		/*for (unsigned int j = 0; j < Physics2D_Objects[i].CornerCount(); j++)
		{
			Point2D p = Physics2D_Objects[i].CornerFromIndex(j);
			Point2D now = Physics2D_Objects[i].AbsolutePositionOf(p);
			Point2D vel = Physics2D_Objects[i].AbsoluteVelocityOf(p);
			data.Insert(Arrow2D::Inst::Data(now, now + vel, 10, ColorF4(0.5f, 1.0f, 0.5f)));
			vel -= Physics2D_Objects[i].Data.Vel.Pos;
			data.Insert(Arrow2D::Inst::Data(now, now + vel, 10, ColorF4(1.0f, 0.5f, 0.5f)));
		}*/
	}
}



void Physics2D::Object::Show_PolyGon()
{
	if (!Data_PolyGon.Is())
	{
		Data_PolyGon.Allocate(*(*InstanceManager).Instances_PolyGon, 1);
	}
}
void Physics2D::Object::Show_WireFrame()
{
	if (!Data_WireFrame.Is())
	{
		Data_WireFrame.Allocate(*(*InstanceManager).Instances_WireFrame, 1);
	}
}
void Physics2D::Object::Show_WireFrameBox()
{
	if (!Data_WireFrameBox.Is())
	{
		Data_WireFrameBox.Allocate(*(*InstanceManager).Instances_WireFrameBox, 1);
	}
}
void Physics2D::Object::Show_Arrows()
{
	if (!Data_Arrows.Is())
	{
		Data_Arrows.Allocate((*(*InstanceManager).Manager).Instances_Arrow, 1);
	}
}

void Physics2D::Object::Hide_PolyGon()
{
	if (Data_PolyGon.Is())
	{
		Data_PolyGon.Dispose();
	}
}
void Physics2D::Object::Hide_WireFrame()
{
	if (Data_WireFrame.Is())
	{
		Data_WireFrame.Dispose();
	}
}
void Physics2D::Object::Hide_WireFrameBox()
{
	if (Data_WireFrameBox.Is())
	{
		Data_WireFrameBox.Dispose();
	}
}
void Physics2D::Object::Hide_Arrows()
{
	if (Data_Arrows.Is())
	{
		Data_Arrows.Dispose();
	}
}

unsigned int Physics2D::Object::CornerCount() const { return (PolyGon() -> Corners.Count()); }
unsigned int Physics2D::Object::SideCount() const { return (PolyGon() -> Sides.Count()); }

Point2D Physics2D::Object::CornerFromIndex(unsigned int idx) const { return PolyGon() -> Corners[idx].Pos; }

Point2D Physics2D::Object::RelativePositionOf(Point2D p) const { return Data.Now / p; }
Point2D Physics2D::Object::AbsolutePositionOf(Point2D p) const { return Data.Now * p; }
Point2D Physics2D::Object::AbsoluteVelocityOf(Point2D p) const
{
	Point2D perp = p.perpendicular0().normalize();
	perp = Data.Now.Rot / (perp);
	// use Angle stuff instead ?

	Point2D v;
	v = perp * (Data.Vel.Rot.Ang.ToRadians() * p.length());
	v += Data.Vel.Pos;

	return v;
}





Physics2D::Object::~Object()
{ }
Physics2D::Object::Object()
	: InstanceManager(nullptr)
	, Data_PolyGon()
	, Data_WireFrame()
	, Data_WireFrameBox()
	, Data_Arrows()
	, Data()
	, IsTangible(true)
	, IsStatic(true)
	, Mass(0.0f)
{ }
Physics2D::Object::Object(const Object & other)
	: InstanceManager(other.InstanceManager)
	, Data_PolyGon(other.Data_PolyGon)
	, Data_WireFrame(other.Data_WireFrame)
	, Data_WireFrameBox(other.Data_WireFrameBox)
	, Data_Arrows(other.Data_Arrows)
	, Data(other.Data)
	, IsTangible(other.IsTangible)
	, IsStatic(other.IsStatic)
	, Mass(other.Mass)
{ }
Physics2D::Object & Physics2D::Object::operator=(const Object & other)
{
	InstanceManager = other.InstanceManager;
	Data_PolyGon = other.Data_PolyGon;
	Data_WireFrame = other.Data_WireFrame;
	Data_WireFrameBox = other.Data_WireFrameBox;
	Data_Arrows = other.Data_Arrows;
	Data = other.Data;
	IsTangible = other.IsTangible;
	IsStatic = other.IsStatic;
	Mass = other.Mass;
	return *this;
}



Physics2D::Object::Object(Physics2D::InstanceManager & inst_manager, bool is_static)
	: InstanceManager(&inst_manager)
	, Data_PolyGon(*(*InstanceManager).Instances_PolyGon, 1)
	, Data_WireFrame()
	, Data_WireFrameBox()
	, Data_Arrows()
	, Data()
	, IsTangible(true)
	, IsStatic(is_static)
	, Mass(1.0f)
{ }
Physics2D::Object::Object(Physics2D::InstanceManager & inst_manager, Trans2D now, bool is_static)
	: InstanceManager(&inst_manager)
	, Data_PolyGon(*(*InstanceManager).Instances_PolyGon, 1)
	, Data_WireFrame()
	, Data_WireFrameBox()
	, Data_Arrows()
	, Data(now)
	, IsTangible(true)
	, IsStatic(is_static)
	, Mass(1.0f)
{ }
Physics2D::Object::Object(Physics2D::InstanceManager & inst_manager, Trans2D now, Trans2D vel, bool is_static)
	: InstanceManager(&inst_manager)
	, Data_PolyGon(*(*InstanceManager).Instances_PolyGon, 1)
	, Data_WireFrame()
	, Data_WireFrameBox()
	, Data_Arrows()
	, Data(now, vel)
	, IsTangible(true)
	, IsStatic(is_static)
	, Mass(1.0f)
{ }





bool Physics2D::Object::IsContaining(Point2D p) const { return PolyGon() -> IsContaining(Data.Now / p); }
