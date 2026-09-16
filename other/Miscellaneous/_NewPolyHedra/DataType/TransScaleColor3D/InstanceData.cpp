#include "NewPolyHedra/DataType/TransScaleColor3D/InstanceData.hpp"
#include "NewPolyHedra/DataType/TransScaleColor3D/ObjectData.hpp"



TransScaleColor3D::InstanceData::InstanceData(const ObjectData & data)
	: Trans(Matrix4x4::TransformForward(data.Trans))
	, Normal(Matrix4x4::Rotation(data.Trans.Rotation))
	, Scale(data.Scale)
	, Color(data.Color)
{ }
