#include "PolyHedra/Object.hpp"
#include "PolyHedra/ObjectData.hpp"
#include "PolyHedra/Manager.hpp"



bool			PolyHedraObject::Is() const { return (Data != nullptr); }
const Trans3D &	PolyHedraObject::Trans() const { return (Data -> Trans); }
Trans3D &		PolyHedraObject::Trans() { return (Data -> Trans); }



PolyHedraObject::~PolyHedraObject()
{
	if (Data != nullptr)
	{
		Data -> Remove = true;
	}
}
PolyHedraObject::PolyHedraObject()
	: Data(nullptr)
{ }

PolyHedraObject::PolyHedraObject(const PolyHedraObject & other)
	: Data(PolyHedraManager::Current().CopyObject(other.Data))
{ }
PolyHedraObject & PolyHedraObject::operator=(const PolyHedraObject & other)
{
	if (Data != nullptr)
	{
		Data -> Remove = true;
	}
	Data = PolyHedraManager::Current().CopyObject(other.Data);
	return *this;
}





PolyHedraObject::PolyHedraObject(unsigned int polyhedra)
	: Data(PolyHedraManager::Current().PlaceObject(polyhedra, Trans3D()))
{ }
PolyHedraObject::PolyHedraObject(unsigned int polyhedra, Trans3D trans)
	: Data(PolyHedraManager::Current().PlaceObject(polyhedra, trans))
{ }
PolyHedraObject::PolyHedraObject(unsigned int polyhedra, Point3D pos, EulerAngle3D ang)
	: Data(PolyHedraManager::Current().PlaceObject(polyhedra, Trans3D(pos, ang)))
{ }
PolyHedraObject::PolyHedraObject(unsigned int polyhedra, Point3D pos)
	: Data(PolyHedraManager::Current().PlaceObject(polyhedra, Trans3D(pos, EulerAngle3D())))
{ }



PolyHedraObject::PolyHedraObject(::PolyHedra * polyhedra)
	: Data(PolyHedraManager::Current().PlaceObject(polyhedra, Trans3D()))
{ }
PolyHedraObject::PolyHedraObject(::PolyHedra * polyhedra, Trans3D trans)
	: Data(PolyHedraManager::Current().PlaceObject(polyhedra, trans))
{ }
PolyHedraObject::PolyHedraObject(::PolyHedra * polyhedra, Point3D pos, EulerAngle3D ang)
	: Data(PolyHedraManager::Current().PlaceObject(polyhedra, Trans3D(pos, ang)))
{ }
PolyHedraObject::PolyHedraObject(::PolyHedra * polyhedra, Point3D pos)
	: Data(PolyHedraManager::Current().PlaceObject(polyhedra, Trans3D(pos, EulerAngle3D())))
{ }





void PolyHedraObject::Delete()
{
	if (Data != nullptr)
	{
		Data -> Remove = true;
		Data = nullptr;
	}
}
/*void PolyHedraObject::Create(unsigned int polyhedra)
{
	(void)polyhedra;
}*/
/*void PolyHedraObject::Create(::PolyHedra * polyhedra)
{
	(void)polyhedra;
}*/
