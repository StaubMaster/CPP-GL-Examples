#include "Logical/Data.hpp"
#include "Display/Data.hpp"

#include "NewPolyHedra/Type/Logical/Object.cpp"
#include "NewPolyHedra/Type/Logical/ObjectManager.cpp"
#include "NewPolyHedra/Type/Display/Object.cpp"
#include "NewPolyHedra/Type/Display/ObjectManager.cpp"
#include "NewPolyHedra/Type/Manager.cpp"
#include "NewPolyHedra/Type/Object.cpp"

namespace NewPolyHedra
{
typedef TransScaleColor3D::LogicalData LogicalData;
typedef TransScaleColor3D::DisplayData DisplayData;
template struct TypeLogicalObject			<LogicalData>;
template struct TypeLogicalObjectManager	<LogicalData>;
template struct TypeDisplayObject			<LogicalData, DisplayData>;
template struct DataDisplayObjectManager	<LogicalData>;
template struct TypeDisplayObjectManager	<LogicalData, DisplayData>;
template struct DataManager					<LogicalData>;
template struct TypeManager					<LogicalData, DisplayData>;
template struct Type_Object					<LogicalData>;
};
