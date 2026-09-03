#include "3D/Voxel/Pallet/Geometry/Graphics/F/Layout.hpp"
#include "3D/Voxel/Pallet/Geometry/Graphics/F/Data.hpp"



VoxelGraphics::LayoutF::~LayoutF() { }
VoxelGraphics::LayoutF::LayoutF()
	: ::Attribute::Layout(0, sizeof(VoxelGraphicsDataF::Vertex))
	, Pos(*this)
	, Tex(*this)
	, Normal(*this)
{ }
