#include "Voxel.hpp"
#include "ValueType/VectorU3.hpp"



Voxel::~Voxel() { }
Voxel::Voxel()
	: Template(nullptr)
	, Orientation()
{ }

Voxel::Voxel(const Voxel & other)
	: Template(other.Template)
	, Orientation(other.Orientation)
{ }
Voxel & Voxel::operator=(const Voxel & other)
{
	Template = other.Template;
	Orientation = other.Orientation;
	return *this;
}
