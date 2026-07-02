#include "PalletObjectData.hpp"
#include "PalletObjectManager.hpp"
#include "ObjectData.hpp"


void NewPolyHedra_PalletObjectData::InstancePut() const
{
	if (Manager != nullptr)
	{
		Manager -> InstancePut(Data);
	}
}
