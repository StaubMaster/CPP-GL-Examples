#include "AnchorAxis.hpp"
#include "AnchorEnum.hpp"
#include "ValueType/Box/F1.hpp"



AnchorAxis::AnchorAxis(
	float & size,
	float & dist_min,
	float & dist_max,
	float & normal_center
)
	: Size(size)
	, DistMin(dist_min)
	, DistMax(dist_max)
	, NormalCenter(normal_center)
	, Anchor(AnchorType::Min)
{ }



void AnchorAxis::ChangeBox(
	float boxO_min,
	float boxO_max,
	float boxI_min,
	float boxI_max
)
{
	DistMin = +(boxI_min - boxO_min);
	DistMax = -(boxI_max - boxO_max);

	float size = boxO_max - boxO_min;
	Size = size - (DistMin + DistMax);
	NormalCenter = (DistMin + (Size / 2)) / size;
}

void AnchorAxis::Update(float size)
{
	if (Anchor == AnchorType::Both)
	{
		Size = size - (DistMin + DistMax);
		NormalCenter = (DistMin + (Size / 2)) / size;
	}
	else if (Anchor == AnchorType::Min)
	{
		DistMax = size - (DistMin + Size);
		NormalCenter = (DistMin + (Size / 2)) / size;
	}
	else if (Anchor == AnchorType::Max)
	{
		DistMin = size - (DistMax + Size);
		NormalCenter = (DistMin + (Size / 2)) / size;
	}
	else if (Anchor == AnchorType::None)
	{
		DistMin = (size * NormalCenter) - (Size / 2);
		DistMax = size - (DistMin + Size);
	}
}
