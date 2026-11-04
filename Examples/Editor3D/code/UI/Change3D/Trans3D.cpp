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



bool Change3D::Trans3D::IndicatorsIsVisible() const
{
	return loop_check_any(Changes, &Change3D::Base::IndicatorsIsVisible);
}
void Change3D::Trans3D::IndicatorsShow()
{
	loop_invoke(Changes, &Change3D::Base::IndicatorsShow);
}
void Change3D::Trans3D::IndicatorsHide()
{
	loop_invoke(Changes, &Change3D::Base::IndicatorsHide);
}

RayHitF3 Change3D::Trans3D::IndicatorsFind(const RayF3 & ray)
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
				Changes[i] -> MakeOther();
			}
		}
	}

	Hovering = hit.Data;
	return hit;
}

void Change3D::Trans3D::IndicatorsUpdateColor()
{
}
void Change3D::Trans3D::IndicatorsUpdateScale(float scale)
{
	(void)scale;
}
void Change3D::Trans3D::IndicatorsUpdateTrans()
{
}

void Change3D::Trans3D::IndicatorsUpdate(const View3D & view, const DisplaySize & display_size)
{
	loop_invoke(Changes, &Change3D::Base::IndicatorsUpdate, view, display_size);
}



void Change3D::Trans3D::RoundValue()
{
}
void Change3D::Trans3D::ChangeValue(const RayF3 & ray)
{
	loop_invoke(Changes, &Change3D::Base::ChangeValue, ray);
}



void Change3D::Trans3D::MakeNone()
{
	loop_invoke(Changes, &Change3D::Base::MakeNone);
}
void Change3D::Trans3D::MakeOther()
{
	loop_invoke(Changes, &Change3D::Base::MakeOther);
}

bool Change3D::Trans3D::IsNone() const
{
	return loop_check_all(Changes, &Change3D::Base::IsNone);
}
bool Change3D::Trans3D::IsHovering() const
{
	return loop_check_any(Changes, &Change3D::Base::IsHovering);
}
bool Change3D::Trans3D::IsSelected() const
{
	return loop_check_any(Changes, &Change3D::Base::IsSelected);
}

void Change3D::Trans3D::SelectedMakeL()
{
	if (Hovering == nullptr) { return; }
	Hovering -> SelectedMakeL();
}
void Change3D::Trans3D::SelectedMakeR()
{
	if (Hovering == nullptr) { return; }
	Hovering -> SelectedMakeR();
}



void Change3D::Trans3D::Display()
{
	loop_invoke(Changes, &Change3D::Base::Display);
}
