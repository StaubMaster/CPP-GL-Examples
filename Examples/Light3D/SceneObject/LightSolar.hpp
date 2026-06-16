#ifndef  SCENE_OBJECT_LIGHT_SOLAR_HPP
# define SCENE_OBJECT_LIGHT_SOLAR_HPP

# include "SceneObject.hpp"
# include "ValueType/LightSolar.hpp"
# include "PolyHedra/Object.hpp"

struct SceneObject_LightSolar : public SceneObject
{
	LightSolar *		Light;
	VectorF3			Position;
	PolyHedraObject		Object;

	~SceneObject_LightSolar();
	SceneObject_LightSolar();

	Trans3D		GetTrans() const override;
	void		SetTrans(const Trans3D & trans) override;

	void	Update() override;

	void	ShowWire() override;

	void	DisplayObject() override;

	Ray3D_Hit	Hit(const Ray3D & ray) const override;
};

#endif