#include "Buffer.hpp"
#include "Data.hpp"



VoxelGraphics::MainBufferF::~MainBufferF() { }
VoxelGraphics::MainBufferF::MainBufferF(::VertexArray & vertex_array)
	: ::Buffer::Array(vertex_array, GL::BufferDataUsage::StaticDraw, 0, sizeof(MainDataF))
	, Pos(*this)
	, Tex(*this)
	, Normal(*this)
{ }

VoxelGraphics::MainBufferU::~MainBufferU() { }
VoxelGraphics::MainBufferU::MainBufferU(::VertexArray & vertex_array)
	: ::Buffer::Array(vertex_array, GL::BufferDataUsage::StaticDraw, 0, sizeof(MainDataU))
	, Voxel(*this)
	, Texture(*this)
	, Chunk(*this)
{ }
