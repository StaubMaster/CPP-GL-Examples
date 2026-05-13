#include "VoxelGraphicsData.hpp"



void VoxelAxisGraphicsDataF::Done()
{
	for (unsigned int i = 0; i < Data.Count(); i++)
	{
		Data[i].CalcNormal();
	}
}

void VoxelGraphicsDataF::Done()
{
	Here.Done();
	PrevX.Done();
	PrevY.Done();
	PrevZ.Done();
	NextX.Done();
	NextY.Done();
	NextZ.Done();
}
