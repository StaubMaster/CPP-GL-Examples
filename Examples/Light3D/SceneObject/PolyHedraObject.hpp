#ifndef  SCENE_OBJECT_POLYHEDRA_OBJECT_HPP
# define SCENE_OBJECT_POLYHEDRA_OBJECT_HPP

# include "SceneObject.hpp"
# include "PolyHedra/Object.hpp"

struct SceneObject_PolyHedraObject : public SceneObject
{
	PolyHedraObject		Object;
	~SceneObject_PolyHedraObject();
	SceneObject_PolyHedraObject();
	SceneObject_PolyHedraObject(const PolyHedraObject & obj);
	void	Update() override;
	Ray3D_Hit	Hit(const Ray3D & ray) const override;
};

#endif