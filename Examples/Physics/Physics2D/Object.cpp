#include "Physics2D/Object.hpp"
#include "PolyGon/Data.hpp"



bool Physics2D::Object::Valid() const { return (InstanceManager != nullptr); }
const ::PolyGon * Physics2D::Object::PolyGon() const { return (InstanceManager -> PolyGon); }
void Physics2D::Object::Update()
{
	if (Data_PolyGon.Is()) { (*Data_PolyGon) = Data; }
	if (Data_WireFrame.Is()) { (*Data_WireFrame) = Data; }
	if (Data_WireFrameBox.Is()) { (*Data_WireFrameBox) = Data; }
}

const Trans2D & Physics2D::Object::Now() const { return (Data).Now; }
const Trans2D & Physics2D::Object::Vel() const { return (Data).Vel; }

Trans2D & Physics2D::Object::Now() { return (Data).Now; }
Trans2D & Physics2D::Object::Vel() { return (Data).Vel; }

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
		Data_Arrows.Allocate(*(*(*InstanceManager).Manager).Instances_Arrow, 1);
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

Point2D Physics2D::Object::RelativePositionOf(Point2D p) const
{
	const Trans2D & now = Now();
	return now.Rot.rotateFore(p - now.Pos);
}
Point2D Physics2D::Object::AbsolutePositionOf(Point2D p) const
{
	const Trans2D & now = Now();
	return now.Rot.rotateBack(p) + now.Pos;
}
Point2D Physics2D::Object::AbsoluteVelocityOf(Point2D p) const
{
	const Trans2D & vel = Vel();
	Point2D v;

	Point2D perp = p.perpendicular0().normalize();
	perp = Now().Rot.rotateBack(perp);
	// use Angle stuff instead ?

	v = perp * (vel.Rot.Ang.ToRadians() * p.length());
	v += vel.Pos;

	return v;
}





Physics2D::Object::~Object()
{ }
Physics2D::Object::Object()
	: InstanceManager(nullptr)
	, Data()
	, Data_PolyGon()
	, Data_WireFrame()
	, Data_WireFrameBox()
	, Data_Arrows()
	, IsStatic(true)
	, Mass(0.0f)
{ }
Physics2D::Object::Object(const Object & other)
	: InstanceManager(other.InstanceManager)
	, Data(other.Data)
	, Data_PolyGon(other.Data_PolyGon)
	, Data_WireFrame(other.Data_WireFrame)
	, Data_WireFrameBox(other.Data_WireFrameBox)
	, Data_Arrows(other.Data_Arrows)
	, IsStatic(other.IsStatic)
	, Mass(other.Mass)
{ }
Physics2D::Object & Physics2D::Object::operator=(const Object & other)
{
	InstanceManager = other.InstanceManager;
	Data = other.Data;
	Data_PolyGon = other.Data_PolyGon;
	Data_WireFrame = other.Data_WireFrame;
	Data_WireFrameBox = other.Data_WireFrameBox;
	Data_Arrows = other.Data_Arrows;
	IsStatic = other.IsStatic;
	Mass = other.Mass;
	return *this;
}



Physics2D::Object::Object(Physics2D::InstanceManager & inst_manager, bool is_static)
	: InstanceManager(&inst_manager)
	, Data()
	, Data_PolyGon(*(*InstanceManager).Instances_PolyGon, 1)
	, Data_WireFrame()
	, Data_WireFrameBox()
	, Data_Arrows()
	, IsStatic(is_static)
	, Mass(1.0f)
{ }
Physics2D::Object::Object(Physics2D::InstanceManager & inst_manager, Trans2D now, bool is_static)
	: InstanceManager(&inst_manager)
	, Data(now)
	, Data_PolyGon(*(*InstanceManager).Instances_PolyGon, 1)
	, Data_WireFrame()
	, Data_WireFrameBox()
	, Data_Arrows()
	, IsStatic(is_static)
	, Mass(1.0f)
{ }
Physics2D::Object::Object(Physics2D::InstanceManager & inst_manager, Trans2D now, Trans2D vel, bool is_static)
	: InstanceManager(&inst_manager)
	, Data(now, vel)
	, Data_PolyGon(*(*InstanceManager).Instances_PolyGon, 1)
	, Data_WireFrame()
	, Data_WireFrameBox()
	, Data_Arrows()
	, IsStatic(is_static)
	, Mass(1.0f)
{ }





bool Physics2D::Object::IsContaining(Point2D p) const
{
	return PolyGon() -> IsContaining(Now().Transform1(p));
}



void Physics2D::Object::UpdateArrows()
{
	if (Data_Arrows.Is())
	{
		Point2D now = Now().Pos;
		Point2D vel = Vel().Pos;
		Data_Arrows[0] = Arrow2D::Inst::Data(now, now + vel, 10, ColorF4(0.5f, 0.5f, 1.0f));
		/*for (unsigned int j = 0; j < Physics2D_Objects[i].CornerCount(); j++)
		{
			Point2D p = Physics2D_Objects[i].CornerFromIndex(j);
			Point2D now = Physics2D_Objects[i].AbsolutePositionOf(p);
			Point2D vel = Physics2D_Objects[i].AbsoluteVelocityOf(p);
			data.Insert(Arrow2D::Inst::Data(now, now + vel, 10, ColorF4(0.5f, 1.0f, 0.5f)));
			vel -= Physics2D_Objects[i].Vel().Pos;
			data.Insert(Arrow2D::Inst::Data(now, now + vel, 10, ColorF4(1.0f, 0.5f, 0.5f)));
		}*/
	}
}
