#ifndef  SCENE_OBJECT_POLYHEDRA_OBJECT_HPP
# define SCENE_OBJECT_POLYHEDRA_OBJECT_HPP

# include "SceneObject.hpp"
# include "PolyHedra/ObjectData.hpp"

# include "NewPolyHedraDataType/Basic3D/PalletObjectData.hpp"

/* PolyHedraObjects: temporary vs permanent

current PolyHedra Objects are temporary
so ObjectData like Trans only exists when Object .Is()

but here, I need Trans even when the PolyHedra Manager does not know this
*/

struct SceneObject_PolyHedraObject : public SceneObject
{
	Basic3D::PalletObjectData	Data;

	~SceneObject_PolyHedraObject();
	SceneObject_PolyHedraObject();
	SceneObject_PolyHedraObject(::NewPolyHedra::PalletObjectManager * manager, Trans3D trans);

	Trans3D		GetTrans() const override;
	void		SetTrans(const Trans3D & trans) override;

	void	Update() override;

	void	ShowWire() override;

	void	DisplayObject(const DisplayMode & mode) override;

	RayHitF3	Hit(const RayF3 & ray) const override;
};

#endif