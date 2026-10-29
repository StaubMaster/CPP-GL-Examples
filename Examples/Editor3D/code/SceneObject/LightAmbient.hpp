#ifndef  SCENE_OBJECT_LIGHT_AMBIENT_HPP
# define SCENE_OBJECT_LIGHT_AMBIENT_HPP

# include "SceneObject.hpp"
# include "ValueType/Light/Base.hpp"

# include "Special/TransScaleColor3D/Display/Object.hpp"
# include "Special/TransScaleColor3D/Logical/Data.hpp"

struct SceneObject_LightAmbient : public SceneObject
{
	LightBase *		Light;

	static	TransScaleColor3D::DisplayObject *		Display;
			TransScaleColor3D::LogicalData			Data;

	~SceneObject_LightAmbient();
	SceneObject_LightAmbient();

	Trans3D		GetTrans() const override;
	void		SetTrans(const Trans3D & trans) override;

	void	Update() override;

	bool	_ShowWire = false;
	void	ShowWire() override;

	void	DisplayObject(const SceneObjectDisplayMode & mode) override;

	RayHitF3	Hit(const RayF3 & ray) const override;
};

#endif