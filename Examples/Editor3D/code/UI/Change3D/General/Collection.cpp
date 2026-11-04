#include "UI/Change3D/General/Collection.hpp"

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





bool Change3D::Collection::IndicatorsIsVisible() const
{
	return loop_check_any(Changes, &Change3D::Base::IndicatorsIsVisible);
}
void Change3D::Collection::IndicatorsShow()
{
	loop_invoke(Changes, &Change3D::Base::IndicatorsShow);
}
void Change3D::Collection::IndicatorsHide()
{
	loop_invoke(Changes, &Change3D::Base::IndicatorsHide);
}

void Change3D::Collection::IndicatorsDisplay()
{
	loop_invoke(Changes, &Change3D::Base::IndicatorsDisplay);
}

void Change3D::Collection::IndicatorsUpdateColor()
{
}
void Change3D::Collection::IndicatorsUpdateScale(float scale)
{
	(void)scale;
}
void Change3D::Collection::IndicatorsUpdateTrans()
{
}

void Change3D::Collection::IndicatorsUpdate(const View3D & view, const DisplaySize & display_size)
{
	loop_invoke(Changes, &Change3D::Base::IndicatorsUpdate, view, display_size);
}

RayHitF3 Change3D::Collection::IndicatorsFind(const RayF3 & ray)
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



void Change3D::Collection::MakeNone()
{
	loop_invoke(Changes, &Change3D::Base::MakeNone);
}
void Change3D::Collection::MakeOther()
{
	loop_invoke(Changes, &Change3D::Base::MakeOther);
}

bool Change3D::Collection::IsNone() const
{
	return loop_check_all(Changes, &Change3D::Base::IsNone);
}
bool Change3D::Collection::IsHovering() const
{
	return loop_check_any(Changes, &Change3D::Base::IsHovering);
}
bool Change3D::Collection::IsSelected() const
{
	return loop_check_any(Changes, &Change3D::Base::IsSelected);
}

void Change3D::Collection::MakeL()
{
	if (Hovering != nullptr)
	{
		Hovering -> MakeL();
	}
}
void Change3D::Collection::MakeR()
{
	if (Hovering != nullptr)
	{
		Hovering -> MakeR();
	}
}



Change3D::Collection::Collection()
	: Base()
	, Changes()
{ }

void Change3D::Collection::ChangeValue(const RayF3 & ray)
{
	loop_invoke(Changes, &Change3D::Base::ChangeValue, ray);
}
