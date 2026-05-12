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

	struct MainDataU
	{
		unsigned int	Value;

		~MainDataU();
		MainDataU();

		MainDataU(const MainDataU & other);
		MainDataU & operator=(const MainDataU & other);

		MainDataU(VectorU3 pos, VectorU3 tex, AxisRel axis);
	};
	struct MainFaceU
	{
		MainDataU	Vertexes[6];

		~MainFaceU();
		MainFaceU();

		MainFaceU(const MainFaceU & other);
		MainFaceU & operator=(const MainFaceU & other);
	};
};

#endif