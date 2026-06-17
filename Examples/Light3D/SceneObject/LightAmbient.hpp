#ifndef  SCENE_OBJECT_LIGHT_AMBIENT_HPP
# define SCENE_OBJECT_LIGHT_AMBIENT_HPP

# include "SceneObject.hpp"
# include "ValueType/LightBase.hpp"

struct PolyHedraPalletManager;

struct SceneObject_LightAmbient : public SceneObject
{
	LightBase *		Light;
	VectorF3		Position;
	::PolyHedraPalletManager *	Pallet;

	~SceneObject_LightAmbient();
	SceneObject_LightAmbient();

	Trans3D		GetTrans() const override;
	void		SetTrans(const Trans3D & trans) override;

	void	Update() override;

	void	ShowWire() override;

	void	DisplayObject() override;

	Ray3D_Hit	Hit(const Ray3D & ray) const override;
};

#endif