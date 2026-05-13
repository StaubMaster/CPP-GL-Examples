#ifndef  CHUNK_GRAPHICS_DATA_HPP
# define CHUNK_GRAPHICS_DATA_HPP

# include "Graphics/Main/Data.hpp"
# include "VoxelEnums.hpp"

# include "Miscellaneous/Container/Array.hpp"
# include "BlockList.hpp"

struct VectorU3;
struct VoxelOrientation;
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

struct ChunkGraphicsData // ChunkGraphicsData
{
	BlockList<1024, VoxelGraphics::MainFaceF>	DataF;
	BlockList<1024, VoxelGraphics::MainFaceU>	DataU;
	Container::Array<VoxelGraphics::MainFaceF>	ArrayF;
	Container::Array<VoxelGraphics::MainFaceU>	ArrayU;

	void	ClearU();
	void	ClearF();

	void	Concatnate(VectorU3 u, const VoxelOrientation & orientation, const VoxelPallet & pallet, AxisRel axis);
	void	Concatnate(VectorU3 u, const VoxelOrientation & orientation, const VoxelPallet & pallet, AxisRel axis, const ChunkNeighbour & neighbours);

	void	Make(const Chunk & chunk);

	void	DoneU();
	void	DoneF();
};

#endif