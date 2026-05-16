#ifndef  CHUNK_GRAPHICS_DATA_HPP
# define CHUNK_GRAPHICS_DATA_HPP

# include "Graphics/Main/Data.hpp"
# include "VoxelEnums.hpp"

# include "Miscellaneous/Container/Array.hpp"
# include "Miscellaneous/Container/Array3D.hpp"
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

struct ChunkGraphicsData
{
	private:
	BlockList<1024, VoxelGraphics::MainFaceU>	DataU;
	Container::Array<VoxelGraphics::MainFaceU>	ArrayU;
	public:
	void	ClearU();
	private:
	void	CatU(VectorU3 u, AxisRel axis, const VoxelOrientation & orientation, const VoxelPallet & pallet);
	void	MakeU(const Chunk & chunk, const ChunkNeighbour & neighbours);
	void	DoneU();
	public:
	const Container::Array<VoxelGraphics::MainFaceU> &	GraphicsDataU() const;



	private:
	BlockList<1024, VoxelGraphics::MainFaceF>	DataF;
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