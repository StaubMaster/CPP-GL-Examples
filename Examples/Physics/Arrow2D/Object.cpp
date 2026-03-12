#include "Arrow2D/Object.hpp"
#include "Arrow2D/Manager.hpp"



bool Arrow2D::Object::Is() const { return Data != nullptr; }
unsigned int Arrow2D::Object::Count() const { return (Data -> DataArray).Count(); }
Arrow2D::Inst::Data & Arrow2D::Object::operator*() { return (Data -> DataArray)[0]; }
Arrow2D::Inst::Data & Arrow2D::Object::operator[](unsigned int idx) { return (Data -> DataArray)[idx]; }
const Arrow2D::Inst::Data & Arrow2D::Object::operator*() const { return (Data -> DataArray)[0]; }
const Arrow2D::Inst::Data & Arrow2D::Object::operator[](unsigned int idx) const { return (Data -> DataArray)[idx]; }



Arrow2D::Object::~Object()
{
	if (Data != nullptr)
	{
		Data -> DisposeThisFrame = true;
	}
}
Arrow2D::Object::Object()
	: Data(nullptr)
{ }
Arrow2D::Object::Object(unsigned int count)
	: Data(new Arrow2D::Data(count))
{
	Arrow2D::Manager::Current().Instances.Insert(Data);
}



void Arrow2D::Object::Dispose()
{
	if (Data != nullptr)
	{
		Data -> DisposeThisFrame = true;
		Data = nullptr;
	}
}
void Arrow2D::Object::Allocate(unsigned int count)
{
	Dispose();
	Data = new Arrow2D::Data(count);
	Arrow2D::Manager::Current().Instances.Insert(Data);
}
