#include "Special/TransScaleColor3D/Display/Data.hpp"
#include "Special/TransScaleColor3D/Logical/Data.hpp"



TransScaleColor3D::DisplayData::DisplayData(const LogicalData & data)
	: Trans(Matrix4x4::TransformForward(data.Trans))
	, Normal(Matrix4x4::Rotation(data.Trans.Rotation))
	, Scale(data.Scale)
	, Color(data.Color)
{ }
