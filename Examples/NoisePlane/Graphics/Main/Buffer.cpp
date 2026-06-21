#include "Buffer.hpp"
#include "Data.hpp"



VoxelGraphics::MainLayoutF::~MainLayoutF() { }
VoxelGraphics::MainLayoutF::MainLayoutF()
	: ::Attribute::Layout(0, sizeof(MainDataF))
	, Pos(*this)
	, Tex(*this)
	, Normal(*this)
{ }

VoxelGraphics::MainLayoutU::~MainLayoutU() { }
VoxelGraphics::MainLayoutU::MainLayoutU()
	: ::Attribute::Layout(0, sizeof(MainDataU))
	, Voxel(*this)
	, Texture(*this)
	, Chunk(*this)
{ }
