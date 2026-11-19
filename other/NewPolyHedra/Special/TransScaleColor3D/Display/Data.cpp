#include "Special/TransScaleColor3D/Display/Data.hpp"
#include "Special/TransScaleColor3D/Logical/Data.hpp"



TransScaleColor3D::DisplayData::DisplayData(const LogicalData & data)
	: Trans(
		Matrix4x4::TransformForward(data.Trans) *
		Matrix4x4::Scale(data.Scale)
	)
	, Color(data.Color)
{ }
