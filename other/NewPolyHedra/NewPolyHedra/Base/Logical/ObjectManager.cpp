#include "NewPolyHedra/Base/Logical/ObjectManager.hpp"
#include "NewPolyHedra/Base/Logical/Object.hpp"

#include "NewPolyHedra/Base/Display/ObjectManager.hpp"

#include "NewPolyHedra/Pallet/Manager.hpp"

#include "Generics/Loop.hpp"



/*unsigned int NewPolyHedra::BaseLogicalObjectManager::Count() const
{
	return Datas.Count();
}*/



/*void NewPolyHedra::BaseLogicalObjectManager::Clean()
{
	for (unsigned int i = 0; i < Datas.Count(); i++)
	{
		BaseLogicalObject * object = Datas[i];
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
}*/



/*void NewPolyHedra::BaseLogicalObjectManager::InstancesMake()
{
	Container::Loop::Invoke(Datas, &NewPolyHedra::BaseLogicalObject::InstancePut);
}*/
