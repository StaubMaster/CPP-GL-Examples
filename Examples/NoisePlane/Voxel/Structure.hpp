#ifndef  STRUCTURE_HPP
# define STRUCTURE_HPP

# include "ValueType/Vector/I3.hpp"
# include "Miscellaneous/Container/Array3D.hpp"

# include "Voxel.hpp"

struct Structure
{
	static Structure	Tree0;
	static void			Default();

	VectorI3		Offset;
	Array3D<Voxel>	Voxels;
};

#endif