#ifndef  NEW_POLYHEDRA_DATA_TYPE_TRANS_SCALE_COLOR_3D_TYPE_MANAGER_HPP
# define NEW_POLYHEDRA_DATA_TYPE_TRANS_SCALE_COLOR_3D_TYPE_MANAGER_HPP

# include "NewPolyHedra/Type/Manager.hpp"

namespace TransScaleColor3D
{
struct LogicalData;
struct DisplayData;
typedef NewPolyHedra::TypeManager <LogicalData, DisplayData> Manager;
};

#endif