#include "Instance/Basic3D/Data.hpp"



Instance::Basic3D::Data::~Data() { }
Instance::Basic3D::Data::Data()
	: Trans()
	, Normal()
{ }

Instance::Basic3D::Data::Data(Trans3D trans)
	: Trans(Matrix4x4::TransformForward(trans))
	, Normal(Matrix4x4::Rotation(trans.Rotation))
{ }
