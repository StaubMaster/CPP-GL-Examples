#ifndef  SCENE_OBJECT_LIGHT_SPOT_HPP
# define SCENE_OBJECT_LIGHT_SPOT_HPP

# include "SceneObject.hpp"
# include "ValueType/Light/Spot.hpp"

# include "NewPolyHedra/DataType/Basic3D/Logical/Object.hpp"

struct SceneObjectDisplayMode;
struct SceneObject_LightSpot : public SceneObject
{
	LightSpot *		Light;

	NewPolyHedra::Basic3D::LogicalObject	Data;

	~SceneObject_LightSpot();
	SceneObject_LightSpot();

	Trans3D		GetTrans() const override;
	void		SetTrans(const Trans3D & trans) override;

	void	Update() override;

	void	ShowWire() override;

	void	DisplayObject(const SceneObjectDisplayMode & mode) override;

	RayHitF3	Hit(const RayF3 & ray) const override;
};

#endif