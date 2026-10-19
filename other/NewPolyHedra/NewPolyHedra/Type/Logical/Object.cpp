#include "NewPolyHedra/Type/Logical/Object.hpp"
#include "NewPolyHedra/Type/Logical/ObjectManager.hpp"



template<typename LogicalData> void NewPolyHedra::TypeLogicalObject<LogicalData>::InstancePut() const
{
	if (DisplayObject != nullptr)
	{
		if (VisibleFull())
		{
			DisplayObject -> InstancesFullPut(Data);
		}
		if (VisibleWire())
		{
			DisplayObject -> InstancesWirePut(Data);
		}
	}
}
