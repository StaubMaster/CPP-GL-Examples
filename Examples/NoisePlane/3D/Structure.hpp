#ifndef  STRUCTURE_HPP
# define STRUCTURE_HPP

# include "ValueType/Vector/I3.hpp"
# include "Generics/Container/Array3D.hpp"

# include "Voxel.hpp"

# include <string>

struct Structure
{
	std::string		Name;
	VectorU3		Center;
	Array3D<Voxel>	Voxels;
};

#endif