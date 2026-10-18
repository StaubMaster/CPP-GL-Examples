#ifndef  SCENE_OBJECT_POLYHEDRA_OBJECT_HPP
# define SCENE_OBJECT_POLYHEDRA_OBJECT_HPP

# include "SceneObject.hpp"

# include "NewPolyHedra/DataType/Basic3D/Logical/Object.hpp"

/* PolyHedraObjects: temporary vs permanent

current PolyHedra Objects are temporary
so ObjectData like Trans only exists when Object .Is()

but here, I need Trans even when the PolyHedra Manager does not know this
*/

struct SceneObjectDisplayMode;
struct SceneObject_PolyHedraObject : public SceneObject
{
	NewPolyHedra::Basic3D::LogicalObject	Data;

	~SceneObject_PolyHedraObject();
	SceneObject_PolyHedraObject();
	SceneObject_PolyHedraObject(NewPolyHedra::BaseDisplayObject * manager, Trans3D trans);

	Trans3D		GetTrans() const override;
	void		SetTrans(const Trans3D & trans) override;

	void	Update() override;

	void	ShowWire() override;

	void	DisplayObject(const SceneObjectDisplayMode & mode) override;

	RayHitF3	Hit(const RayF3 & ray) const override;
};

#endif