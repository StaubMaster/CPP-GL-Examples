#include "Voxel.hpp"
#include "ValueType/VectorU3.hpp"



Voxel::~Voxel() { }
Voxel::Voxel()
	: Template(nullptr)
{ }

Voxel::Voxel(const Voxel & other)
	: Template(other.Template)
{ }
Voxel & Voxel::operator=(const Voxel & other)
{
	Template = other.Template;
	return *this;
}
