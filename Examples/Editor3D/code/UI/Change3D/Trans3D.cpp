#include "UI/Change3D/Trans3D.hpp"

#include "Ray3D_Hit.hpp"
#include "ValueType/Ray/Hit/F3Type.hpp"



void Change3D::Trans3D::IndicatorsInit(const DirectoryInfo & dir)
{
	unsigned int n = 2;
	Change3D::Base * change3D[n] = {
		&VectorF3,
		&EulerAngle3D,
	};

	for (unsigned int i = 0; i < n; i++)
	{
		change3D[i] -> IndicatorsInit(dir);
	}
}

void Change3D::Trans3D::IndicatorsShow()
{
	unsigned int n = 2;
	Change3D::Base * change3D[n] = {
		&VectorF3,
		&EulerAngle3D,
	};

	for (unsigned int i = 0; i < n; i++)
	{
		change3D[i] -> IndicatorsShow();
	}
}
void Change3D::Trans3D::IndicatorsHide()
{
	unsigned int n = 2;
	Change3D::Base * change3D[n] = {
		&VectorF3,
		&EulerAngle3D,
	};

	for (unsigned int i = 0; i < n; i++)
	{
		change3D[i] -> IndicatorsHide();
	}
}

unsigned int Change3D::Trans3D::IndicatorsFind(const RayF3 & ray)
{
	unsigned int n = 2;
	Change3D::Base * change3D[n] = {
		&VectorF3,
		&EulerAngle3D,
	};

	RayHitF3Type<unsigned int> hit;

	for (unsigned int i = 0; i < n; i++)
	{
		hit.Consider(change3D[i] -> IndicatorsFind(ray), i);
	}

	if (hit.Is())
	{
		for (unsigned int i = 0; i < n; i++)
		{
			if (hit.Data != i)
			{
				change3D[i] -> HoveringMakeOther();
			}
		}
	}

	return hit.Data;
}

void Change3D::Trans3D::IndicatorsUpdate(const View3D & view, const DisplaySize & display_size)
{
	unsigned int n = 2;
	Change3D::Base * change3D[n] = {
		&VectorF3,
		&EulerAngle3D,
	};

	for (unsigned int i = 0; i < n; i++)
	{
		change3D[i] -> IndicatorsUpdate(view, display_size);
	}
}



bool Change3D::Trans3D::IsNone() const
{
	unsigned int n = 2;
	const Change3D::Base * change3D[n] = {
		&VectorF3,
		&EulerAngle3D,
	};

	for (unsigned int i = 0; i < n; i++)
	{
		if (!change3D[i] -> IsNone())
		{
			return false;
		}
	}

	return true;
}



bool Change3D::Trans3D::HoveringIsNone() const
{
	unsigned int n = 2;
	const Change3D::Base * change3D[n] = {
		&VectorF3,
		&EulerAngle3D,
	};

	for (unsigned int i = 0; i < n; i++)
	{
		if (!change3D[i] -> HoveringIsNone())
		{
			return false;
		}
	}

	return true;
}
void Change3D::Trans3D::HoveringMakeNone()
{
	unsigned int n = 2;
	Change3D::Base * change3D[n] = {
		&VectorF3,
		&EulerAngle3D,
	};

	for (unsigned int i = 0; i < n; i++)
	{
		change3D[i] -> HoveringMakeNone();
	}
}
void Change3D::Trans3D::HoveringMakeOther()
{
	unsigned int n = 2;
	Change3D::Base * change3D[n] = {
		&VectorF3,
		&EulerAngle3D,
	};

	for (unsigned int i = 0; i < n; i++)
	{
		change3D[i] -> HoveringMakeOther();
	}
}



bool Change3D::Trans3D::SelectedIsNone() const
{
	unsigned int n = 2;
	const Change3D::Base * change3D[n] = {
		&VectorF3,
		&EulerAngle3D,
	};

	for (unsigned int i = 0; i < n; i++)
	{
		if (!change3D[i] -> SelectedIsNone())
		{
			return false;
		}
	}

	return true;
}
void Change3D::Trans3D::SelectedMakeNone()
{
	unsigned int n = 2;
	Change3D::Base * change3D[n] = {
		&VectorF3,
		&EulerAngle3D,
	};

	for (unsigned int i = 0; i < n; i++)
	{
		change3D[i] -> SelectedMakeNone();
	}
}

void Change3D::Trans3D::SelectedMakeL(unsigned int idx)
{
	unsigned int n = 2;
	Change3D::Base * change3D[n] = {
		&VectorF3,
		&EulerAngle3D,
	};

	for (unsigned int i = 0; i < n; i++)
	{
		if (i == idx)
		{
			change3D[i] -> SelectedMakeL();
		}
	}
}
void Change3D::Trans3D::SelectedMakeR(unsigned int idx)
{
	unsigned int n = 2;
	Change3D::Base * change3D[n] = {
		&VectorF3,
		&EulerAngle3D,
	};

	for (unsigned int i = 0; i < n; i++)
	{
		if (i == idx)
		{
			change3D[i] -> SelectedMakeR();
		}
	}
}



void Change3D::Trans3D::ChangeValue(const RayF3 & ray)
{
	unsigned int n = 2;
	Change3D::Base * change3D[n] = {
		&VectorF3,
		&EulerAngle3D,
	};

	for (unsigned int i = 0; i < n; i++)
	{
		change3D[i] -> ChangeValue(ray);
	}
}
