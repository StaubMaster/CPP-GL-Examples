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
struct ChunkNeighbour;

struct Voxel;
struct Chunk;
enum class VoxelType : unsigned char;

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
	Container::BlockLinkedList<1024, VoxelGraphicsDataU::Face>	BlockU;
	Container::Array<VoxelGraphicsDataU::Face>	ArrayU;
	public:
	void	ClearU();
	private:
	void	CatU(const VectorI3 & chunk, const VectorU3 & u, AxisRel axis, const AxisOrientation & orientation, const VoxelPallet & pallet);
	void	MakeU(const Chunk & chunk, const Array3D<VoxelType> & voxel_types, const ChunkNeighbour & neighbours);
	void	DoneU();
	public:
	const Container::Array<VoxelGraphicsDataU::Face> &	DataU() const;



	private:
	Container::BlockLinkedList<1024, VoxelGraphicsDataF::Face>	BlockF;
	Container::Array<VoxelGraphicsDataF::Face>	ArrayF;
	public:
	void	ClearF();
	private:
	void	CatF(const VectorF3 & offset, AxisRel axis, const AxisOrientation & orientation, const VoxelPallet & pallet);
	void	MakeF(const Chunk & chunk, const Array3D<VoxelType> & voxel_types, const ChunkNeighbour & neighbours);
	void	DoneF();
	public:
	const Container::Array<VoxelGraphicsDataF::Face> &	DataF() const;



	public:
	void	Make(const Chunk & chunk, const ChunkNeighbour & neighbours);
};

#endif