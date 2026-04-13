#include "Buffer.hpp"



VoxelGraphics::Buffer::~Buffer() { }
VoxelGraphics::Buffer::Buffer()
	: ::BufferArray::MainInst<MainBuffer, InstBuffer>(GL::DrawMode::Triangles)
{ }
