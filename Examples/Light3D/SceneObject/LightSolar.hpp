#ifndef  SCENE_OBJECT_LIGHT_SOLAR_HPP
# define SCENE_OBJECT_LIGHT_SOLAR_HPP

# include "SceneObject.hpp"
# include "ValueType/LightSolar.hpp"
# include "PolyHedra/Object.hpp"

struct SceneObject_LightSolar : public SceneObject
{
	PolyHedraObject		Object;
	LightSolar *			Light;
	~SceneObject_LightSolar();
	SceneObject_LightSolar();
	void	Update() override;
	Ray3D_Hit	Hit(const Ray3D & ray) const override;
};

#endif