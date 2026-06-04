#include "Anchor1D.hpp"
#include "AnchorEnum.hpp"
#include "ValueType/Box/F1.hpp"



refBoxF1::refBoxF1(float & min, float & max)
	: Min(min)
	, Max(max)
{ }



Anchor1D::Anchor1D(
	float & size,
	refBoxF1 dist,
	refBoxF1 margin,
	refBoxF1 boarder,
	refBoxF1 padding,
	float & normal_center
)
	: Size(size)
	, Dist(dist)
	, Margin(margin)
	, Boarder(boarder)
	, Padding(padding)
	, NormalCenter(normal_center)
	, Anchor(AnchorType::Min)
{ }



//float Anchor1D::GetRealSize() { return Size; }
//float Anchor1D::GetRealHalfSize() { return (Size / 2); }
//float Anchor1D::GetRealMinDist() { return MinDist; }
//float Anchor1D::GetRealMinSize() { return (MinDist + Size); }
//float Anchor1D::GetRealMaxDist() { return MaxDist; }
//float Anchor1D::GetRealMaxSize() { return (MaxDist + Size); }
//float Anchor1D::GetRealNormalCenter() { return NormalCenter; }
//float Anchor1D::GetRealCenter() { return (MinDist + GetRealHalfSize()); }



//void Anchor1D::SetRealSize(float val) { Size = val; }
//void Anchor1D::SetRealHalfSize(float val) { Size = (val * 2); }
//void Anchor1D::SetRealMinDist(float val) { Dist.Min = val; }
//void Anchor1D::SetRealMinSize(float val) { Dist.Min = (val - Size); }
//void Anchor1D::SetRealMaxDist(float val) { Dist.Max = val; }
//void Anchor1D::SetRealMaxSize(float val) { Dist.Max = (val - Size); }
//void Anchor1D::SetRealNormalCenter(float val) { NormalCenter = val; }
//void Anchor1D::SetRealCenter(float val) { Dist.Min = (val - GetRealHalfSize()); }



//	Padded
//float Anchor1D::GetPaddedSize() { return GetRealSize() + (MinPadding + MaxPadding); }
//float Anchor1D::GetPaddedHalfSize() { return GetPaddedSize() / 2; }
//float Anchor1D::GetPaddedMinDist() { return GetRealMinDist() - MinPadding; }
//float Anchor1D::GetPaddedMinSize() { return GetRealMinSize() + MinPadding; }
//float Anchor1D::GetPaddedMaxDist() { return GetRealMaxDist() - MaxPadding; }
//float Anchor1D::GetPaddedMaxSize() { return GetRealMaxSize() + MaxPadding; }



//void Anchor1D::SetPaddedSize(float val) { SetRealSize(val - (MinPadding + MaxPadding)); }
//void Anchor1D::SetPaddedHalfSize(float val) { SetPaddedSize(val * 2); }
//void Anchor1D::SetPaddedMinDist(float val) { SetRealMinDist(val + MinPadding); }
//void Anchor1D::SetPaddedMinSize(float val) { SetRealMinSize(val - MinPadding); }
//void Anchor1D::SetPaddedMaxDist(float val) { SetRealMaxDist(val + MaxPadding); }
//void Anchor1D::SetPaddedMaxSize(float val) { SetRealMaxSize(val - MaxPadding); }



//float Anchor1D::GetSize() { return GetRealSize(); }
////float Anchor1D::GetHalfSize() { return GetRealHalfSize(); }
//float Anchor1D::GetMinDist() { return GetPaddedMinDist(); }
//float Anchor1D::GetMinSize() { return GetPaddedMinSize(); }
//float Anchor1D::GetMaxDist() { return GetPaddedMaxDist(); }
//float Anchor1D::GetMaxSize() { return GetPaddedMaxSize(); }
////float Anchor1D::GetNormalCenter() { return GetRealNormalCenter(); }
////float Anchor1D::GetCenter() { return GetRealCenter(); }

