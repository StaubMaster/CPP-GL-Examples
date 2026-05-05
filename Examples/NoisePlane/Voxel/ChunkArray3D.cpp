#include "ChunkArray3D.hpp"



unsigned int ChunkArray3D::Count() const { return Size.Product(); }

Chunk * & ChunkArray3D::operator[](unsigned int idx) { return Data[idx]; }
Chunk * & ChunkArray3D::operator[](VectorU3 idx) { return Data[Size.Convert(idx)]; }

// Lock Container while doing this
// make Lock a part of Container ?

Chunk * ChunkArray3D::FindLockOrNull(VectorI3 idx)
{
	VectorU3 udx = relative(idx);
	if ((udx < Size).Any(false)) { return nullptr; }
	Chunk * chunk = Data[Size.Convert(udx)];
	if (chunk == nullptr) { return nullptr; }
	chunk -> lock();
	return chunk;
}
Chunk * ChunkArray3D::FindTryLockOrNull(VectorI3 idx)
{
	VectorU3 udx = relative(idx);
	if ((udx < Size).Any(false)) { return nullptr; }
	Chunk * chunk = Data[Size.Convert(udx)];
	if (chunk == nullptr) { return nullptr; }
	if (!chunk -> try_lock()) { return nullptr; }
	return chunk;
}

VectorI3 ChunkArray3D::absolute(VectorU3 u) const { return u + Corner; }
VectorU3 ChunkArray3D::relative(VectorI3 i) const { return i - Corner; }



ChunkArray3D::~ChunkArray3D()
{
	delete[] Data;
}
ChunkArray3D::ChunkArray3D()
	: Data(nullptr)
	, Size()
{ }
