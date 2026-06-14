#ifndef  SCENE_OBJECT_POLYHEDRA_OBJECT_HPP
# define SCENE_OBJECT_POLYHEDRA_OBJECT_HPP

# include "SceneObject.hpp"
# include "PolyHedra/Object.hpp"

struct SceneObject_PolyHedraObject : public SceneObject
{
	Trans3D				Trans;
	PolyHedraObject		Object;

	~SceneObject_PolyHedraObject();
	SceneObject_PolyHedraObject();
	SceneObject_PolyHedraObject(::PolyHedraPalletManager * pallet, Trans3D trans);

	Trans3D		GetTrans() const override;
	void		SetTrans(const Trans3D & trans) override;

	void	Update() override;

	void	ShowWire() override;

	Ray3D_Hit	Hit(const Ray3D & ray) const override;
};

#endif