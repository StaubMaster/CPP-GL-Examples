#include "ObjectData.hpp"
#include "InstanceData.hpp"



TransScaleColor3D::InstanceData TransScaleColor3D::ObjectData::ToData() const
{
	InstanceData data;
	data.Trans = Matrix4x4::TransformForward(Trans);
	data.Normal = Matrix4x4::Rotation(Trans.Rotation);
	data.Scale = Scale;
	data.Color = Color;
	return data;
}
