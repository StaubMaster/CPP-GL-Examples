#ifndef  SCENE_OBJECT_LIGHT_AMBIENT_HPP
# define SCENE_OBJECT_LIGHT_AMBIENT_HPP

# include "SceneObject.hpp"
# include "ValueType/LightBase.hpp"
# include "PolyHedra/Object.hpp"

struct SceneObject_LightAmbient : public SceneObject
{
	PolyHedraObject		Object;
	LightBase *			Light;
	~SceneObject_LightAmbient();
	SceneObject_LightAmbient();
	void	Update() override;
	Ray3D_Hit	Hit(const Ray3D & ray) const override;
};

#endif