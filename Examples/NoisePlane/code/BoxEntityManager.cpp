#include "BoxEntityManager.hpp"
#include "BoxEntity3D.hpp"

#include "PhysicsContext.hpp"

#include "DisplayHelp/Normalized.hpp"



void BoxEntityManager::Delete(BoxEntity3D * box_entity)
{
	Remove(*box_entity);
	delete box_entity;
}
void BoxEntityManager::Remove(BoxEntity3D & box_entity)
{
	for (unsigned int i = 0; i < BoxEntitys.Count(); i++)
	{
		if (BoxEntitys[i] == &box_entity)
		{
			BoxEntitys.RemoveAt(i);
			i--;
		}
	}
}
void BoxEntityManager::Insert(BoxEntity3D * box_entity)
{
	BoxEntitys.Insert(box_entity);
}
void BoxEntityManager::Create(BoxEntity3D & box_entity)
{
	Insert(new BoxEntity3D(box_entity));
}



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
