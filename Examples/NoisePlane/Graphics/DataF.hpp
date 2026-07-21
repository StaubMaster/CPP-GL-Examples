#ifndef  VOXEL_GRAPHICS_DATA_F_HPP
# define VOXEL_GRAPHICS_DATA_F_HPP

# include "ValueType/Vector/F3.hpp"

namespace VoxelGraphicsDataF
{
	struct Vertex
	{
		VectorF3	Pos;
		VectorF3	Tex;
		VectorF3	Normal;

		~Vertex() = default;
		Vertex() = default;
		Vertex(const Vertex & other) = default;
		Vertex & operator=(const Vertex & other) = default;

		Vertex(VectorF3 pos, VectorF3 tex);
	};
	struct Face
	{
		Vertex	Vertexes[3];

		~Face() = default;
		Face() = default;
		Face(const Face & other) = default;
		Face & operator=(const Face & other) = default;

		void	CalcNormal();
	};
};

#endif