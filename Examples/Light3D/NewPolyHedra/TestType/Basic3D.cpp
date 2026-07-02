#include "Basic3D.hpp"



TestBasic3D::InstanceData TestBasic3D::ObjectData::ToData() const
{
	return Instance::Basic3D::Data(Trans);
}



TestBasic3D::ShaderLayout::~ShaderLayout()
{ }
TestBasic3D::ShaderLayout::ShaderLayout()
	: ::Uniform::Layout()
	, DisplaySize(*this, "DisplaySize")
	, View(*this, "View")
	, Depth(*this, "Depth")
	, FOV(*this, "FOV")
{ }
