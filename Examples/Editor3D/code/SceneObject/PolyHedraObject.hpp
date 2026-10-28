#ifndef  SCENE_OBJECT_POLYHEDRA_OBJECT_HPP
# define SCENE_OBJECT_POLYHEDRA_OBJECT_HPP

# include "SceneObject.hpp"

# include "Special/Basic3D/Logical/Object.hpp"
# include "Special/Basic3D/Logical/Data.hpp"

# include "Special/Basic3D/Display/Object.hpp"
# include "Special/Basic3D/Display/Data.hpp"

struct SceneObjectDisplayMode;
struct SceneObject_PolyHedraObject : public SceneObject
{
	NewPolyHedra::Basic3D::LogicalObject	Data;

	~SceneObject_PolyHedraObject() = default;
	SceneObject_PolyHedraObject() = default;

	SceneObject_PolyHedraObject(NewPolyHedra::Basic3D::DisplayObject * display, Trans3D trans);

	Trans3D		GetTrans() const override;
	void		SetTrans(const Trans3D & trans) override;

	void	Update() override;

	void	ShowWire() override;

	void	DisplayObject(const SceneObjectDisplayMode & mode) override;

	RayHitF3	Hit(const RayF3 & ray) const override;
};

#endif