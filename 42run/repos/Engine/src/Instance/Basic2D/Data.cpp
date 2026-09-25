#include "Instance/Basic2D/Data.hpp"



Instance::Basic2D::Data::~Data() { }
Instance::Basic2D::Data::Data()
	: Trans()
{ }

Instance::Basic2D::Data::Data(Trans2D trans)
	: Trans(Matrix3x3::TransformForward(trans))
{ }
