#ifndef  SCENE_OBJECT_LIGHT_SPOT_HPP
# define SCENE_OBJECT_LIGHT_SPOT_HPP

# include "SceneObject.hpp"
# include "ValueType/Light/Spot.hpp"

# include "Special/Basic3D/Display/Object.hpp"
# include "Special/Basic3D/Logical/Data.hpp"

struct SceneObjectDisplayMode;
struct SceneObject_LightSpot : public SceneObject
{
	LightSpot *		Light;

	static	NewPolyHedra::Basic3D::DisplayObject *	Display;
			NewPolyHedra::Basic3D::LogicalData		Data;

	~SceneObject_LightSpot();
	SceneObject_LightSpot();

	Trans3D		GetTrans() const override;
	void		SetTrans(const Trans3D & trans) override;

	void	Update() override;

	bool	_ShowWire = false;
	void	ShowWire() override;

	void	DisplayObject(const SceneObjectDisplayMode & mode) override;

	RayHitF3	Hit(const RayF3 & ray) const override;
};

#endif