#ifndef  STRUCTURE_HPP
# define STRUCTURE_HPP

# include "ValueType/Vector/I3.hpp"
# include "Generics/Container/Array3D.hpp"

# include "Voxel.hpp"

struct Structure
{
	static Structure	Tree0;
	static Structure	Tree1;
	static void			Default();

	VectorU3		Center;
	Array3D<Voxel>	Voxels;
};

#endif