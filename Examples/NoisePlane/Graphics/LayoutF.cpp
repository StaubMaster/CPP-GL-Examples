#include "LayoutF.hpp"
#include "DataF.hpp"



VoxelGraphics::LayoutF::~LayoutF() { }
VoxelGraphics::LayoutF::LayoutF()
	: ::Attribute::Layout(0, sizeof(VoxelGraphicsDataF::Vertex))
	, Pos(*this)
	, Tex(*this)
	, Normal(*this)
{ }
