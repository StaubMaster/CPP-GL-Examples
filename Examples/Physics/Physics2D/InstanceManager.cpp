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
{
	IntData.Density = 1.0f;
	IntData.Restitution = 1.0f;
}
Physics2D::InstanceManager::InstanceManager(const InstanceManager & other)
	: Manager(other.Manager)
	, PolyGon(other.PolyGon)
	, Bound(other.Bound)
	, IntData(other.IntData)
{ }
Physics2D::InstanceManager & Physics2D::InstanceManager::operator=(const InstanceManager & other)
{
	Manager = other.Manager;
	PolyGon = other.PolyGon;
	Bound = other.Bound;
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
