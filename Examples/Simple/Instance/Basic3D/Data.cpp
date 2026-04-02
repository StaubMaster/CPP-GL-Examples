#include "Instance/Basic3D/Data.hpp"



Instance::Basic3D::Data::~Data() { }
Instance::Basic3D::Data::Data()
	: Trans()
	, Normal()
{ }

Instance::Basic3D::Data::Data(Trans3D trans)
	: Trans(trans.ToMatrixForward())
	, Normal(Matrix4x4::Rotation(trans.Rotation))
{ }
