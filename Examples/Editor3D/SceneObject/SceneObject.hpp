#ifndef  SCENE_OBJECT_HPP
# define SCENE_OBJECT_HPP

# include "ValueType/Trans/3D.hpp"
# include "ValueType/Ray/Hit/F3.hpp"

struct PolyHedraManager;

struct SceneObject
{
	struct DisplayMode
	{
		enum class EIndicators
		{
			Show,
			Hide,
		};
		EIndicators		Indicators;

		enum class EObjects
		{
			Full,
			Wire,
			None,
		};
		EObjects	Objects;
	};

	virtual ~SceneObject();
	SceneObject();

	virtual Trans3D		GetTrans() const = 0;
	virtual void		SetTrans(const Trans3D & trans) = 0;

	virtual void	Update() = 0;

	virtual void	ShowWire() = 0;

	virtual void	DisplayObject(const DisplayMode & mode) = 0;

	virtual RayHitF3	Hit(const RayF3 & ray) const = 0;
};

#endif