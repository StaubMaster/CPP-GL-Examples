#include "NewPolyHedra/DataType/Basic3D/InstanceData.hpp"
#include "NewPolyHedra/DataType/Basic3D/ObjectData.hpp"



NewPolyHedra::Basic3D::InstanceData::InstanceData(const ObjectData & data)
	: Trans(Matrix4x4::TransformForward(data.Trans))
	, Normal(Matrix4x4::Rotation(data.Trans.Rotation))
{ }
