#ifndef  VOXEL_GRAPHICS_MAIN_DATA_HPP
# define VOXEL_GRAPHICS_MAIN_DATA_HPP

# include "ValueType/VectorF3.hpp"

namespace VoxelGraphics
{
	struct MainData
	{
		VectorF3		Pos;
		VectorF3		Tex;

		~MainData();
		MainData();

		MainData(const MainData & other);
		MainData & operator=(const MainData & other);

		MainData(VectorF3 pos, VectorF3 tex);
	};
	struct MainTriangle
	{
		MainData	Corners[3];

		~MainTriangle();
		MainTriangle();

		MainTriangle(const MainTriangle & other);
		MainTriangle & operator=(const MainTriangle & other);
	};
};

#endif