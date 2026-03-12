#include "Arrow2D/Object.hpp"
#include "Arrow2D/Manager.hpp"



Arrow2D::Object::~Object()
{ }
Arrow2D::Object::Object()
	: Data()
{ }
Arrow2D::Object::Object(unsigned int count)
	: Data(Arrow2D::Manager::Current().Instances, count)
{ }



void Arrow2D::Object::Dispose()
{
	Data.Dispose();
}
void Arrow2D::Object::Allocate(unsigned int count)
{
	Data.Allocate(Arrow2D::Manager::Current().Instances, count);
}
