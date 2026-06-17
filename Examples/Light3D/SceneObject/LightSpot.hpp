#ifndef  SCENE_OBJECT_LIGHT_SPOT_HPP
# define SCENE_OBJECT_LIGHT_SPOT_HPP

# include "SceneObject.hpp"
# include "ValueType/LightSpot.hpp"
# include "ValueType/Trans3D.hpp"

struct PolyHedraPalletManager;

struct SceneObject_LightSpot : public SceneObject
{
	LightSpot *			Light;
	Trans3D				Trans;
	::PolyHedraPalletManager *	Pallet0;
	::PolyHedraPalletManager *	Pallet1;

	~SceneObject_LightSpot();
	SceneObject_LightSpot();

	Trans3D		GetTrans() const override;
	void		SetTrans(const Trans3D & trans) override;

	void	Update() override;

	void	ShowWire() override;

	void	DisplayObject() override;

	Ray3D_Hit	Hit(const Ray3D & ray) const override;
};

#endif