//void Anchor1D::SetSize(float val) { SetRealSize(val); }
////void Anchor1D::SetHalfSize(float val) { SetRealHalfSize(val); }
//void Anchor1D::SetMinDist(float val) { SetPaddedMinDist(val); }
//void Anchor1D::SetMinSize(float val) { SetPaddedMinSize(val); }
//void Anchor1D::SetMaxDist(float val) { SetPaddedMaxDist(val); }
//void Anchor1D::SetMaxSize(float val) { SetPaddedMaxSize(val); }
////void Anchor1D::SetNormalCenter(float val) { SetRealNormalCenter(val); }
////void Anchor1D::SetCenter(float val) { SetCenter(val); }

float Anchor1D::GetSize() { return Size; }
//float Anchor1D::GetHalfSize() { return GetRealHalfSize(); }
float Anchor1D::GetMinDist() { return (Dist.Min) - Margin.Max; }
float Anchor1D::GetMinSize() { return (Dist.Min + Size) + Margin.Max; }
float Anchor1D::GetMaxDist() { return (Dist.Max) - Margin.Max; }
float Anchor1D::GetMaxSize() { return (Dist.Max + Size) + Margin.Max; }
//float Anchor1D::GetNormalCenter() { return GetRealNormalCenter(); }
//float Anchor1D::GetCenter() { return GetRealCenter(); }

void Anchor1D::SetSize(float val) { Size = val; }
//void Anchor1D::SetHalfSize(float val) { SetRealHalfSize(val); }
void Anchor1D::SetMinDist(float val) { Dist.Min = ((val + Margin.Max)); }
void Anchor1D::SetMinSize(float val) { Dist.Min = ((val - Margin.Max) - Size); }
void Anchor1D::SetMaxDist(float val) { Dist.Max = ((val + Margin.Max)); }
void Anchor1D::SetMaxSize(float val) { Dist.Max = ((val - Margin.Max) - Size); }
//void Anchor1D::SetNormalCenter(float val) { SetRealNormalCenter(val); }
//void Anchor1D::SetCenter(float val) { SetCenter(val); }



void Anchor1D::AnchorMin(float dist)
{
	Anchor = AnchorType::Min;
	SetMinDist(dist);
}
void Anchor1D::AnchorMin(float dist, float size)
{
	Anchor = AnchorType::Min;
	SetMinDist(dist);
	SetSize(size);
}
void Anchor1D::AnchorMax(float dist)
{
	Anchor = AnchorType::Max;
	SetMaxDist(dist);
}
void Anchor1D::AnchorMax(float dist, float size)
{
	Anchor = AnchorType::Max;
	SetMaxDist(dist);
	SetSize(size);
}
void Anchor1D::AnchorBoth(float min, float max)
{
	Anchor = AnchorType::Both;
	SetMinDist(min);
	SetMaxDist(max);
}



void Anchor1D::CalculateSize(float ParentSize) { Size = ParentSize - (Dist.Min + Dist.Max); }
void Anchor1D::CalculateNormalCenter(float ParentSize) { NormalCenter = (Dist.Min + (Size / 2)) / ParentSize; }

BoxF1 Anchor1D::Calculate(BoxF1 Parent)
{
	float ParentSize = Parent.Size();
	if (Anchor == AnchorType::Both)
	{
		CalculateSize(ParentSize);
		CalculateNormalCenter(ParentSize);
	}
	else if (Anchor == AnchorType::Min)
	{
		Dist.Max = ParentSize - (Dist.Min + Size);
		CalculateNormalCenter(ParentSize);
	}
	else if (Anchor == AnchorType::Max)
	{
		Dist.Min = ParentSize - (Dist.Max + Size);
		CalculateNormalCenter(ParentSize);
	}
	else if (Anchor == AnchorType::None)
	{
		Dist.Min = (ParentSize * NormalCenter) - (Size / 2);
		Dist.Max = ParentSize - (Dist.Min + Size);
	}
	return BoxF1(Parent.Min + Dist.Min, Parent.Max - Dist.Max);
}
void Anchor1D::Calculate(BoxF1 Parent, BoxF1 box)
{
	Dist.Min = +(box.Min - Parent.Min);
	Dist.Max = -(box.Max - Parent.Max);

	float ParentSize = Parent.Size();
	CalculateSize(ParentSize);
	CalculateNormalCenter(ParentSize);
}
