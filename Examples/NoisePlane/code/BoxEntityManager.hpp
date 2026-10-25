#ifndef  BOX_ENTITY_MANAGER_HPP
# define BOX_ENTITY_MANAGER_HPP

# include "Generics/Container/Binary.hpp"

struct BoxEntity3D;
struct FrameTime;

namespace Physics
{
	struct GravityContext;
};

struct BoxEntityManager
{
	Container::Binary<BoxEntity3D*>		BoxEntitys;

	void	Delete(BoxEntity3D * box_entity);
	void	Remove(BoxEntity3D & box_entity);
	void	Insert(BoxEntity3D * box_entity);
	void	Create(BoxEntity3D & box_entity);

	void	Physics(const Physics::GravityContext & context, BoxEntity3D & box_entity);
	void	Physics(const Physics::GravityContext & context);

	void	Display();
};

#endif