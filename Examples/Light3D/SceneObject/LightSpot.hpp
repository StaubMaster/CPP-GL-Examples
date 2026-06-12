#ifndef  SCENE_OBJECT_LIGHT_SPOT_HPP
# define SCENE_OBJECT_LIGHT_SPOT_HPP

# include "SceneObject.hpp"
# include "ValueType/LightSpot.hpp"
# include "PolyHedra/Object.hpp"

struct SceneObject_LightSpot : public SceneObject
{
	LightSpot *			Light;
//	VectorF3			Origin;
//	VectorF3			Target;
	PolyHedraObject		Object0;
	PolyHedraObject		Object1;

	~SceneObject_LightSpot();
	SceneObject_LightSpot();

	void	Update() override;

	Ray3D_Hit	Hit(const Ray3D & ray) const override;
};

#endif