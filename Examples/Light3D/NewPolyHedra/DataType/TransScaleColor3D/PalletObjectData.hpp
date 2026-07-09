#ifndef  NEW_POLYHEDRA_TEST_TYPE_TRANS_SCALE_COLOR_3D_PALLET_OBJECT_DATA_HPP
# define NEW_POLYHEDRA_TEST_TYPE_TRANS_SCALE_COLOR_3D_PALLET_OBJECT_DATA_HPP

# include "../../Type/PalletObjectData.hpp"
# include "ObjectData.hpp"

namespace TransScaleColor3D
{
typedef NewPolyHedra::Type_PalletObjectData<
	TransScaleColor3D::ObjectData
> PalletObjectData;
};

#endif