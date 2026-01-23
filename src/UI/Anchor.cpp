#include "Anchor.hpp"

#include "ValueType/Point2D.hpp"
#include "ValueType/AxisBox1D.hpp"
#include "ValueType/AxisBox2D.hpp"



Anchor1D::Anchor1D(float & size, float & min_dist, float & max_dist, float & normal_center, float & min_padding, float & max_padding) :
	Size(size),
	MinDist(min_dist),
	MaxDist(max_dist),
	NormalCenter(normal_center),
	MinPadding(min_padding),
	MaxPadding(max_padding),
	Anchor(ANCHOR_MIN)
{ }



float Anchor1D::GetSize() { return Size; }
float Anchor1D::GetMinDist() { return MinDist; }
float Anchor1D::GetMaxDist() { return MaxDist; }
float Anchor1D::GetNormalCenter() { return NormalCenter; }

float Anchor1D::GetHalfSize() { return (Size / 2); }
float Anchor1D::GetMinSize() { return (MinDist + Size); }
float Anchor1D::GetMaxSize() { return (MaxDist + Size); }
float Anchor1D::GetCenter() { return (MinDist + GetHalfSize()); }



void Anchor1D::SetSize(float val) { Size = val; }
void Anchor1D::SetMinDist(float val) { MinDist = val; }
void Anchor1D::SetMaxDist(float val) { MaxDist = val; }
void Anchor1D::SetNormalCenter(float val) { NormalCenter = val; }

void Anchor1D::SetHalfSize(float val) { Size = (val * 2); }
void Anchor1D::SetMinSize(float val) { MinDist = (val - Size); }
void Anchor1D::SetMaxSize(float val) { MaxDist = (val - Size); }
void Anchor1D::SetCenter(float val) { MinDist = (val - GetHalfSize()); }



float Anchor1D::GetPaddedSize() { return GetSize() + (MinPadding + MaxPadding); }
float Anchor1D::GetPaddedMinDist() { return GetMinDist() - MinPadding; }
float Anchor1D::GetPaddedMaxDist() { return GetMaxDist() - MaxPadding; }

float Anchor1D::GetPaddedHalfSize() { return GetPaddedSize() / 2; }
float Anchor1D::GetPaddedMinSize() { return GetMinSize() + MinPadding; }
float Anchor1D::GetPaddedMaxSize() { return GetMaxSize() + MaxPadding; }



void Anchor1D::SetPaddedSize(float val) { SetSize(val - (MinPadding + MaxPadding)); }
void Anchor1D::SetPaddedMinDist(float val) { SetMinDist(val + MinPadding); }
void Anchor1D::SetPaddedMaxDist(float val) { SetMaxDist(val + MaxPadding); }

void Anchor1D::SetPaddedHalfSize(float val) { SetPaddedSize(val / 2); }
void Anchor1D::SetPaddedMinSize(float val) { SetMinSize(val - MinPadding); }
void Anchor1D::SetPaddedMaxSize(float val) { SetMaxSize(val - MaxPadding); }



AxisBox1D Anchor1D::Calculate(AxisBox1D Parent)
{
	float ParentSize = Parent.Max - Parent.Min;
	if (Anchor == ANCHOR_BOTH)
	{
		Size = ParentSize - (MinDist + MaxDist);
		NormalCenter = GetCenter() / ParentSize;
	}
	else if (Anchor == ANCHOR_MIN)
	{
		MaxDist = ParentSize - GetMinSize();
		NormalCenter = GetCenter() / ParentSize;
	}
	else if (Anchor == ANCHOR_MAX)
	{
		MinDist = ParentSize - GetMaxSize();
		NormalCenter = GetCenter() / ParentSize;
	}
	else if (Anchor == ANCHOR_NONE)
	{
		MinDist = (ParentSize * NormalCenter) - GetHalfSize();
		MaxDist = ParentSize - GetMinSize();
	}
	return AxisBox1D(Parent.Min + MinDist, Parent.Max - MaxDist);
}

/*AxisBox1D Anchor1D::Calculate(AxisBox1D Dist, float Size, float NormalCenter, AxisBox1D Parent)
{
	AxisBox1D child;
	if (Anchor == ANCHOR_NONE)
	{
		float t0 = (NormalCenter - 0);
		float t1 = (1 - NormalCenter);
		float center = (Parent.Min * t0) + (Parent.Max * t1);
		child.Min = center - (Size / 2);
		child.Max = center + (Size / 2);
	}
	else if (Anchor == ANCHOR_MIN)
	{
		child.Min = Parent.Min + Dist.Min;
		child.Max = Parent.Min + Dist.Min + Size;
	}
	else if (Anchor == ANCHOR_MAX)
	{
		child.Min = Parent.Max - Dist.Max - Size;
		child.Max = Parent.Max - Dist.Max;
	}
	else if (Anchor == ANCHOR_BOTH)
	{
		child.Min = Parent.Min + Dist.Min;
		child.Max = Parent.Max - Dist.Max;
	}
	return child;
}*/



Anchor2D::Anchor2D(Anchor1D x, Anchor1D y) :
	X(x),
	Y(y)
{ }

AxisBox2D Anchor2D::Calculate(AxisBox2D Parent)
{
	AxisBox1D x = X.Calculate(AxisBox1D(Parent.Min.X, Parent.Max.X));
	AxisBox1D y = Y.Calculate(AxisBox1D(Parent.Min.Y, Parent.Max.Y));
	return AxisBox2D(
		Point2D(x.Min, y.Min),
		Point2D(x.Max, y.Max)
	);
}

/*AxisBox2D Anchor2D::Calculate(AxisBox2D Dist, Point2D Size, Point2D NormalCenter, AxisBox2D Parent)
{
	AxisBox1D x = X.Calculate(AxisBox1D(Dist.Min.X, Dist.Max.X), Size.X, NormalCenter.X, AxisBox1D(Parent.Min.X, Parent.Max.X));
	AxisBox1D y = Y.Calculate(AxisBox1D(Dist.Min.Y, Dist.Max.Y), Size.Y, NormalCenter.Y, AxisBox1D(Parent.Min.Y, Parent.Max.Y));
	return AxisBox2D(
		Point2D(x.Min, y.Min),
		Point2D(x.Max, y.Max)
	);
}*/
