#ifndef  CHUNK_GRAPHICS_DATA_HPP
# define CHUNK_GRAPHICS_DATA_HPP

# include "Graphics/Main/Data.hpp"
# include "General/Axis/Enums.hpp"

# include "Miscellaneous/Container/Array.hpp"
# include "Miscellaneous/Container/Array3D.hpp"
# include "Miscellaneous/Container/BlockLinkedList.hpp"

struct VectorU3;
struct VectorI3;
struct AxisOrientation;
struct VoxelPallet;
struct VoxelAxisGraphicsDataF;
struct ChunkNeighbour;

struct Voxel;
struct Chunk;

/* LOD ?
use Float Data for those that want it
only use DataU when farther away
*/

/* even simpler Graphics
maybe 1 Color per Voxel
for very far
*/

# include <mutex>

struct ChunkGraphicsData
{
	public:
	std::mutex	ArrayLock;



	private:
	Container::BlockLinkedList<1024, VoxelGraphics::MainFaceU>	BlockU;
	Container::Array<VoxelGraphics::MainFaceU>	ArrayU;
	public:
	void	ClearU();
	private:
	void	CatU(const VectorI3 & chunk, const VectorU3 & u, AxisRel axis, const AxisOrientation & orientation, const VoxelPallet & pallet);
	void	MakeU(const Chunk & chunk, const ChunkNeighbour & neighbours);
	void	DoneU();
	public:
	const Container::Array<VoxelGraphics::MainFaceU> &	GraphicsDataU() const;



	private:
	Container::BlockLinkedList<1024, VoxelGraphics::MainFaceF>	BlockF;
	Container::Array<VoxelGraphics::MainFaceF>	ArrayF;
	public:
	void	ClearF();
	private:
	void	DoneF();
	public:
	const Container::Array<VoxelGraphics::MainFaceF> &	GraphicsDataF() const;



	public:
	void	Make(const Chunk & chunk, const ChunkNeighbour & neighbours);
};

#endif