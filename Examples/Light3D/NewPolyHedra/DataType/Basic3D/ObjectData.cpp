#include "ObjectData.hpp"
#include "InstanceData.hpp"



Basic3D::InstanceData Basic3D::ObjectData::ToData() const
{
	return Instance::Basic3D::Data(Trans);
}
