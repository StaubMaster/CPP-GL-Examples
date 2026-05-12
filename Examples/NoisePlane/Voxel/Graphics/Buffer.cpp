#include "Buffer.hpp"



VoxelGraphics::BufferF::~BufferF() { }
VoxelGraphics::BufferF::BufferF()
	: ::BufferArray::MainInst<MainBufferF, InstBuffer>(GL::DrawMode::Triangles)
{ }

VoxelGraphics::BufferU::~BufferU() { }
VoxelGraphics::BufferU::BufferU()
	: ::BufferArray::MainInst<MainBufferU, InstBuffer>(GL::DrawMode::Triangles)
{ }
