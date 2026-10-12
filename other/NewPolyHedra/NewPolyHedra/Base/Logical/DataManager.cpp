#include "NewPolyHedra/Base/Logical/DataManager.hpp"
#include "NewPolyHedra/Base/Logical/Data.hpp"

#include "NewPolyHedra/Base/Display/DataManager.hpp"

#include "NewPolyHedra/Pallet/Manager.hpp"

#include "Generics/Loop.hpp"



unsigned int NewPolyHedra::BaseLogicalDataManager::Count() const
{
	return Datas.Count();
}



void NewPolyHedra::BaseLogicalDataManager::Clean()
{
	for (unsigned int i = 0; i < Datas.Count(); i++)
	{
		BaseLogicalData * object = Datas[i];
		if (object == nullptr)
		{
			Datas.RemoveAt(i);
			i--;
		}
		else if (object -> Remove)
		{
			delete object;
			Datas.RemoveAt(i);
			i--;
		}
	}
}



void NewPolyHedra::BaseLogicalDataManager::InstancesMake()
{
	Container::Loop::Invoke(Datas, NewPolyHedra::BaseLogicalData::InstancePut);
}
