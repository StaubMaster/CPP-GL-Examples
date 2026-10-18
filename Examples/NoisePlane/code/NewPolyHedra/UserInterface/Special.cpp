#include "LogicalData.hpp"
#include "DisplayData.hpp"

#include "NewPolyHedra/Type/Logical/Object.cpp"
#include "NewPolyHedra/Type/Logical/ObjectManager.cpp"
#include "NewPolyHedra/Type/Display/Object.cpp"
#include "NewPolyHedra/Type/Display/ObjectManager.cpp"
#include "NewPolyHedra/Type/Manager.cpp"
#include "NewPolyHedra/Type/Object.cpp"

namespace NewPolyHedra
{
typedef UserInterface::LogicalData LogicalData;
typedef UserInterface::DisplayData DisplayData;
template struct TypeLogicalObject			<LogicalData>;
template struct TypeLogicalObjectManager	<LogicalData>;
template struct TypeDisplayObject			<LogicalData, DisplayData>;
template struct DataDisplayObjectManager	<LogicalData>;
template struct TypeDisplayObjectManager	<LogicalData, DisplayData>;
template struct DataManager					<LogicalData>;
template struct TypeManager					<LogicalData, DisplayData>;
template struct Type_Object					<LogicalData>;
};
