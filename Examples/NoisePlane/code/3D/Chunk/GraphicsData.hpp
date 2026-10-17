#ifndef  CHUNK_GRAPHICS_DATA_HPP
# define CHUNK_GRAPHICS_DATA_HPP

# include "3D/Voxel/Pallet/Geometry/Graphics/U/Data.hpp"
# include "3D/Voxel/Pallet/Geometry/Graphics/F/Data.hpp"

# include "Axis/3D/Types.hpp"
namespace Axis3D { struct Orientation; };

# include "Generics/Container/Array.hpp"
# include "Generics/Container/Array3D.hpp"
# include "Generics/Container/BlockLinkedList.hpp"

struct VectorU3;
struct VectorI3;
struct VectorF3;
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
		const ::Axis3D::Orientation & Orientation;
		const ::VoxelPallet & Pallet;
		const ::VoxelPalletGeometry & Geometry;
		const ::VectorI3 & Chunk;
		const ::VectorU3 & Undex;
		const ::VectorF3 & Offset;
		VoxelData(const ::Voxel & voxel, const VectorI3 & chunk, const VectorU3 & undex, const VectorF3 & offset);
	};



	private:
	Container::BlockLinkedList<1024, VoxelGraphicsDataU::Face>	BlockU;
	Container::BlockLinkedList<1024, VoxelGraphicsDataF::Face>	BlockF;

	Container::Array<VoxelGraphicsDataU::Face>	ArrayU;
	Container::Array<VoxelGraphicsDataF::Face>	ArrayF;

	public:
	void	ClearU();
	void	ClearF();

	const Container::Array<VoxelGraphicsDataU::Face> &	DataU() const;
	const Container::Array<VoxelGraphicsDataF::Face> &	DataF() const;



	private:
	void	CatU(const VoxelData & voxel_data, Axis3D::Rel axis);
	void	CatF(const VoxelData & voxel_data, Axis3D::Rel axis);
	void	Cat(const VoxelData & voxel_data, Axis3D::Rel axis);



	private:
	void	Done();
	void	Make(const Chunk & chunk, const Array3D<bool> & voxel_is_empty, const ChunkNeighbour & neighbours);

	public:
	void	Make(const Chunk & chunk, const ChunkNeighbour & neighbours);
};

#endif