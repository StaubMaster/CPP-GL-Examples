#include "Special/Basic3D/Logical/Data.hpp"
#include "Special/Basic3D/Display/Data.hpp"

#include "NewPolyHedra/Type/Logical/Object.cpp"
#include "NewPolyHedra/Type/Logical/ObjectManager.cpp"
#include "NewPolyHedra/Type/Display/Object.cpp"
#include "NewPolyHedra/Type/Display/ObjectManager.cpp"
#include "NewPolyHedra/Type/Manager.cpp"
#include "NewPolyHedra/Type/Object.cpp"

namespace NewPolyHedra
{
typedef Basic3D::LogicalData LogicalData;
typedef Basic3D::DisplayData DisplayData;
template struct TypeLogicalObject			<LogicalData>;
template struct TypeLogicalObjectManager	<LogicalData>;
template struct TypeDisplayObject			<LogicalData, DisplayData>;
template struct DataDisplayObjectManager	<LogicalData>;
template struct TypeDisplayObjectManager	<LogicalData, DisplayData>;
template struct DataManager					<LogicalData>;
template struct TypeManager					<LogicalData, DisplayData>;
template struct TypeObject					<LogicalData>;
};

#include "Special/Basic3D/Logical/Object.hpp"
#include "Special/Basic3D/Logical/ObjectManager.hpp"
#include "Special/Basic3D/Display/Object.hpp"
#include "Special/Basic3D/Display/ObjectManager.hpp"
#include "Special/Basic3D/Manager.hpp"
#include "Special/Basic3D/Object.hpp"
