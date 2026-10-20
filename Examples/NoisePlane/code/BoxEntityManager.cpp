#include "BoxEntityManager.hpp"
#include "BoxEntity3D.hpp"

#include "PhysicsContext.hpp"

#include "DisplayHelp/Normalized.hpp"



void BoxEntityManager::Physics(const Physics::GravityContext & context, BoxEntity3D & box_entity)
{
	box_entity.Vel += context.Vector();
}
void BoxEntityManager::Physics(const Physics::GravityContext & context)
{
	for (unsigned int i = 0; i < BoxEntitys.Count(); i++)
	{
		BoxEntity3D * obj = BoxEntitys[i];
		if (obj != nullptr)
		{
			Physics(context, *obj);
		}
	}
}

void BoxEntityManager::Display()
{
	for (unsigned int i = 0; i < BoxEntitys.Count(); i++)
	{
		BoxEntity3D * obj = BoxEntitys[i];
		if (obj != nullptr)
		{
			DisplayHelp::Normalized(*obj);
		}
	}
}
