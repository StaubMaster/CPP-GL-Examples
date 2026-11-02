#include "UI/Change3D/Trans3D.hpp"

#include "Ray3D_Hit.hpp"
#include "ValueType/Ray/Hit/F3Type.hpp"



#include "Generics/Loop.hpp"

// put in Container::Loop
// these have double args to allow conversion if not identical


template<
	typename TypeItemObject,
	typename TypeFuncObject,
	typename ... TypeFuncArgs,
	typename ... TypeItemArgs
>
static void		loop_invoke(
	Container::Binary<TypeItemObject*> & container,
	void (TypeFuncObject::*func)(TypeFuncArgs ...),
	TypeItemArgs & ... args
)
{
	unsigned long n = container.Count();
	for (unsigned long i = 0; i < n; i++)
	{
		TypeItemObject * obj = container.At(i);
		if (obj != nullptr)
		{
			(*obj.*func)(args ...);
		}
	}
}



template<
	typename TypeItemObject,
	typename TypeFuncObject,
	typename ... TypeFuncArgs,
	typename ... TypeItemArgs
>
static bool		loop_check_all(
	const Container::Binary<TypeItemObject*> & container,
	bool (TypeFuncObject::*func)(TypeFuncArgs ...) const,
	const TypeItemArgs & ... args
)
{
	unsigned long n = container.Count();
	for (unsigned long i = 0; i < n; i++)
	{
		const TypeItemObject * obj = container.At(i);
		if (obj != nullptr)
		{
			if (!(*obj.*func)(args ...))
			{
				return false;
			}
		}
	}
	return true;
}



template<
	typename TypeItemObject,
	typename TypeFuncObject,
	typename ... TypeFuncArgs,
	typename ... TypeItemArgs
>
static bool		loop_check_any(
	const Container::Binary<TypeItemObject*> & container,
	bool (TypeFuncObject::*func)(TypeFuncArgs ...) const,
	const TypeItemArgs & ... args
)
{
	unsigned long n = container.Count();
	for (unsigned long i = 0; i < n; i++)
	{
		const TypeItemObject * obj = container.At(i);
		if (obj != nullptr)
		{
			if ((*obj.*func)(args ...))
			{
				return true;
			}
		}
	}
	return false;
}





Change3D::Trans3D::Trans3D()
	: Changes()
	, VectorF3()
	, EulerAngle3D()
{
	Changes.Insert(&VectorF3);
	Changes.Insert(&EulerAngle3D);
}



void Change3D::Trans3D::IndicatorsInit(PolyHedraManager & manager, const DirectoryInfo & dir)
{
	loop_invoke(Changes, &Change3D::Base::IndicatorsInit, manager, dir);
}

void Change3D::Trans3D::IndicatorsShow()
{
	loop_invoke(Changes, &Change3D::Base::IndicatorsShow);
}
void Change3D::Trans3D::IndicatorsHide()
{
	loop_invoke(Changes, &Change3D::Base::IndicatorsHide);
}

Change3D::Base * Change3D::Trans3D::IndicatorsFind(const RayF3 & ray)
{
	RayHitF3Type<Base *> hit(nullptr);

	for (unsigned int i = 0; i < Changes.Count(); i++)
	{
		if (Changes[i] != nullptr)
		{
			hit.Consider(Changes[i] -> IndicatorsFind(ray), Changes[i]);
		}
	}

	if (hit.Is())
	{
		for (unsigned int i = 0; i < Changes.Count(); i++)
		{
			if (Changes[i] != hit.Data)
			{
				Changes[i] -> HoveringMakeOther();
			}
		}
	}

	return hit.Data;
}

void Change3D::Trans3D::IndicatorsUpdate(const View3D & view, const DisplaySize & display_size)
{
	loop_invoke(Changes, &Change3D::Base::IndicatorsUpdate, view, display_size);
}



bool Change3D::Trans3D::IsNone() const
{
	return loop_check_all(Changes, &Change3D::Base::IsNone);
}



bool Change3D::Trans3D::HoveringIsNone() const
{
	return loop_check_all(Changes, &Change3D::Base::HoveringIsNone);
}
void Change3D::Trans3D::HoveringMakeNone()
{
	loop_invoke(Changes, &Change3D::Base::HoveringMakeNone);
}
void Change3D::Trans3D::HoveringMakeOther()
{
	loop_invoke(Changes, &Change3D::Base::HoveringMakeOther);
}



bool Change3D::Trans3D::SelectedIsNone() const
{
	return loop_check_all(Changes, &Change3D::Base::SelectedIsNone);
}
void Change3D::Trans3D::SelectedMakeNone()
{
	loop_invoke(Changes, &Change3D::Base::SelectedMakeNone);
}

/*void Change3D::Trans3D::SelectedMakeL(unsigned int idx)
{
	if (Changes.Check(idx))
	{
		Changes[idx] -> SelectedMakeL();
	}
}*/
/*void Change3D::Trans3D::SelectedMakeR(unsigned int idx)
{
	if (Changes.Check(idx))
	{
		Changes[idx] -> SelectedMakeR();
	}
}*/



void Change3D::Trans3D::ChangeValue(const RayF3 & ray)
{
	loop_invoke(Changes, &Change3D::Base::ChangeValue, ray);
}



void Change3D::Trans3D::Display()
{
	loop_invoke(Changes, &Change3D::Base::Display);
}
