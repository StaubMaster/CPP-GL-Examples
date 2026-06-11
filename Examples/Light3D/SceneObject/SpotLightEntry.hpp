#ifndef  SCENE_OBJECT_SPOT_LIGHT_ENTRY_HPP
# define SCENE_OBJECT_SPOT_LIGHT_ENTRY_HPP

# include "SceneObject.hpp"
# include "../SpotLightEntry.hpp"

struct SceneObject_SpotLightEntry : public SceneObject
{
	SpotLightEntry		Object;
	~SceneObject_SpotLightEntry();
	SceneObject_SpotLightEntry();
	void	Update() override;
	Ray3D_Hit	Hit(const Ray3D & ray) const override;
};

#endif