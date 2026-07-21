#include "LayoutU.hpp"
#include "DataU.hpp"



VoxelGraphics::LayoutU::~LayoutU()
{ }
VoxelGraphics::LayoutU::LayoutU()
	: ::Attribute::Layout(0, sizeof(VoxelGraphicsDataU::Vertex))
	, Voxel(*this)
	, Texture(*this)
	, Chunk(*this)
{ }
