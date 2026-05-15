#ifndef  VOXEL_GRAPHICS_MAIN_DATA_HPP
# define VOXEL_GRAPHICS_MAIN_DATA_HPP

# include "ValueType/Vector/F3.hpp"
# include "ValueType/Vector/U3.hpp"

enum class AxisRel : unsigned char;

namespace VoxelGraphics
{
	struct MainDataF
	{
		VectorF3	Pos;
		VectorF3	Tex;
		VectorF3	Normal;

		~MainDataF();
		MainDataF();

		MainDataF(const MainDataF & other);
		MainDataF & operator=(const MainDataF & other);

		MainDataF(VectorF3 pos, VectorF3 tex);
	};
	struct MainFaceF
	{
		MainDataF	Vertexes[3];

		~MainFaceF();
		MainFaceF();

		MainFaceF(const MainFaceF & other);
		MainFaceF & operator=(const MainFaceF & other);

		void	CalcNormal();
	};

	// unsigned int Data
	// Pos: [0;32]*3 
	// Tex: [0;1]*3
	// Normal: [0;6]
	// [0;31] is 5 Bits
	// [0;32] is 6 Bits
	// [0;1] is 1 Bit
	// [0;6] is 3 Bits
	// 6 * 3 = 18 Bits
	// 1 * 3 = 3 Bits
	// 24 Bits = 3 Bytes
	// make each Byte have 6 Bits for Pos, 1 Bit for Tex and 1 Bit of Normal ?
	// or just use uint32 for now ?

	/* Texture Coordinate ?
		Texture on the Texture are [0;1]
		Texture Index should be as much as possible ?
		|------||------||------||------| Bits in 4 Bytes
		[-PX-][-PY-][-PZ-][][N]
						  ||
						TextureXY
		this leaves 9 Bits [0;511] for the Texture Index
		512 is now enough ?
		I would much rather have 16 Bits [0;65535]
		this should require a second UInt32
		the Position wastes a lot of space
		32*32*32=32768 is 15 Bits
		currently it is 18 Bits
		which would leave 12 Bits [0;4095] for Texture Index
		4096 still dosent fell like enough

		8 Bits pre Axis
		2 Bits for Texture XY
		3 Bits for Normal
		32 Bits for Texture Index
	*/

	struct MainDataU
	{
		unsigned int	Vertex;
		unsigned int	Texture;

		~MainDataU();
		MainDataU();

		MainDataU(const MainDataU & other);
		MainDataU & operator=(const MainDataU & other);

		MainDataU(const VectorU3 & pos, const VectorU3 & tex, const AxisRel & axis);
	};
	struct MainFaceU
	{
		MainDataU	Vertexes[6];

		~MainFaceU();
		MainFaceU();
		
		MainFaceU(const MainFaceU & other);
		MainFaceU & operator=(const MainFaceU & other);

		MainFaceU(const MainDataU data[4]);
	};
};

#endif