#include "Graphics/U/Layout.hpp"
#include "Graphics/U/Data.hpp"



VoxelGraphics::LayoutU::~LayoutU()
{ }
VoxelGraphics::LayoutU::LayoutU()
	: ::Attribute::Layout(0, sizeof(VoxelGraphicsDataU::Vertex))
	, Voxel(*this)
	, Texture(*this)
	, Chunk(*this)
{ }
