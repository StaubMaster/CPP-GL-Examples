#ifndef  CHUNK_GRAPHICS_DATA_HPP
# define CHUNK_GRAPHICS_DATA_HPP

# include "Graphics/DataU.hpp"
# include "Graphics/DataF.hpp"
# include "Axis/Enums.hpp"

# include "Generics/Container/Array.hpp"
# include "Generics/Container/Array3D.hpp"
# include "Generics/Container/BlockLinkedList.hpp"

struct VectorU3;
struct VectorI3;
struct VectorF3;
struct AxisOrientation;
struct VoxelPallet;
struct VoxelPalletGeometry;
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

	struct VoxelData
	{
		const ::Voxel & Voxel;
		const ::AxisOrientation & Orientation;
		const ::VoxelPallet & Pallet;
		const ::VoxelPalletGeometry & Geometry;
		const ::VectorI3 & Chunk;
		const ::VectorU3 & Undex;
		const ::VectorF3 & Offset;
		VoxelData(const ::Voxel & voxel, const VectorI3 & chunk, const VectorU3 & undex, const VectorF3 & offset);
	};



	private:
	Container::BlockLinkedList<1024, VoxelGraphicsDataU::Face>	BlockU;
	Container::Array<VoxelGraphicsDataU::Face>	ArrayU;
	public:
	void	ClearU();
	const Container::Array<VoxelGraphicsDataF::Face> &	DataF() const;



	private:
	Container::BlockLinkedList<1024, VoxelGraphicsDataF::Face>	BlockF;
	Container::Array<VoxelGraphicsDataF::Face>	ArrayF;
	public:
	void	ClearF();
	const Container::Array<VoxelGraphicsDataU::Face> &	DataU() const;



	private:
	void	CatU(const VoxelData & voxel_data, AxisRel axis);
	void	CatF(const VoxelData & voxel_data, AxisRel axis);
	void	Cat(const VoxelData & voxel_data, AxisRel axis);



	private:
	void	Done();
	void	Make(const Chunk & chunk, const Array3D<bool> & voxel_is_empty, const ChunkNeighbour & neighbours);

	public:
	void	Make(const Chunk & chunk, const ChunkNeighbour & neighbours);
};

#endif