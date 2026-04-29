#include "VoxelTemplate.hpp"
#include "VoxelOrientation.hpp"
#include "Voxel.hpp"

#include "VoxelGraphicsTemplate.hpp"



VoxelTemplate VoxelTemplate::OrientationCube(VoxelGraphicsTemplate::Cube);
VoxelTemplate VoxelTemplate::OrientationCylinder(VoxelGraphicsTemplate::Cylinder);
VoxelTemplate VoxelTemplate::OrientationSlope(VoxelGraphicsTemplate::Slope);

VoxelTemplate VoxelTemplate::Gray(VoxelGraphicsTemplate::Cube);
VoxelTemplate VoxelTemplate::Grass(VoxelGraphicsTemplate::Cube);
VoxelTemplate VoxelTemplate::RedLog(VoxelGraphicsTemplate::Cylinder);

VoxelTemplate VoxelTemplate::ConcreteCube(VoxelGraphicsTemplate::Cube);
VoxelTemplate VoxelTemplate::ConcreteCylinder(VoxelGraphicsTemplate::Cylinder);



const VoxelGraphicsData & VoxelTemplate::AxisData(AxisRel axis) const
{
	return GraphicsTemplate.AxisData(axis);
}
bool VoxelTemplate::Visible(AxisRel axis) const
{
	return GraphicsTemplate.Visible(axis);
}

Voxel VoxelTemplate::ToVoxel(AxisRel placeAxis0, AxisRel placeAxis1) const
{
	Voxel voxel;
	voxel.Template = this;
	voxel.Orientation = GraphicsTemplate.Orient(placeAxis0, placeAxis1);
	return voxel;
}



VoxelTemplate::~VoxelTemplate()
{ }
VoxelTemplate::VoxelTemplate(VoxelGraphicsTemplate & graphics_template)
	: GraphicsTemplate(graphics_template)
	, TextureFile()
	, TextureIndex(0)
	, PolyHedra(nullptr)
{ }
