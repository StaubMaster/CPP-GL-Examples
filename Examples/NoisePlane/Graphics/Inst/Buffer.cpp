#include "Buffer.hpp"
#include "Data.hpp"



VoxelGraphics::InstLayout::~InstLayout() { }
VoxelGraphics::InstLayout::InstLayout()
	: ::Attribute::Layout(1, sizeof(InstData))
	, Pos(*this)
{ }
