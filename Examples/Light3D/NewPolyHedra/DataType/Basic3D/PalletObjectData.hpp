#ifndef  NEW_POLYHEDRA_TEST_TYPE_BASIC_3D_PALLET_OBJECT_DATA_HPP
# define NEW_POLYHEDRA_TEST_TYPE_BASIC_3D_PALLET_OBJECT_DATA_HPP

# include "../../Type/PalletObjectData.hpp"
# include "ObjectData.hpp"

namespace Basic3D
{
typedef NewPolyHedra::Type_PalletObjectData<
	Basic3D::ObjectData
> PalletObjectData;
};

#endif