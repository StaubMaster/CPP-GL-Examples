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
	//refBoxF1 margin,
	//refBoxF1 boarder,
	//refBoxF1 padding,
	float & normal_center
)
	: Size(size)
	, Dist(dist)
	//, Margin(margin)
	//, Boarder(boarder)
	//, Padding(padding)
	, NormalCenter(normal_center)
	, Anchor(AnchorType::Min)
{ }



//float Anchor1D::GetMarginMinDist() const		{ return (Dist.Min       ) - Margin.Min; }
//float Anchor1D::GetMarginMinSize() const		{ return (Dist.Min + Size) + Margin.Min; }
//float Anchor1D::GetMarginMaxDist() const		{ return (Dist.Max       ) - Margin.Max; }
//float Anchor1D::GetMarginMaxSize() const		{ return (Dist.Max + Size) + Margin.Max; }

//void Anchor1D::SetMarginMinDist(float val)	{ Dist.Min = (val + Margin.Min)       ; }
//void Anchor1D::SetMarginMinSize(float val)	{ Dist.Min = (val - Margin.Min) - Size; }
//void Anchor1D::SetMarginMaxDist(float val)	{ Dist.Max = (val + Margin.Max)       ; }
//void Anchor1D::SetMarginMaxSize(float val)	{ Dist.Max = (val - Margin.Max) - Size; }



/*
float Anchor1D::AnchorMarginMin(float dist)
{
	Anchor = AnchorType::Min;
	SetMarginMinDist(dist);
	return GetMarginMinSize();
}
float Anchor1D::AnchorMarginMin(float dist, float size)
{
	Anchor = AnchorType::Min;
	SetMarginMinDist(dist);
	SetSize(size);
	return GetMarginMinSize();
}
float Anchor1D::AnchorMarginMax(float dist)
{
	Anchor = AnchorType::Max;
	SetMarginMaxDist(dist);
	return GetMarginMaxSize();
}
float Anchor1D::AnchorMarginMax(float dist, float size)
{
	Anchor = AnchorType::Max;
	SetMarginMaxDist(dist);
	SetSize(size);
	return GetMarginMaxSize();
}
void Anchor1D::AnchorMarginBoth(float min, float max)
{
	Anchor = AnchorType::Both;
	SetMarginMinDist(min);
	SetMarginMaxDist(max);
}
*/



void Anchor1D::ChangeO_Size(float sizeO)
{
	Size = sizeO - (Dist.Min + Dist.Max);
}
void Anchor1D::ChangeO_NormalCenter(float sizeO)
{
	NormalCenter = (Dist.Min + (Size / 2)) / sizeO;
}

void Anchor1D::UpdateO(const BoxF1 & boxO)
{
	float size = boxO.Size();
	if (Anchor == AnchorType::Both)
	{
		ChangeO_Size(size);
		ChangeO_NormalCenter(size);
	}
	else if (Anchor == AnchorType::Min)
	{
		Dist.Max = size - (Dist.Min + Size);
		ChangeO_NormalCenter(size);
	}
	else if (Anchor == AnchorType::Max)
	{
		Dist.Min = size - (Dist.Max + Size);
		ChangeO_NormalCenter(size);
	}
	else if (Anchor == AnchorType::None)
	{
		Dist.Min = (size * NormalCenter) - (Size / 2);
		Dist.Max = size - (Dist.Min + Size);
	}
}
void Anchor1D::UpdateO(const BoxF1 & boxO, const BoxF1 & boxI)
{
	Dist.Min = +(boxI.Min - boxO.Min);
	Dist.Max = -(boxI.Max - boxO.Max);

	float size = boxO.Size();
	ChangeO_Size(size);
	ChangeO_NormalCenter(size);
}

BoxF1 Anchor1D::ToInnerBox(const BoxF1 & boxO) const
{
	return BoxF1(
		boxO.Min + Dist.Min,
		boxO.Max - Dist.Max
	);
}
