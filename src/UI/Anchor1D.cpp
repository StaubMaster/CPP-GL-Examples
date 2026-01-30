#include "Anchor1D.hpp"
#include "AnchorEnum.hpp"
#include "ValueType/AxisBox1D.hpp"



Anchor1D::Anchor1D(float & size, float & min_dist, float & max_dist, float & normal_center, float & min_padding, float & max_padding) :
	Size(size),
	MinDist(min_dist),
	MaxDist(max_dist),
	NormalCenter(normal_center),
	MinPadding(min_padding),
	MaxPadding(max_padding),
	Anchor(AnchorType::Min)
{ }




float Anchor1D::GetRealSize() { return Size; }
float Anchor1D::GetRealHalfSize() { return (Size / 2); }
float Anchor1D::GetRealMinDist() { return MinDist; }
float Anchor1D::GetRealMinSize() { return (MinDist + Size); }
float Anchor1D::GetRealMaxDist() { return MaxDist; }
float Anchor1D::GetRealMaxSize() { return (MaxDist + Size); }
float Anchor1D::GetRealNormalCenter() { return NormalCenter; }
float Anchor1D::GetRealCenter() { return (MinDist + GetRealHalfSize()); }



void Anchor1D::SetRealSize(float val) { Size = val; }
void Anchor1D::SetRealHalfSize(float val) { Size = (val * 2); }
void Anchor1D::SetRealMinDist(float val) { MinDist = val; }
void Anchor1D::SetRealMinSize(float val) { MinDist = (val - Size); }
void Anchor1D::SetRealMaxDist(float val) { MaxDist = val; }
void Anchor1D::SetRealMaxSize(float val) { MaxDist = (val - Size); }
void Anchor1D::SetRealNormalCenter(float val) { NormalCenter = val; }
void Anchor1D::SetRealCenter(float val) { MinDist = (val - GetRealHalfSize()); }



//	Padded
float Anchor1D::GetPaddedSize() { return GetRealSize() + (MinPadding + MaxPadding); }
float Anchor1D::GetPaddedHalfSize() { return GetPaddedSize() / 2; }
float Anchor1D::GetPaddedMinDist() { return GetRealMinDist() - MinPadding; }
float Anchor1D::GetPaddedMinSize() { return GetRealMinSize() + MinPadding; }
float Anchor1D::GetPaddedMaxDist() { return GetRealMaxDist() - MaxPadding; }
float Anchor1D::GetPaddedMaxSize() { return GetRealMaxSize() + MaxPadding; }



void Anchor1D::SetPaddedSize(float val) { SetRealSize(val - (MinPadding + MaxPadding)); }
void Anchor1D::SetPaddedHalfSize(float val) { SetPaddedSize(val * 2); }
void Anchor1D::SetPaddedMinDist(float val) { SetRealMinDist(val + MinPadding); }
void Anchor1D::SetPaddedMinSize(float val) { SetRealMinSize(val - MinPadding); }
void Anchor1D::SetPaddedMaxDist(float val) { SetRealMaxDist(val + MaxPadding); }
void Anchor1D::SetPaddedMaxSize(float val) { SetRealMaxSize(val - MaxPadding); }



float Anchor1D::GetSize() { return GetRealSize(); }
//float Anchor1D::GetHalfSize() { return GetRealHalfSize(); }
float Anchor1D::GetMinDist() { return GetPaddedMinDist(); }
float Anchor1D::GetMinSize() { return GetPaddedMinSize(); }
float Anchor1D::GetMaxDist() { return GetPaddedMaxDist(); }
float Anchor1D::GetMaxSize() { return GetPaddedMaxSize(); }
//float Anchor1D::GetNormalCenter() { return GetRealNormalCenter(); }
//float Anchor1D::GetCenter() { return GetRealCenter(); }

void Anchor1D::SetSize(float val) { SetRealSize(val); }
//void Anchor1D::SetHalfSize(float val) { SetRealHalfSize(val); }
void Anchor1D::SetMinDist(float val) { SetPaddedMinDist(val); }
void Anchor1D::SetMinSize(float val) { SetPaddedMinSize(val); }
void Anchor1D::SetMaxDist(float val) { SetPaddedMaxDist(val); }
void Anchor1D::SetMaxSize(float val) { SetPaddedMaxSize(val); }
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

AxisBox1D Anchor1D::Calculate(AxisBox1D Parent)
{
	float ParentSize = Parent.Max - Parent.Min;
	if (Anchor == AnchorType::Both)
	{
		Size = ParentSize - (MinDist + MaxDist);
		NormalCenter = GetRealCenter() / ParentSize;
	}
	else if (Anchor == AnchorType::Min)
	{
		MaxDist = ParentSize - GetRealMinSize();
		NormalCenter = GetRealCenter() / ParentSize;
	}
	else if (Anchor == AnchorType::Max)
	{
		MinDist = ParentSize - GetRealMaxSize();
		NormalCenter = GetRealCenter() / ParentSize;
	}
	else if (Anchor == AnchorType::None)
	{
		MinDist = (ParentSize * NormalCenter) - GetRealHalfSize();
		MaxDist = ParentSize - GetRealMinSize();
	}
	return AxisBox1D(Parent.Min + MinDist, Parent.Max - MaxDist);
}
