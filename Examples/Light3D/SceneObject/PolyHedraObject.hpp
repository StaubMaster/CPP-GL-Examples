#ifndef  SCENE_OBJECT_POLYHEDRA_OBJECT_HPP
# define SCENE_OBJECT_POLYHEDRA_OBJECT_HPP

# include "SceneObject.hpp"
# include "PolyHedra/ObjectData.hpp"

/* PolyHedraObjects: temporary vs permanent

current PolyHedra Objects are temporary
so ObjectData like Trans only exists when Object .Is()

but here, I need Trans even when the PolyHedra Manager does not know this
*/

struct SceneObject_PolyHedraObject : public SceneObject
{
	PolyHedraObjectData		Data;

	~SceneObject_PolyHedraObject();
	SceneObject_PolyHedraObject();
	SceneObject_PolyHedraObject(::PolyHedraPalletManager * pallet, Trans3D trans);

	Trans3D		GetTrans() const override;
	void		SetTrans(const Trans3D & trans) override;

	void	Update() override;

	void	ShowWire() override;

	void	DisplayObject() override;

	Ray3D_Hit	Hit(const Ray3D & ray) const override;
};

#endif